## if_\<cmp\>

### Operation
Compare and jump.

### Format
| if_\<cmp\> |
| :----: |
| bbbyte1 |
| bbbyte2 |

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

If the comparison succeeds, the **unsigned** `bbbyte1` and
`bbbyte2` are used to construct a **signed 16-bit BBID**, where
the BBID is calculated to be `(bbbyte1 << 8) | bbbyte2`.

Execution then proceeds at that BB. The target BB
must be a BasicBlock within the function that
contains this `if_<cmp>` instruction.

Otherwise, if the comparison fails, execution proceeds at
the address of the instruction following this `if_<cmp>`
instruction.

### Run-time Exceptions
