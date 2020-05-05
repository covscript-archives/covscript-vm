## local_store

### Operation
Store local variable.

### Format
| local_store |
| :----: |
| indexbyte1 |
| indexbyte2 |

### Forms
```
local_store =
```

### Operand Stack
```
..., value ->
...
```

### Description
Store the `value` to local variable `index` (constructed by `indexbyte1 << 8 | indexbyte2`).

### Run-time Exceptions

### Notes

