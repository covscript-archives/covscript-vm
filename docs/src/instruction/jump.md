## jump

### Operation
Unconditionally jump.

### Format
| jump |
| :----: |
| bbbyte1 |
| bbbyte2 |

### Forms
```
jump =
```

### Description
The **unsigned** `bbbyte1` and `bbyte2` are used to
construct a **signed 16-bit BBID**, where the BBID is calculated
to be `(bbbyte1 << 8) | bbyte2`.

Execution then proceeds at that BB. The target BB
must be an BasicBlock within the function that
contains this `jump` instruction.


### Run-time Exceptions

### Notes

