## jump

### Operation
Unconditionally jump.

### Format
| jump |
| :----: |
| branchbyte1 |
| branchbyte2 |

### Forms
```
jump =
```

### Description
The **unsigned** `branchbyte1` and `branchbyte2` are used to
construct a **signed 16-bit offset**, where the offset is calculated
to be `(branchbyte1 << 8) | branchbyte2`.

Execution then proceeds at that offset from the address of the
opcode of this `jump` instruction. The target address
must be that of an opcode of an instruction within the function that
contains this `jump` instruction.


### Run-time Exceptions

### Notes

