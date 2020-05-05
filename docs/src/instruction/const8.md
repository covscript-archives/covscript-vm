## const8

### Operation
Push byte.

### Format
| const8 |
| :----: |
| byte |

### Forms
```
const8 =
```

### Operand Stack
```
... ->
..., value
```

### Description
The immediate `byte` is **sign-extended** to an `int` value.
That `value` is pushed onto the operand stack.

### Run-time Exceptions

### Notes

