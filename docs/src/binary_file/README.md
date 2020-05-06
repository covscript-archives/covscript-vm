# Binary File Format

In this chapter, we will standardize:
- Binary file header
- Constant pools
- Functions' binary representation
- Structs' binary representation

## File Type
Epoch VM loads and executes **epoch file** (with the file extension `.epoch`).

An epoch class file consists of a stream of 8-bit bytes. All 16-bit, 32-bit, and 64-bit
quantities are constructed by reading in two, four, and eight consecutive 8-bit
bytes, respectively. Multibyte data items are always stored in **big-endian order**,
where the high bytes come first.

## Conventions

This chapter defines its own set of data types representing class file data: The
types `u1`, `u2`, and `u4` represent an unsigned `one-`, `two-`, or `four-`byte quantity,
respectively.

In the C++ programming language, these data types are defined as:
```cpp
using u1 = uint8_t;
using u2 = uint16_t;
using u4 = uint32_t;
```

This chapter presents the class file format using pseudo-structures written in a
C-like structure notation. To avoid confusion with the fields of classes and class
instances, etc., the contents of the structures describing the class file format are
referred to as items. Successive items are stored in the class file sequentially,
without padding or alignment.

Tables, consisting of zero or more variable-sized items, are used in several class
file structures. Although we use C-like array syntax to refer to table items, the fact
that tables are streams of varying-sized structures means that it is not possible to
translate a table index directly to a byte offset into the table.
Where we refer to a data structure as an array, it consists of zero or more contiguous
fixed-sized items and can be indexed like an array.
