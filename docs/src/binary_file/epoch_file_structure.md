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
    FieldInfo this_field[this_field_count];
};
```

The items in the `EpochFile` structure are as follows:

