# Memento Pattern

> Behavioral Pattern

> **Gof**
>
> Without violating encapsulation, capture and externalize an object’s internal state so that the object can be restored to this state later.

> **Refactoring guru**
>
> **Memento** is a behavioral design pattern that lets you save and restore the previous state of an object without revealing the details of its implementation.

The purpose of the `Memento Pattern` is to preserve a certain state and restore it later. For example, in a game checkpoint, the game world’s state is saved and restored when the player dies.

The originator is responsible for creating and restoring snapshots.
- HP (health)
- Attack power
- Defense power
- ...

In game development, the `Memento Pattern` is rarely used directly. It is often replaced by alternatives such as:
- Serialization
- [Command Pattern](Command.md) + Undo Stack

The `Memento Pattern` can be applied to restore the state of small, self-contained objects. It is conceptually similar to the [Prototype Pattern](Prototype.md).

### References
- [Difference from the Prototype Pattern](../README.md#the-difference-between-memento-and-prototype)
