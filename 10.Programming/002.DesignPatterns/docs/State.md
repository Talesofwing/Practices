# State Pattern

> Behavioral Pattern

> **Gof**
>
>  Allow an object to alter its behavior when its internal state changes. The object will appear to change its class.

> **Refactoring guru**
>
> **State** is a behavioral design pattern that allows an object to change the behavior when its internal state changes.

The problem with traditional state machines is that they often contain many `if` or `switch` statements. As the project grows larger, this kind of implementation can easily become disastrous.

> Of course, it is case by case. For example, in a generic state machine, it is not always possible to design each state as a separate class.

To reduce the number of `if` or `switch` statements, the `State Pattern` is a great choice. The `State Pattern` encapsulates variations into classes, thereby minimizing the use of `if` and `switch`. States can also change other states internally.

The actions an object executes are fully determined by its state, for example:
- Normal State: Normal Attack
- Angry State: Gravity Attack

### Advanced

The `State Pattern` has many variations and subtleties; for further learning, you can refer to the following resources.

- [Finite State Machine](https://en.wikipedia.org/wiki/Finite-state_machine)
- Hierarchical State Machine
- Pushdown Automata
- Behavior Trees
- Planning Systems

### References
- [Difference from the Strategy Pattern](../README.md#the-difference-between-state-pattern-and-strategy-pattern)
