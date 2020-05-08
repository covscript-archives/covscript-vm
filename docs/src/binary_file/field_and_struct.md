# Field and Struct

## Field
A `Field` structure is defined as follow:
```c
struct Field {
    u1 type;
    u1 info[];
};
```

Each field entry must begin with a 1-byte `tag` indicating the
kind of this field. The contents of the `info` array vary with the value of tag.

The valid tags and their values are listed in [Field tags](#field-tags). Each tag byte must be
followed by two or more bytes giving information about the specific field. The
format of the additional information varies with the `tag` value (see [Field Variants](#field-variants)).

### Field tags
| Field type | value | length of the `info` array |
| :--------: | :---: | :------------------------: |
| FIELD_var  | 1     | `sizeof(FieldVar)`         |
| FIELD_fn   | 2     | `sizeof(FieldFn)`          |


### Field variants
A field can be a variable or a function. Each has a different
binary representation.

#### FieldVar
```c
struct FieldVar {
    u2 name_index;
};
```

The value of the `name_index` item must be a valid index into the `string_pool` table.
The `string_pool` entry at that index represents the field name.

#### FieldFn
```c
struct FieldFn {
    u2 name_index;
    u2 block_count;
    CodeBlock block[block_count];
};
```

The items of the `FieldFn` structure are the following:

##### name_index
The value of the `name_index` item must be a valid index into the `string_pool` table.
The `string_pool` entry at that index represents the field name.

##### block_count
The value of the `block_count` item is equal to the number of entries in the `block` table.
A `block` index is considered valid if it is in the range `[0, block_count)`.

A function must at least have one block (the `block_count` is always greater than 0).
In run-time, the first block of a function is equal to `block[0]`.

##### block
A block refers to a **Basic Block** of the function's _Control Flow Graph_,
and it is defined as:

```c
struct CodeBlock {
    u2 next_block;
    u2 code_length;
    u1 code[code_length];
};
```

###### next_block
The value of the `next_block` item must be a valid index into the `block` table,
indicating the block that will be executed when this block ends.

###### code_length
The value of the `code_length` indicates the length of the `code` array.

###### code[]
The `code` array gives the actual bytes of Epoch Virtual Machine code
that implement the function.

The detailed constraints on the contents of the code array are extensive and are
given in [Instructions](../instruction/00-format-description.md).

## Struct
A `Struct` structure is defined as follow:

```c
struct Struct {
    u2 name_index;
    u2 field_count;
    Field field[field_count];
};
```

The items of the `Struct` structure are the following:

### name_index
The value of the `name_index` item must be a valid index into the `string_pool` table.
The `string_pool` entry at that index represents the field name.


### field_count
The value of the `field_count` item is equal to the number of entries in the `field` table.
A `field` index is considered valid if it is in the range `[0, field_count)`.

### field
The `field` is a table of structures representing various field defined in this struct.
A `Field` can be a function or a variable.
The format of `Field` structure is described in [**Field**](#field).

The `field` table is indexed from `0` to `field_count - 1`

