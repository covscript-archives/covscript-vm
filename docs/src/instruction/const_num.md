## const_num

### Operation
Push double.

### Format
| const_num |
| :----: |
| indexbyte1 |
| indexbyte2 |

### Forms
const_num =

### Operand Stack
```
...->
..., value
```

### Description
Push the `value` (stored in **Constant Number Pool** indexed by `index` (constructed by `indexbyte1 << 8 | indexbyte2`))
onto the operand stack.

### Run-time Exceptions

### Notes

