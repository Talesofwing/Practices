# Design Patterns

Whether in team development or solo development, clean and elegant code is always pleasing to the eye. Moreover, both game development and application development are ongoing processes. If the code architecture is not well designed, it will cause many problems in subsequent updates and development. Therefore, learning **Design Patterns** is an important task.

> Design patterns not only describe code structures but also convey the underlying design intentions and the problems they aim to solve.
>
> Therefore, understanding their core concepts is the key to truly mastering design patterns.
>
> In addition, design patterns are merely guidelines and recommendations, not concrete solutions, and should be applied flexibly.

### Contents
#### Behavioral Patterns
1. [Command](docs/Command.md)
2. [Observer](docs/Observer.md)
3. [State](docs/State.md)
4. [Chain of Responsibility](docs/ChainOfResponsibility.md)
5. [Iteartor](docs/Iteartor.md)
6. [Mediator](docs/Mediator.md)
7. [Memento](docs/Memento.md)
8. [Strategy](docs/Strategy.md)
9. [TemplateMethod](docs/TemplateMethod.md)
10. [Visitor](docs/Visitor.md)

#### Structural Patterns
1. [Flyweight](docs/Flyweight.md)
2. [Adapter](docs/Adapter.md)
3. [Bridge](docs/Bridge.md)
4. [Composite](docs/Composite.md)
5. [Decorator](docs/Decorator.md)
6. [Facade](docs/Facade.md)

#### Creational Patterns
1. [Prototype](docs/Prototype.md)
2. [Singleton](docs/Singleton.md)

#### Game Programming Patterns
##### Sequencing Patterns
1. [Double Buffer](docs/DoubleBuffer.md)
2. [GameLoop](docs/GameLoop.md)
3. [Update Method](docs/UpdateMethod.md)

##### Behavioral Patterns
1. [Bytecode](docs/Bytecode.md)
2. [Subclass Sandbox](docs/SubclassSandbox.md)
3. [Type Object](docs/TypeObject.md)

### Notes

#### The difference between [Command](docs/Command.md) and [Strategy](docs/Strategy.md)

The [Strategy Pattern](docs/Strategy.md) is designed for interchangeable behaviors. For example:
- Attack: different attack methods
- Movement: different movement types

In other words, the same type can have different strategies to execute varying behaviors.

The [Command Pattern](docs/Command.md) is intended to encapsulate requests, operations, or actions, which may not necessarily be interchangeable. For example:

- Button actions: a certain key may perform `Jump` or `Attack`

This allows dynamically switching to a different action.

#### The difference between [Singleton](docs/Singleton.md) and `Static Class`

- Utility functions (stateless): Static Class
- Requires state + OOP features: Singleton
- For testing purposes: Avoid using Singleton; use [[Dependency Injection|DI]] instead


#### The difference between [State](docs/State.md) and [Strategy](docs/Strategy.md)

The granularity of [State Pattern](docs/State.md) is usually larger; a concrete state not only contains the implementation of certain behaviors, but may also include the logic for switching to other states. In addition, a single state may integrate multiple behaviors.

For example, the "Running" state of an elevator may include:
- moving up and down
- stopping
- opening doors

and it may switch to the `Idle` or `Maintenance` state depending on conditions.

The granularity of [Strategy Pattern](docs/Strategy.md) is usually smaller; each strategy only encapsulates one algorithm or performs a single task. The Context can choose different strategies at runtime, but the strategies are independent of each other and will not change the Context’s state.

For example, a sorting Context can choose between `Quick Sort`, `Merge Sort`, etc. Each strategy is single-purpose and independent.

> In short, the [State Pattern](docs/State.md) is like a less constrained version of the [Strategy Pattern](docs/Strategy). States are not independent from each other and can change the Context’s state.

#### The difference between [Bytecode](docs/Bytecode.md) and [Interpreter](docs/Interpreter.md)

Both are basically designed to solve the same problem, but their core implementations are different.

- Interpreter Pattern

	Each execution requires traversing the tree structure, and a large amount of syntax must be analyzed every time.

- Bytecode

	Precompiled into a linear sequence of instructions, execution only requires sequential interpretation of the instructions.

Bytecode moves the entire front-end compilation process ahead of time, generating an intermediate format that is more suitable for machine execution.

#### The difference between [Mediator](docs/Mediator.md) and [Facade](docs/Facade.md)

Both aim to reduce coupling between components, but their core purposes are different:

- Mediator Pattern

	Adds logic; components cannot interact directly and must communicate through the Mediator.

- Facade Pattern

	Provides a simplified interface without changing the underlying logic; components can still interact directly and are unaware of the Facade’s existence.

#### The difference between [Subclass Sandbox](docs/SubclassSandbox.md) and [Template](docs/Template.md)

Both deal with the relationship between base classes and subclasses.

