## jump_null

### Operation
Jump if null.

### Format
| jump_null |
| :----: |
| branchbyte1 |
| branchbyte2 |

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

If the comparison succeeds, the **unsigned** `branchbyte1` and
`branchbyte2` are used to construct a **signed 16-bit offset**, where
the offset is calculated to be `(branchbyte1 << 8) | branchbyte2`.

Execution then proceeds at that offset from the address of the
opcode of this `jump_<cmp>` instruction. The target address
must be that of an opcode of an instruction within the function that
contains this `jump_<cmp>` instruction.

Otherwise, if the comparison fails, execution proceeds at
the address of the instruction following this `jump_<cmp>`
instruction.

### Run-time Exceptions
