## local_load

### Operation
Load local variable.

### Format
| local_load |
| :----: |
| indexbyte1 |
| indexbyte2 |

### Forms
```
local_load =
```

### Operand Stack
```
...->
..., value
```

### Description
Push local variable `index` (constructed by `indexbyte1 << 8 | indexbyte2`) onto the operand stack.

### Run-time Exceptions

### Notes

