## invoke

### Operation
Invoke function.

### Format
| invoke |
| :----: |
| indexbyte1 |
| indexbyte2 |

### Forms
```
invoke =
```

### Operand Stack
```
..., [arg1, [arg2...]] ->
..., [result]
```

### Description
Invoke function described by `index` (constructed by `indexbyte1 << 8 | indexbyte2`) with args (`arg1` .. `argN`).

The `result` is the function return value if and only if the function doesn't return void.

The `index` must be a valid **Constant Function Info Pool** index.

### Run-time Exceptions

### Notes
For more information about function invocation, please see
the runtime section about **Calling Conventions**.

