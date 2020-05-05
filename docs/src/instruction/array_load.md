## array_load

### Operation
Load an value from an array.

### Format
| array_load |
| :----: |

### Forms
```
array_load =
```

### Operand Stack
```
..., array, index ->
..., value
```

### Description
The `array` must refer to an array. The `index` must be of
type number. Both `array` and `index` are popped from the operand
stack. The value in the component of the array at index
is retrieved and pushed onto the operand stack.

### Run-time Exceptions

### Notes

