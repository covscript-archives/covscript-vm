# Format of Instruction Descriptions

Epoch Virtual Machine instructions are represented in this chapter by entries of the
form shown below, in alphabetical order and each beginning on a new page.

Here an example starts:

-------

## mnemonic

### Operation
Short description of the instruction

### Format
| mnemonic |
| :----: |
| operand1 |
| operand2 |
|   ...    |

### Forms
mnemonic = opcode

### Operand Stack
```
..., value1, value2 ->
..., value3
```

### Description
A longer description detailing constraints on operand stack
contents or constant pool entries, the operation performed, the type
of the results, etc.

### Run-time Exceptions
If any run-time exceptions can be thrown by the execution of an
instruction, they are set off one to a line, in the order in which they
must be thrown.
Other than the run-time exceptions, if any, listed
for an instruction, that instruction must not throw any run-time
exceptions except for instances of `VirtualMachineError`.

### Notes
Comments not strictly part of the specification of an instruction
are set aside as notes at the end of the description.

---------------------

Here the example ends.


## Detailed Explanation

### mnemonic and opcode
Each cell in the instruction format diagram represents a single **8-bit byte**. The
instruction's mnemonic is its name. Its opcode is its numeric representation and is
given in both decimal and hexadecimal forms. Only the numeric representation is
actually present in the Epoch Virtual Machine code in a class file.

### "Operands"
Keep in mind that there are "operands" generated at compile time and embedded
within Epoch Virtual Machine instructions, as well as "operands" calculated at run
time and supplied on the operand stack. Although they are supplied from several
different areas, all these operands represent the same thing: values to be operated
upon by the Epoch Virtual Machine instruction being executed.

By implicitly taking many of its operands from its operand stack, rather than representing them
explicitly in its compiled code as additional operand bytes, register numbers, etc.,
the Epoch Virtual Machine's code stays compact.

### Instruction Family
Some instructions are presented as members of a family of related instructions
sharing a single description, format, and operand stack diagram. As such, a family
of instructions includes several opcodes and opcode mnemonics; only the family
mnemonic appears in the instruction format diagram, and a separate forms line
lists all member mnemonics and opcodes.
For example, the Forms line for the `const16_<l>` family of instructions,
giving mnemonic and opcode information for the two instructions in that family
(`const16_0` and `const16_1`), is
```
const16_0 = 9 (0x9)
const16_1 = 10 (0xa)
```

### Operand Stack Diagram
In the description of the Epoch Virtual Machine instructions, the effect of an
instruction's execution on the operand stack of the current frame is represented textually,
with the stack growing from left to right and each value represented separately. Thus,

```
..., value1, value2 ->
..., result
```

shows an operation that begins by having `value2` on top of the operand stack with
`value1` just beneath it.

As a result of the execution of the instruction, `value1` and `value2` are popped
from the operand stack and replaced by `result` value, which has been calculated
by the instruction. The remainder of the operand stack, represented
by an ellipsis (...), is unaffected by the instruction's execution.

Each value regardless of theirs' type are equally represented by a single entry
on the operand stack.
