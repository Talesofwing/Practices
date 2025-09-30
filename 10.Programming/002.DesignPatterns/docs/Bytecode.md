# Update Method

> Game Programming Pattern
>
> Give behavior the flexibility of data by encoding it as instructions for a virtual machine.

Very similar to the [Interpreter Pattern](../docs/Interpreter.md).

The Lua scripting language is also a form of `Bytecode` implementation; it can be compiled with `luac`, reducing the runtime overhead of parsing and analysis.

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
