## jump_null

### Operation
Jump if null.

### Format
| jump_null |
| :----: |
| bbbyte1 |
| bbbyte1 |

### Forms
jump_null =

### Operand Stack
```
..., value ->
...
```

### Description
The `value` is popped from the operand stack and compared.
The results of the comparison are as follows:
- `jump_null` succeeds if and only if `value == null`

If the comparison succeeds, the **unsigned** `bbbyte1` and
`bbbyte2` are used to construct a **signed 16-bit BBID**, where
the BBID is calculated to be `(bbbyte1 << 8) | bbbyte2`.

Execution then proceeds at that BBID. The target BB
must be a BasicBlock within the function that
contains this `jump_<cmp>` instruction.

Otherwise, if the comparison fails, execution proceeds at
the address of the instruction following this `jump_<cmp>`
instruction.

### Run-time Exceptions
