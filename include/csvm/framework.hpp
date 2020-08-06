#pragma once
#include <mozart++/core>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <string>
#include <deque>
#include <list>

namespace cs {
    // Build-in Type
    class var_t;
    template<typename _kT, typename _vT> using map_t = std::unordered_map<_kT, _vT>;
    template<typename _vT> using set_t = std::unordered_set<_vT>;
    // Basic Type
    using char_t     = char;
    using number_t   = long double;
    using boolean_t  = bool;
    // using pointer_t = TODO
    using string_t   = std::string;
    using array_t    = std::deque<var_t>;
    using list_t     = std::list<var_t>;
    using pair_t     = std::pair<var_t, var_t>;
    using hash_map_t = cs::map_t<var_t, var_t>;
    class field;

    class stack_overflow final : public mpp::runtime_error {
    public:
        using mpp::runtime_error::runtime_error;
    };

    class stack_empty final : public mpp::runtime_error {
    public:
        using mpp::runtime_error::runtime_error;
    };

    template<typename T, std::size_t m_size = 512>
    class stack_type final {
        typename std::aligned_storage<sizeof(T), alignof(T)>::type m_data[m_size];
        T *m_start = nullptr, *m_current = nullptr;
    public:
        class iterator final {
            friend class stack_type;

            T *m_ptr = nullptr;

            explicit iterator(T *const ptr) : m_ptr(ptr) {}

        public:
            iterator() = delete;

            iterator(const iterator &) = default;

            iterator(iterator &&) noexcept = default;

            ~iterator() = default;

            inline T &operator*() const noexcept
            {
                return *m_ptr;
            }

            inline T *operator->() const noexcept
            {
                return m_ptr;
            }

            inline iterator &operator++() noexcept
            {
                --m_ptr;
                return *this;
            }

            inline const iterator operator++(int) noexcept
            {
                return iterator(m_ptr--);
            }

            inline bool operator==(const iterator &it) const noexcept
            {
                return m_ptr == it.m_ptr;
            }

            inline bool operator!=(const iterator &it) const noexcept
            {
                return m_ptr != it.m_ptr;
            }
        };

        stack_type() : m_start(reinterpret_cast<T *>(m_data)), m_current(m_start) {}

        stack_type(const stack_type &) = delete;

        ~stack_type()
        {
            while (m_current != m_start)
                (--m_current)->~T();
        }

        inline bool empty() const
        {
            return m_current == m_start;
        }

        inline std::size_t size() const
        {
            return m_current - m_start;
        }

        inline bool full() const
        {
            return m_current - m_start == m_size;
        }

        inline T &top() const
        {
            if (empty())
                mpp::throw_ex<stack_empty>("Access top element of empty stack.");
            return *(m_current - 1);
        }

        inline T &bottom() const
        {
            if (empty())
                mpp::throw_ex<stack_empty>("Access bottom element of empty stack.");
            return *m_start;
        }

        inline T &at(std::size_t offset) const
        {
            if (offset >= size())
                mpp::throw_ex<std::out_of_range>("Stack out of range.");
            return *(m_current - offset - 1);
        }

        inline T &operator[](std::size_t offset) const
        {
            return *(m_current - offset - 1);
        }

        template<typename...ArgsT>
        inline void push(ArgsT &&...args)
        {
            if (full())
                mpp::throw_ex<stack_overflow>("Stack overflow.");
            ::new(m_current++) T(std::forward<ArgsT>(args)...);
        }

        inline T pop()
        {
            if (empty())
                mpp::throw_ex<stack_empty>("Pop from empty stack.");
            T data(std::move(*m_current));
            (m_current - 1)->~T();
            --m_current;
            return std::move(data);
        }

        inline void pop_no_return()
        {
            if (empty())
                mpp::throw_ex<stack_empty>("Pop from empty stack.");
            (m_current - 1)->~T();
            --m_current;
        }

        iterator begin() const noexcept
        {
            return iterator(m_current - 1);
        }

        iterator end() const noexcept
        {
            return iterator(m_start - 1);
        }
    };
}
