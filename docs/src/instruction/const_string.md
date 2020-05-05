## const_string

### Operation
Push string.

### Format
| const_string |
| :----: |
| indexbyte1 |
| indexbyte2 |

### Forms
const_string =

### Operand Stack
```
...->
..., value
```

### Description
Push the `value` (stored in **Constant String Pool** indexed by `index` (constructed by `indexbyte1 << 8 | indexbyte2`))
onto the operand stack.

### Run-time Exceptions

### Notes

