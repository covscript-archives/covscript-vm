## if_\<cmp\>

### Operation
Compare and jump.

### Format
| if_\<cmp\> |
| :----: |
| branchbyte1 |
| branchbyte1 |

### Forms
```
if_eq =
if_ne =
if_lt =
if_le =
if_gt =
if_ge =
```

### Operand Stack
```
..., lhs, rhs ->
...
```

### Description
Both `lhs` and `rhs` are popped from the operand stack and compared.
The results of the comparison are as follows:
- `if_eq` succeeds if and only if `lhs == rhs`
- `if_ne` succeeds if and only if `lhs != rhs`
- `if_lt` succeeds if and only if `lhs < rhs`
- `if_le` succeeds if and only if `lhs <= rhs`
- `if_gt` succeeds if and only if `lhs > rhs`
- `if_ge` succeeds if and only if `lhs >= rhs`

If the comparison succeeds, the **unsigned** `branchbyte1` and
`branchbyte2` are used to construct a **signed 16-bit offset**, where
the offset is calculated to be `(branchbyte1 << 8) | branchbyte2`.

Execution then proceeds at that offset from the address of the
opcode of this `if_<cmp>` instruction. The target address
must be that of an opcode of an instruction within the function that
contains this `if_<cmp>` instruction.

Otherwise, if the comparison fails, execution proceeds at
the address of the instruction following this `if_<cmp>`
instruction.

### Run-time Exceptions
