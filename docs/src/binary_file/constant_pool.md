# Constant Pool

## Constant Number Pool
The `NumInfo` represent 8-byte numeric(double) constants:

```c
struct NumInfo {
    u4 high_bytes;
    u4 low_bytes;
};
```

The items of these structures are as follows:

#### high_bytes, low_bytes
The **unsigned** `high_bytes` and `low_bytes` items of the `NumInfo`
structure together represent the `double` value in _**IEEE 754 floating-point**_ double format. The bytes of each item are stored in big-endian (high byte first) order.

The value represented by the `NumInfo` structure is determined
as follows:

The `high_bytes` and `low_bytes` items are converted into the `long`
constant `bits`, which is equal to

```c
long bits = ((long) high_bytes << 32) + low_bytes;
```

Then:
- If `bits` is `0x7ff0000000000000L`, the double value will be positive infinity.

- If `bits` is `0xfff0000000000000L`, the double value will be negative infinity.

- If `bits` is in the range `0x7ff0000000000001L` through `0x7fffffffffffffffL` or in the range `0xfff0000000000001L` through `0xffffffffffffffffL`, the double value will be `NaN`.

- In all other cases, let `s`, `e`, and `m` be three values that might be computed from `bits`:

    ```c
    int s = ((bits >> 63) == 0) ? 1 : -1;
    int e = (int) ((bits >> 52) & 0x7ffL);
    long m = (e == 0)
           ? (bits & 0xfffffffffffffL) << 1
           : (bits & 0xfffffffffffffL) | 0x10000000000000L;
    ```
    Then the floating-point value equals the `double` value of the mathematical expression
    $$s \times m \times {2}^{e-1075}$$
    which is equivalent to the following code:
    ```c
    double value = s * m * pow(2, e - 1075);
    ```
    where the `pow` is of type `(double, double) -> double`.

## Constant String Pool
The `StringInfo` structure is used to represent constant string values:

```c
struct StringInfo {
    u2 length;
    u1 bytes[length];
};
```

The items of the `StringInfo` structure are the following:

#### length
The value of the length item gives the number of bytes in the bytes array
(not the length of the resulting string). The strings in the `StringInfo`
structure are not null-terminated.

#### bytes[]
The bytes array contains the bytes of the string. No byte may have the value
`(u1) 0` or lie in the range `(u1) 0xf0` - `(u1) 0xff`.

## Constant Field Info Pool and Constant Type Info Pool
Fields and Types are represented by similar structures:

```c
struct FieldInfo {
    u2 name_index;
};

struct TypeInfo {
    u2 name_index;
};
```

The value of the `name_index` item must be a valid index into the `string_pool` table.
The `string_pool` entry at that index represents the field name or type name.

If the name of the field of a `FieldInfo` structure begins with a '<' ('\u003c'),
then the name must be the special name `<class-init>`, representing a class constructor method.
The return type of such a method must be `Unit`. (see [Reserved Names](../runtime/reserved_names.md))

If the name of the field of a `FieldInfo` structure is `constructor`, then it must
be representing a object constructor method.
The return type of such a method must be `Unit`. (see [Reserved Names](../runtime/reserved_names.md))

