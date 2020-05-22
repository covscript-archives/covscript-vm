# Types

In Epoch VM, there are types defined as follows:

- Unit
- Int32
- Number
- String
- Any

## Unit
The `Unit` type has only one value `()`.

## Int32
The `Int32` type is equivalent to `int32_t` in C++ and `i32` in Rust.
The valid range is `[-2147483648, 2147483467]`.

## Number
The `Number` type is equivalent to `long double` in C++.

## String
The `String` type is equivalent to `std::string` in C++.

## Any
The `Any` type can be any type listed above or any complete C++ type.

