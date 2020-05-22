## jump_\<cmp\>

### Operation
Compare and jump.

### Format
| jump_\<cmp\> |
| :----: |
| bbbyte1 |
| bbbyte2 |

### Forms
```
jump_eq =
jump_ne =
jump_lt =
jump_le =
jump_gt =
jump_ge =
```

### Operand Stack
```
..., value ->
...
```

### Description
The `value` is popped from the operand stack and compared.
The results of the comparison are as follows:
- `jump_eq` succeeds if and only if `value == 0`
- `jump_ne` succeeds if and only if `value != 0`
- `jump_lt` succeeds if and only if `value < 0`
- `jump_le` succeeds if and only if `value <= 0`
- `jump_gt` succeeds if and only if `value > 0`
- `jump_ge` succeeds if and only if `value >= 0`

If the comparison succeeds, the **unsigned** `bbbyte1` and
`bbbyte2` are used to construct a **signed 16-bit BBID**, where
the BBID is calculated to be `(bbbyte1 << 8) | bbbyte2`.

Execution then proceeds at that BBID. The target BB
must be a BaiscBlock within the function that
contains this `jump_<cmp>` instruction.

Otherwise, if the comparison fails, execution proceeds at
the address of the instruction following this `jump_<cmp>`
instruction.

### Run-time Exceptions
