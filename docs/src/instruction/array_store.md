## array_store

### Operation
Store an value to an array.

### Format
| array_store |
| :----: |

### Forms
```
array_store =
```

### Operand Stack
```
..., array, index, value ->
...
```

### Description
The `array` must refer to an array. The `index` must be of
type number. The `value` is of type any.
The `array`, `index` and `value` are popped from the operand
stack.
The `value` is stored as the component of the `array` at `index`.

### Run-time Exceptions

### Notes

