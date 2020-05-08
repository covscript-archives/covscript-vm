# Epoch File Structure

An epoch file consists of a single `EpochFile` structure.

```c
struct EpochFile {
    u4 magic;
    u4 version;

    u2 num_pool_count;
    NumInfo num_pool[num_pool_count];

    u2 string_pool_count;
    StringInfo string_pool[string_pool_count];

    u2 field_pool_count;
    FieldInfo field_pool[field_pool_count];

    u2 type_pool_count;
    TypeInfo type_pool[type_pool_count];

    u2 this_field_count;
    Field this_field[this_field_count];

    u2 this_struct_count;
    Struct this_struct[this_struct_count];
};
```

The items in the `EpochFile` structure are as follows:

#### magic
The `magic` item supplies the `magic` number identifying the class file format;
it has the value `0xCC114514`.

#### version
The value of `version` is the version number of this class file. Together, a version number determine the version of the class file format.

#### num_pool_count
The value of the `num_pool_count` item is equal to the number of entries in the `num_pool` table.
A `num_pool` index is considered valid if it is in the range `[0, num_pool_count)`.

#### num_pool
The `num_pool` is a table of structures representing various **number constants** that are referred to within the `EpochFile` structure and its substructures. The format of each `num_pool` table entry is described later in [**Constant Pools**](constant_pool.md).

The `num_pool` table is indexed from `0` to `num_pool_count - 1`

#### string_pool_count
The value of the `string_pool_count` item is equal to the number of entries in the `string_pool` table.
A `string_pool` index is considered valid if it is in the range `[0, string_pool_count)`.

#### string_pool
The `string_pool` is a table of structures representing various **string constants** that are referred to within the `EpochFile` structure and its substructures. The format of each `string_pool` table entry is described later in [**Constant Pools**](constant_pool.md).

The `string_pool` table is indexed from `0` to `string_pool_count - 1`

#### field_pool_count
The value of the `field_pool_count` item is equal to the number of entries in the `field_pool` table.
A `field_pool` index is considered valid if it is in the range `[0, field_pool_count)`.

#### field_pool
The `field_pool` is a table of structures representing various **field constants** that are referred to within the `EpochFile` structure and its substructures. The format of each `field_pool` table entry is described later in [**Constant Pools**](constant_pool.md).

The `field_pool` table is indexed from `0` to `field_pool_count - 1`

#### type_pool_count
The value of the `type_pool_count` item is equal to the number of entries in the `type_pool` table.
A `type_pool` index is considered valid if it is in the range `[0, type_pool_count)`.

#### type_pool
The `type_pool` is a table of structures representing various **type constants** that are referred to within the `EpochFile` structure and its substructures. The format of each `type_pool` table entry is described later in [**Constant Pools**](constant_pool.md).

The `type_pool` table is indexed from `0` to `type_pool_count - 1`

#### this_field_count
The value of the `this_field_count` item is equal to the number of entries in the `this_field` table.
A `this_field` index is considered valid if it is in the range `[0, this_field_count)`.

#### this_field
The `this_field` is a table of structures representing various field defined in this file. A `Field` can be a function or a variable. The format of `Field` structure is described later in [**Field and Struct**](field_and_struct.md).

The `this_field` table is indexed from `0` to `this_field_count - 1`

#### this_struct_count
The value of the `this_struct_count` item is equal to the number of entries in the `this_struct` table.
A `this_struct` index is considered valid if it is in the range `[0, this_struct_count)`.

#### this_struct
The `this_struct` is a table of structures representing various field defined in this file. The format of `Struct` structure is described later in [**Field and Struct**](field_and_struct.md).

The `this_struct` table is indexed from `0` to `this_struct_count - 1`

