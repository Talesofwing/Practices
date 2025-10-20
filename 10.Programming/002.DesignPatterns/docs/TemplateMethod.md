# Template Method Pattern

> **Gof**
>
> Define the skeleton of an algorithm in an operation, deferring some steps to subclasses. Template Method lets subclasses redefine certain steps of an algorithm without changing the algorithm’s structure.

> **Refactoring guru**
>
> **Template Method** is a behavioral design pattern that defines the skeleton of an algorithm in the superclass but lets subclasses override specific steps of the algorithm without changing its structure.

The purpose of the `Template method pattern` is to consolidate code that shares the same `logic`, `algorithm`, or `process` into a base class, while subclasses only need to implement their own specific functionalities, thereby reducing code duplication.

In other words, the base class provides the framework, and the actual implementation of each method within that framework is handled by the subclasses.

### References
- [Difference from the Factory Method Pattern](../README.md)
- [Difference from the Subclass Sandbox](../README.md#the-difference-between-subclass-sandbox-and-template)
