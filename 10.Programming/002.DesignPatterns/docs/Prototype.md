# Prototype Pattern

> Creational Pattern

> **Gof**
>
> Specify the kinds of objects to create using a prototypical instance, and create new objects by copying this prototype.

> **Refactoring guru**
>
> **Prototype** is a creational design pattern that lets you copy existing objects without making your code dependent on their classes.

The purpose of the `Prototype Pattern` is to define the type of object to be created through a prototypical instance, and to generate new objects by copying this prototype, thereby reducing creation costs and decoupling the system from concrete classes and complex construction processes.

When using the `Prototype Pattern`, it’s important to consider the distinction between `shallow copy` and `deep copy`.

In C#, `ICloneable` is considered to follow the `Prototype Pattern`. However, it is explicitly recommended not to use it, since it does not specify whether the copy is `shallow` or `deep`.

Additionally, in Unity, `Prefab` is an application of the `Prototype Pattern`.

In modern development, however, cloning is more often implemented through serialization.

> Implementing `Clone()` can be quite complicated.
