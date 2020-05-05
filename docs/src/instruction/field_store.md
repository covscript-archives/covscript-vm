## field_store

### Operation
Store object field

### Format
| field_store |
| :----: |
| indexbyte1 |
| indexbyte2 |

### Forms
```
field_store =
```

### Operand Stack
```
..., object, value ->
...
```

### Description
Store the `value` to `object` field (described by `index` (constructed by `indexbyte1 << 8 | indexbyte2`)).
The `index` must be a valid **Constant Field Info Pool** index.

### Run-time Exceptions

### Notes

