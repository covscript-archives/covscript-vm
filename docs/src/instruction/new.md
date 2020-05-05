## new

### Operation
New object.

### Format
| new |
| :----: |
| indexbyte1 |
| indexbyte2 |

### Forms
```
new =
```

### Operand Stack
```
...->
..., object
```

### Description
Allocate an object from garbage-collected heap with type described by `index` (constructed by `indexbyte1 << 8 | indexbyte2`).
Object fields are initialized with their **default values**.
The `index` must be a valid **Constant Type Info Pool** index.

### Run-time Exceptions

### Notes

