## invoke_ctor

### Operation
Invoke constructor on an object.

### Format
| invoke_ctor |
| :----: |

### Forms
```
invoke_ctor =
```

### Operand Stack
```
..., [arg1, [arg2...]], object ->
..., object
```

### Description
Invoke constructor function on `object` with args (`arg1` .. `argN`),
and **re-push** the `object` onto the operand stack.

### Run-time Exceptions

### Notes

