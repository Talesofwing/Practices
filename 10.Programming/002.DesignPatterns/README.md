# Design Patterns

Whether in team development or solo development, clean and elegant code is always pleasing to the eye. Moreover, both game development and application development are ongoing processes. If the code architecture is not well designed, it will cause many problems in subsequent updates and development. Therefore, learning **Design Patterns** is an important task.

This chapter will describe the uses of each pattern with practical examples from game development. In addition, The chapter will provide personal insights, as well as some difficulties and thoughts encountered during the learning process, all of which will be described in a straightforward manner.

### Contents
#### Behavioral Patterns
1. [Command](docs/Command.md)
2. [Observer](docs/Observer.md)
3. [State](docs/State.md)

#### Structural Patterns
1. [Flyweight](docs/Flyweight.md)

#### Creational Patterns
1. [Prototype](docs/Prototype.md)
2. [Singleton](docs/Singleton.md)

#### Game Programming Patterns
1. [Double Buffer](docs/DoubleBuffer.md)
2. [GameLoop](docs/GameLoop.md)

### Notes

#### The difference between [Command](docs/Command.md) and [Strategy](docs/Strategy.md)

The [Strategy Pattern](docs/Strategy.md) is designed for interchangeable behaviors. For example:
- Attack: different attack methods
- Movement: different movement types

In other words, the same type can have different strategies to execute varying behaviors.

The [Command Pattern](docs/Command.md) is intended to encapsulate requests, operations, or actions, which may not necessarily be interchangeable. For example:

- Button actions: a certain key may perform `Jump` or `Attack`

This allows dynamically switching to a different action.

#### The difference between [State](docs/State.md) and [Strategy](docs/Strategy.md)

The granularity of [State Pattern](docs/State.md) is usually larger; a concrete state not only contains the implementation of certain behaviors, but may also include the logic for switching to other states. In addition, a single state may integrate multiple behaviors.

For example, the "Running" state of an elevator may include:
- moving up and down
- stopping
- opening doors

and it may switch to the `Idle` or `Maintenance` state depending on conditions.

The granularity of [Strategy Pattern](docs/Strategy.md) is usually smaller; each strategy only encapsulates one algorithm or performs a single task. The Context can choose different strategies at runtime, but the strategies are independent of each other and will not change the Context’s state.

For example, a sorting Context can choose between `Quick Sort`, `Merge Sort`, etc. Each strategy is single-purpose and independent.

> In short, the [State Pattern](docs/State.md) is like a less constrained version of the [Strategy Pattern](docs/Strategy). States are not independent from each other and can change the Context’s state.

### References
- [REFACTORING GURU](https://refactoring.guru/)
- [Game Programming Patterns](https://gameprogrammingpatterns.com/)
