## const32

### Operation
Push int32.

### Format
| const32 |
| :----: |
| byte1 |
| byte2 |
| byte3 |
| byte4 |

### Forms
const32 =

### Operand Stack
```
...->
..., value
```

### Description
Push the `value` (constructed by `byte1 << 24 | byte2 << 16 | byte3 << 8 | byte4`)
on to the operand stack.

### Run-time Exceptions

### Notes

