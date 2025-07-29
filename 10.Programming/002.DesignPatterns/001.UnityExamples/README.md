# 001.UnityExamples

> Unity 2022.3.62f1

This example is created using Unity. The main purpose is to illustrate the explanation in conjunction with examples related to game development.

### Contents
#### Behavioral Patterns
1. [Command](docs/Command.md)
2. [Observer](docs/Observer.md)

#### Structural Patterns
1. [Flyweight](docs/Flyweight.md)

### Notes

#### The difference between Command and Strategy

The Strategy Pattern is designed for interchangeable behaviors. For example:
- Attack: different attack methods
- Movement: different movement types

In other words, the same type can have different strategies to execute varying behaviors.

The Command Pattern is intended to encapsulate requests, operations, or actions, which may not necessarily be interchangeable. For example:

- Button actions: a certain key may perform `Jump` or `Attack`

This allows dynamically switching to a different action.
