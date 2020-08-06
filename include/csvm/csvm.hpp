#pragma once

#include <csvm/framework.hpp>
#include <csvm/variable.hpp>

/**
 * Debug mode
 * COVSCRIPT_DEBUG_MODE
 */

namespace cs {
    struct object {
        bool reachable = false;
        var_t data;
        template<typename T, typename...ArgsT>
        object(typeholder<T> type, ArgsT&&...args) : data(type, mpp::forward<ArgsT>(args)...) {}
    };

    class object_not_in_heap final : public mpp::runtime_error {
    public:
        using mpp::runtime_error::runtime_error;
    };

    class vm_heap final {
        template <typename T> using allocator_t = mpp::allocator_type<T, 256>;
        allocator_t<object> allocator;
        set_t<object*> alloc_set;
    public:
        template<typename T, typename...ArgsT>
        object* alloc(ArgsT&&...args)
        {
            object *obj_ptr = allocator.alloc(typeholder<T>(), mpp::forward<ArgsT>(args)...);
            alloc_set.emplace(obj_ptr);
            return obj_ptr;
        }
        void free(object *ptr)
        {
#ifdef COVSCRIPT_DEBUG_MODE
            if (alloc_set.count(ptr) == 0)
                mpp::throw_ex<object_not_in_heap>("Object not in heap.");
#endif
            alloc_set.erase(ptr);
            allocator.free(ptr);
        }
    };
    class vm_stack final {
        stack_type<stack_type<var_t>> raw_stack;
    };
}
