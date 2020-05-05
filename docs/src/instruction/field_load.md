## field_load

### Operation
Load object field.

### Format
| field_load |
| :----: |
| indexbyte1 |
| indexbyte2 |

### Forms
```
field_load =
```

### Operand Stack
```
..., object ->
..., field
```

### Description
Push the `field` of the `object` onto the operand stack.
The `index` (constructed by `indexbyte1 << 8 | indexbyte2`) must be a valid **Constant Field Info Pool** index.

### Run-time Exceptions

### Notes

