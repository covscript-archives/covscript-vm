#pragma once

#include <csvm/framework.hpp>
#include <mozart++/memory>
#include <typeindex>
#include <utility>

/*
 * Small Object Optimization
 * Over-provisioning space will be N*sizeof(void*)
 * Default is 3
 */
#ifdef  COVSCRIPT_VARIABLE_SSO
#if     COVSCRIPT_VARIABLE_SSO <= 0
#define COVSCRIPT_VARIABLE_SSO 1
#endif
#else
#define COVSCRIPT_VARIABLE_SSO 3
#endif

namespace cs {
	struct monotype final {
	};

	template<typename T>
	struct typeholder final {
	};

	template <typename T>
	class is_copyable final {
		template <typename X>
		static void test(X) {}

		template <typename>
		constexpr static bool helper(...)
		{
			return false;
		}

		template <typename X, typename = decltype(test(std::declval<X>()))>
		constexpr static bool helper(int = 0)
		{
			return true;
		}

	public:
		constexpr static bool result = helper<T>(0);
	};

	template <typename, typename, bool>
	struct select_if;
	template <typename A, typename B>
	struct select_if<A, B, true> {
		using result = A;
	};
	template <typename A, typename B>
	struct select_if<A, B, false> {
		using result = B;
	};

	class var_t final {
		template <typename T> using allocator_t = mpp::allocator_type<T, 64>;
		using byte_t = unsigned char;

		struct data_base {
			virtual ~data_base() = default;
			virtual void deallocate(bool) = 0;
			virtual data_base *clone() const = 0;
            virtual void clone(byte_t *) const = 0;
			virtual void set_field(field *) noexcept = 0;
            virtual field *get_field() const noexcept = 0;
			virtual const std::type_info &type() const noexcept = 0;
		};

		template <typename data_t>
		struct data_impl_base : public data_base {
			field *m_ref = nullptr;
			data_t actual_data;

			template <typename...args_t>
			explicit data_impl_base(args_t &&...args) : actual_data(std::forward<args_t>(args)...) {}

			field *get_field() const noexcept override
			{
				return m_ref;
			}

			void set_field(field *ref) noexcept override
			{
				m_ref = ref;
			}

			const std::type_info &type() const noexcept override
			{
				return typeid(data_t);
			}
		};

		template <typename data_t>
		struct data_impl_copyable : public data_impl_base<data_t> {
			inline static allocator_t<data_impl_copyable> &get_alloc()
			{
				static allocator_t<data_impl_copyable> alloc;
				return alloc;
			}

			using data_impl_base<data_t>::data_impl_base;

            data_base *clone() const override
            {
                return get_alloc().alloc(this->actual_data);
            }

			void clone(byte_t *ptr) const override
			{
				::new(ptr) data_impl_copyable(this->actual_data);
			}

			void deallocate(bool sso_hit) override
			{
				if (sso_hit)
					this->~data_impl_copyable();
				else
				    get_alloc().free(this);
			}
		};

		template <typename data_t>
		struct data_impl_noncopyable : public data_impl_base<data_t> {
			inline static allocator_t<data_impl_noncopyable> &get_alloc()
			{
				static allocator_t<data_impl_noncopyable> alloc;
				return alloc;
			}

            data_base *clone() const override
            {
                mpp::throw_ex<mpp::runtime_error>("Target type is non-copyable");
            }

			void clone(byte_t *ptr) const override
			{
				mpp::throw_ex<mpp::runtime_error>("Target type is non-copyable");
			}

			void deallocate(bool sso_hit) override
			{
				if (sso_hit)
					this->~data_impl_noncopyable();
				else
				    get_alloc().free(this);
			}
		};

		template <typename data_t> using data_impl = typename select_if<data_impl_copyable<data_t>, data_impl_noncopyable<data_t>, is_copyable<data_t>::result>::result;

