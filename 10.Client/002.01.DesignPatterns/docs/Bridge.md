# Bridge Pattern

> Structural Pattern

> **Gof**
>
> Decouple an abstraction from its implementation so that the two can vary independently.

> **Refactoring guru**
>
> **Bridge** is a structural design pattern that lets you split a large class or a set of closely related classes into two separate hierarchies—abstraction and implementation—which can be developed independently of each other.

The `Bridge Pattern` is implemented by dividing a class into two parts:
- Abstraction
- Implementation

This means separating the abstraction from the implementation. The term “abstraction” here does not refer to the `abstract class` concept in programming languages; rather, Abstraction in this context is a broader, more general concept.

When a class becomes overly complex, it is often because it handles multiple dimensions of functionality. For example, in a rendering engine, we can separate responsibilities into:
- API: such as OpenGL, Direct3D, etc.
- Renderer: the engine logic that utilizes the underlying API

By separating these two, both can evolve independently. The `Renderer` can reference the base `API` interface, where:
- Abstraction refers to the `Renderer`
- Implementation refers to the `API`

Therefore, Abstraction is not limited to an `abstract class` or `abstract method`—it is a broader architectural concept.
This idea is somewhat similar to the [Adapter Pattern](./Adapter.md), where the `Adapter` handles compatibility issues.

### References
- [Difference from the Strategy Pattern](../README.md#the-difference-between-adapter-pattern-and-strategy-pattern)
- [Difference from the Adapter Pattern](../README.md#the-difference-between-adapter-pattern-and-adapter-pattern)