- Subclass Sandbox

	The algorithm’s skeleton is implemented by the subclass, while the base class provides a set of protected utility methods that the subclass can safely use. This encapsulates shared functionality within the base class, allowing subclasses to use it without modifying the base class’s behavior.

	Example: The attack flow is implemented by the subclass, while the functions used during the attack are provided by the base class.

- Template Pattern

	The algorithm’s skeleton is implemented by the base class, and each step of the skeleton is implemented or overridden by subclasses. This ensures that the overall flow remains controlled and cannot be arbitrarily modified.

	Example: The attack flow is implemented by the base class, while each part of the attack flow is implemented by the subclasses.

In practice, both patterns can be used together.

#### The difference between [Memento](docs/Memento.md) and [Prototype](docs/Prototype.md)

Both can “save the state of an object” and “restore it later.”

- Memento Pattern

	Saves a snapshot of the state for later restoration.

- Prototype Pattern

	Creates a new instance.

#### The difference between [Type Object](docs/TypeObject.md) and [Flyweight Pattern](docs/Flyweight.md)

Both patterns involve separating an object’s data.

- Type Object

	Reduces the number of subclasses by using another “object” to represent the concrete object type. Basically, it’s pure data, such as `AttackType`, `MovementType`, `AttackPower`, etc. The concrete object then executes behavior according to this data.

- Flyweight Pattern

	Its core is storage optimization and it doesn’t require being “data-driven.” For example, GPU Instancing.

The two patterns can easily be unintentionally mixed together.

> Personal understanding
>
> When reading data from a config table (e.g., Monster), the data can exhibit characteristics of both patterns:

- Monsters of the same type hold the same data, so this data is shared → `Flyweight Pattern`

- The Monster’s type is defined by this data, such as attack style, movement style, attack speed… → `Type Object`

#### The difference between [Template Method](docs/TemplateMethod.md) and [Factory Method](docs/Factory.md)

The `Factory Method Pattern` can be described as a specialized form of the `Template Method Pattern`, specifically designed for object creation.

#### The difference between [Adapter Pattern](docs/Adapter.md) and [Decorator Pattern](docs/Decorator.md)

Both patterns can add new functionality to a class through inheritance, but their design philosophies and use cases are fundamentally different.

- Adapter Pattern

	Unifies different or incompatible interfaces by converting them into the format expected by the system.

- Decorator Pattern

	Does not convert interfaces; it simply extends the existing interface by adding new behaviors.

#### The difference between [Bridge Pattern](docs/Bridge.md) and [Strategy Pattern](docs/Strategy.md)

The `Bridge Pattern` can also be switched at runtime, making it structurally similar to the `Strategy Pattern`. However, while their structures are nearly identical, their core concepts and the problems they aim to solve are different.

- Bridge Pattern

	A structural pattern that separates "abstraction" from "implementation" so that both can evolve independently.

- Strategy Pattern

	A behavioral pattern used to encapsulate interchangeable "algorithms" or "behaviors."

> In simple terms: the `Bridge Pattern` separates concerns at the system level, while the `Strategy Pattern` separates concerns at the behavioral level.

#### The difference between [Bridge Pattern](docs/Bridge.md) and [Adapter Pattern](docs/Adapter.md)

Both are structural patterns and share a similar code structure, but their core concepts and the problems they aim to solve are different.

- Bridge Pattern
	- Separates abstraction from implementation, allowing both to evolve independently.
	- Considered during the early design phase as an architectural separation.
	- Not concerned with compatibility issues.
- Adapter Pattern
	- Enables previously incompatible interfaces to work together.
	- Used to integrate third-party or legacy code.

#### The difference between [Component](docs/Component.md) and [Strategy Pattern](docs/Strategy.md)

Both involve the encapsulation and abstraction of behavior, but their core problems and use cases differ, with boundaries often overlapping.

- Component
	- Usually contains its own state and behavior, being more complete and independent, resembling a plug-and-play module.
	- Can be reused across multiple different objects, supporting dynamic composition and extension of functionality.
	- Focuses on the "composition of object capabilities," often representing a certain ability or attribute.
- Strategy Pattern
	- Typically encapsulates algorithmic behavior, containing little or no internal state.
	- Usually designed for behavior variations specific to a particular object and can be switched at runtime.
	- Emphasizes the "switching of algorithmic behavior," solving multiple strategy implementations for the same problem.

#### The difference between [Decorator](docs/Decorator.md) and [Chain of Responsibility Pattern](docs/ChainOfResponsibility.md)

Both rely on recursion to perform a sequence of actions. However, there are several key differences between them:

- Decorator Pattern

	A decorator does not interrupt the next step.

	It mainly serves to add functionality.

- Chain of Responsibility (CoR)

	CoR handles independent operations and can stop passing the request at any point.

	Its primary goal is to find an object capable of handling the request.

In short, the `Decorator` adds functionality, while the `CoR` aims to find the appropriate handler for an operation.

### References
- [REFACTORING GURU](https://refactoring.guru/)
- [Game Programming Patterns](https://gameprogrammingpatterns.com/)
