# Adapter

> Structural Pattern

> **Gof**
>
> Convert the interface of a class into another interface clients expect. Adapter lets classes work together that couldn’t otherwise because of incompatible interfaces.

> **Refactoring guru**
>
> **Adapter** is a structural design pattern that allows objects with incompatible interfaces to collaborate.

The purpose of the `Adapter Pattern` is to enable two incompatible components to work together.
For example, in game development, one of the cars in GTA is actually implemented as a person running underneath the vehicle — an unusual design that illustrates the need for adaptation between incompatible systems.

There are two common ways to implement an adapter:
- Composition-based: Implement all interfaces of the target class and hold a reference to an instance of the original class.
- Inheritance-based: Extend the original class and act as a subclass.

When working with an existing class where it’s inconvenient or impossible to directly add new methods, you can use the `Adapter Pattern` to add functionality. However, this approach requires that the class already exposes a well-defined public interface.
This approach is conceptually similar to the [Decorator Pattern](./Decorator.md)—see [Adapter vs. Decorator](../README.md#the-difference-between-adapter-pattern-and-decorator-pattern) for a detailed comparison.

The Adapter Pattern is typically used in the later stages of a project. At that point, new classes or third-party libraries may not integrate seamlessly with existing code. In such cases, the `Adapter Pattern` provides an elegant way to make them work together without major refactoring.
