# Iterator

> Behavioral Pattern

> **Gof**
>
>  Define an object that encapsulates how a set of objects interact. Mediator promotes loose coupling by keeping objects from referring to each other explicitly, and it lets you vary their interaction independently.

> **Refactoring guru**
>
> **Mediator** is a behavioral design pattern that lets you reduce chaotic dependencies between objects. The pattern restricts direct communications between the objects and forces them to collaborate only via a mediator object.

The main goal is to reduce coupling between components by using a unified `Mediator` to manage interactions. It is similar to the [Facade Pattern](Facade.md), but the `Mediator` includes additional logic.

In the [MVC](https://en.wikipedia.org/wiki/Model%E2%80%93view%E2%80%93controller) architecture for UI frameworks, the `Controller` serves as the `Mediator`. The `Controller` manages all UI interactions—UI elements do not communicate directly with each other and are unaware of one another’s existence. All interactions go through the Controller.
- Interaction between UI elements such as buttons and the `Controller` is typically implemented using the [Observer Pattern](Observer.md).

In game development, interactions between entities can also be handled by a `Mediator`. For example, a `CombatSystem` acts as a `Mediator` when an entity performs an attack. The `CombatSystem` manages:
- Target selection
- Attack range
- Damage calculation
- Applying damage to the target

This design reduces the interaction logic between entities and makes it easier to control and maintain the combat flow.

### References
- [Difference from the Facade Pattern](../README.md#the-difference-between-mediator-and-facade)
