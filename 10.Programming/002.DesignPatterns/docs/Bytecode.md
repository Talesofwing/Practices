# Update Method

> Game Programming Pattern
>
> Give behavior the flexibility of data by encoding it as instructions for a virtual machine.

Very similar to the [Interpreter Pattern](../docs/Interpreter.md), but with an added layer of VM + IR, like C#/Java, where a VM executes the corresponding IR instructions.

The Lua scripting language is also a kind of `Bytecode` implementation: it is interpreted by a VM and executes the corresponding behavior.

`Bytecode` is precompiled into a linear sequence of instructions, so execution only requires sequential interpretation of instructions. Its core is:
- Tree structure → linear instruction sequence
- String identifiers → numeric codes
- Recursive calls → loops + stack

The example code:
```python
# Bytecode
opcodes = [0x00, 0x01, 0x00, 0x02]  # pre-translated
dispatch = [attack, run, attack, heal]  # array of function pointers

for op in opcodes:
    dispatch[op]()  # direct indexing, very fast

# Interpreter Pattern
# This works, but is less efficient
commands = ["Attack", "Run", "Attack", "Heal"]

for cmd in commands:
    if cmd == "Attack":  # string comparison each time
        attack()
    elif cmd == "Run":  # linear search
        run()
    # ...
```

### References
- [Difference from the Interpreter Pattern](../README.md#the-difference-between-bytecode-and-interpreter)