		struct data_store final {
		    static constexpr auto sso_threshold = COVSCRIPT_VARIABLE_SSO * std::alignment_of<data_base *>::value;
			union {
				byte_t sso_cache[sso_threshold];
				data_base *ptr = nullptr;
			} data;
			bool sso_hit = true;

            template<typename T>
			struct sso_enabled_policy
            {
                template <typename...ArgsT>
                static inline void store(data_store& self, ArgsT&&...args) {
                    ::new(self.data.sso_cache) data_impl<T>(std::forward<ArgsT>(args)...);
                    self.sso_hit = true;
                }
                static inline T& instantiate(data_store& self)
                {
                    auto ptr = reinterpret_cast<data_base *>(self.data.sso_cache);
                    if (ptr->type() == typeid(T))
                        return static_cast<data_impl<T>*>(ptr)->actual_data;
                    else
                        mpp::throw_ex<mpp::runtime_error>("Wrong type");
                }
                static inline const T& instantiate(const data_store& self)
                {
                    auto ptr = reinterpret_cast<const data_base *>(self.data.sso_cache);
                    if (ptr->type() == typeid(T))
                        return static_cast<const data_impl<T>*>(ptr)->actual_data;
                    else
                        mpp::throw_ex<mpp::runtime_error>("Wrong type");
                }
            };

			template<typename T>
			struct sso_disabled_policy
            {
                template <typename...ArgsT>
                static inline void store(data_store& self, ArgsT&&...args) {
                    self.data.ptr = data_impl<T>::get_alloc().alloc(std::forward<ArgsT>(args)...);
                    self.sso_hit = false;
                }
                static inline T& instantiate(data_store& self)
                {
                    if (self.data.ptr->type() == typeid(T))
                        return static_cast<data_impl<T>*>(self.data.ptr)->actual_data;
                    else
                        mpp::throw_ex<mpp::runtime_error>("Wrong type");
                }
                static inline const T& instantiate(const data_store& self)
                {
                    if (self.data.ptr->type() == typeid(T))
                        return static_cast<const data_impl<T>*>(self.data.ptr)->actual_data;
                    else
                        mpp::throw_ex<mpp::runtime_error>("Wrong type");
                }
            };

			template<typename T> using sso_dispatcher = typename select_if<sso_enabled_policy<T>, sso_disabled_policy<T>, sizeof(data_impl<T>) <= sso_threshold>::result;

            inline data_base *get_handler()
            {
                if (sso_hit)
                    return reinterpret_cast<data_base *>(data.sso_cache);
                else
                    return data.ptr;
            }

			inline const data_base *get_handler() const
            {
                if (sso_hit)
                    return reinterpret_cast<const data_base *>(data.sso_cache);
                else
                    return data.ptr;
            }

            inline void copy(const data_store& dat)
            {
                sso_hit = dat.sso_hit;
                if (!sso_hit)
                    data.ptr = dat.get_handler()->clone();
                else
                    dat.get_handler()->clone(data.sso_cache);
            }

            data_store()
            {
                sso_dispatcher<monotype>::store(*this);
            }

            data_store(const data_store &dat)
            {
                copy(dat);
            }

            template<typename T, typename...ArgsT>
            explicit data_store(typeholder<T> holder, ArgsT&&...args)
            {
                sso_dispatcher<T>::store(*this, std::forward<ArgsT>(args)...);
            }

            ~data_store()
            {
                get_handler()->deallocate(sso_hit);
            }
		} data;
	public:
	    var_t() = default;
	    var_t(const var_t &) = default;
	    template<typename T, typename...ArgsT>
	    explicit var_t(typeholder<T> holder, ArgsT&&...args) : data(holder, std::forward<ArgsT>(args)...) {}
	    inline const std::type_info& type() const noexcept
        {
	        return data.get_handler()->type();
        }
        template<typename T>
        inline T& get()
        {
            return data_store::sso_dispatcher<T>::instantiate(data);
        }
        template<typename T>
        inline const T& get() const
        {
            return data_store::sso_dispatcher<T>::instantiate(data);
        }
	};
}
