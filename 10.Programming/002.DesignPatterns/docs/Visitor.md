# Visitor Pattern

> Behavioral Pattern

> **Gof**
>
> Represent an operation to be performed on the elements of an object structure. Visitor lets you define a new operation without changing the classes of the elements on which it operates.

> **Refactoring guru**
>
> **Visitor** is a behavioral design pattern that lets you separate algorithms from the objects on which they operate.

The purpose of the `Visitor Pattern` is to separate algorithms from objects, and to use [double dispatch](https://en.wikipedia.org/wiki/Double_dispatch) to execute the correct operation based on both the element type and the visitor type.

For example, different objects (Shapes) have different rendering methods. In general, the client does not know which specific `Shape` it holds—such as `Circle`, `Cube`, etc.—and only holds a reference to the base class `Shape`. When passing it to the `Renderer`, without double dispatch, the Renderer would need to use `if` or `switch` statements to determine the type of the `Shape`. Using  [double dispatch](https://en.wikipedia.org/wiki/Double_dispatch) avoids such type checks.

This pattern is mainly used in situations where functionality needs to be frequently added to objects, allowing complex features to be introduced without making extensive changes to the object code.
