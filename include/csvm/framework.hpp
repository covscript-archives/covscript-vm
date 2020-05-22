#pragma once
#include <unordered_map>
#include <utility>
#include <string>
#include <deque>
#include <list>

namespace cs {
    // Build-in Type
    class var_t;
    template<typename _kT, typename _vT> using map_t = std::unordered_map<_kT, _vT>;
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
}
