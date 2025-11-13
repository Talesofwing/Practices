# Prototype Pattern

> Creational Pattern

> **Gof**
>
> Define an interface for creating an object, but let subclasses decide which class to instantiate. Factory Method lets a class defer instantiation to subclasses.

> **Refactoring guru**
>
> **Factory Method** is a creational design pattern that provides an interface for creating objects in a superclass, but allows subclasses to alter the type of objects that will be created.

Using factories allows the separation of "creation" and "concrete logic." Additionally, an [Object Pool](./ObjectPool.md) can be implemented within the factory.

The `Factory Method` reserves an interface for creation in the parent class, while the concrete creation is implemented by subclasses. It is similar to the [Template Method Pattern](./TemplateMethod.md).

Many designs start by using the `Factory Method Pattern` and later evolve into the [Abstract Factory Pattern](./AbstractFactory.md), [Prototype Pattern](./Prototype.md), or [Builder Pattern](./Builder.md), which are more complex but more flexible.

### References

- [Difference from the Template Method Pattern](../README.md#the-difference-between-template-method-pattern-and-factory-method-pattern)
- [Difference from the Abstract Factory Pattern](../README.md#the-difference-between-abstract-factory-pattern-and-factory-method-pattern)
