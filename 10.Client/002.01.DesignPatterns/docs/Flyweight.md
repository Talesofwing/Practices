# Flyweight Pattern

> Structural Pattern

> **Gof**
>
> Use sharing to support large numbers of fine-grained objects efficiently.

> **Refactoring guru**
>
> **Flyweight** is a structural design pattern that allows programs to support vast quantities of objects by keeping their memory consumption low.

The purpose of the `Flyweight Pattern` is to reduce memory usage by sharing data (Intrinsic state).

Flyweight is divided into two parts:
- Intrinsic: the shared data
- Extrinsic: the independent data

In Unity, `ScriptableObject` is an example of the `Flyweight Pattern` in practice, as it enables data sharing. In contrast, `Prefab` is not an example of Flyweight, because each instantiated `Prefab` creates a separate, independent object rather than sharing data.

Additionally, the concept behind `GPU Instancing` is also consistent with the `Flyweight Pattern`.

In game development, configuration data can also be understood as an implementation of the `Flyweight Pattern`. Each instance object points to a single, unique configuration data rather than holding its own copy.

### References
- [Difference from the Type Object](../README.md#the-difference-between-type-object-and-flyweight-pattern)
