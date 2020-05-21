#pragma once
#include <csvm/framework.hpp>
#include <typeindex>
#include <utility>
#include <memory>

/**
 * Small Object Optimization
 * Set N <= 0 to disable
 * Otherwise, over-provisioning space will be N*sizeof(void*)
 * Default is 3
 */
#ifndef COVSCRIPT_VARIABLE_SSO
#define COVSCRIPT_VARIABLE_SSO 3
#endif

namespace cs {
    class monotype final {};
    template<typename T>
    class is_copyable final {
        template<typename X> static void test(X);
        template<typename>
        constexpr static bool helper(...)
        {
            return false;
        }
        template<typename X, typename = decltype(test(std::declval<X>()))>
        constexpr static bool helper(int = 0)
        {
            return true;
        }
    public:
        constexpr static bool value = helper<T>(0);
    };
    template<typename, typename, bool> struct select_if;
    template<typename A, typename B> struct select_if<A, B, true>
    {
        using result = A;
    };
    template<typename A, typename B> struct select_if<A, B, false>
    {
        using result = B;
    };
    class var_t final {
        template<typename T> using allocator_t = std::allocator<T>;
        using byte_t = unsigned char;
        class data_base
        {
        public:
            virtual ~data_base() = default;
            virtual data_base* clone(const byte_t *) = 0;
            virtual const std::type_info& type() noexcept = 0;
        };
        template<typename data_t>
        class data_impl_copyable : pulic data_base {
        public:
            inline static allocator_t<data_impl>& get_alloc()
            {
                static allocator_t<data_impl> alloc;
                return alloc;
            }
            data_t actual_data;
            template<typename...args_t>
            data_impl(args_t&&...args) : actual_data(std::forward<args_t>(args)...) {}
            virtual ~data_impl_copyable() override = default;
            virtual data_base* clone(const byte_t *ptr) override {
                ::new (ptr) data_impl(actual_data);
            }
            virtual const std::type_info& type() noexcept override {
                return typeid(data_t);
            }
        };
        template<typename data_t>
        class data_impl_noncopyable : pulic data_base {
        public:
            inline static allocator_t<data_impl>& get_alloc()
            {
                static allocator_t<data_impl> alloc;
                return alloc;
            }
            data_t actual_data;
            template<typename...args_t>
            data_impl(args_t&&...args) : actual_data(std::forward<args_t>(args)...) {}
            virtual ~data_impl_copyable() override = default;
            virtual data_base* clone(const byte_t *ptr) override {
                mpp::throw_ex<mpp::runtime_error>("Target type is non-copyable");
            }
        };
        template<typename data_t> using data_impl = typename select_if<
                data_impl_copyable<data_t>,
                data_impl_noncopyable<data_t>,
                is_copyable<data_t>::result
            >::result;
        class data_stor final
        {
#if COVSCRIPT_VARIABLE_SSO > 0
            byte_t sso_cache[COVSCRIPT_VARIABLE_SSO*sizeof(void*)];
            bool sso_hit = false;
#endif
            data_base* data = nullptr;
            void erase_data() const
            {
#if COVSCRIPT_VARIABLE_SSO > 0
#else

#endif
            }
        public:
            template<typename T, typename ...ArgsT>
            void insert_data() const
            {

            }
            template<typename T>
            T& get_data() const
            {
                if (data->type() == typeid(T))
                    return static_assert<const data_impl<T>*>(data)->actual_data;
                else
                    mpp::throw_ex<mpp::runtime_error>("Wrong type");
            }
            inline const data_base* get_raw_data() const
            {
                return data;
            }
            data_stor()
            {

            }
        };
    };
}
