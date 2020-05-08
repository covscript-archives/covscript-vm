## new_dyn

### Operation
New object.

### Format
| new_dyn |
| :----: |

### Forms
```
new_dyn =
```

### Operand Stack
```
..., type ->
..., object
```

### Description
Allocate an object from garbage-collected heap with type described by `type`.
Object fields are initialized with their **default values**.

The `type` must be a valid **type reference**.

### Run-time Exceptions

### Notes

