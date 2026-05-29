# Singleton Pattern

> Creational Pattern

> **Gof**
>
> Ensure a class has only one instance, and provide a global point of access to it.

> **Refactoring guru**
>
> **Singleton** is a creational design pattern that lets you ensure that a class has only one instance, while providing a global access point to this instance.

### Key points

1. Restricting a class to one instance
2. Providing a global point of access

> Violates the Single Responsibility Principle

### Advantages

1. Lazy Initialization

	Resources such as CPU and memory are only used when needed.

2. Inheritance

	Technically possible, but it almost never aligns with the original intent of the Singleton; therefore, not recommended in practice.

3. Runtime Initialization with Controllable Order

	Unlike static classes where the initialization order is uncontrollable, a Singleton can be initialized at runtime, making dependency management easier.

### Disadvantages

1. Global Variable Nature

	- Makes the code harder to understand and debug
	- Increases coupling
	- Not concurrency-friendly

2. Difficult to Modify Later

	As projects grow, a Singleton becomes increasingly hard to refactor.

3. Loss of Control with Lazy Initialization
	Developers cannot precisely control when the initialization occurs. For example, heap memory management cannot be fine-tuned.

	In large systems, this may cause stalls at critical moments—for instance, when the sound system is initialized during battle, causing a noticeable pause.

### Alternatives to `Singleton`

1. Service Locator Pattern

2. Static Class

3. Dependency Passing (Parameter Injection)

4. Subclass Sandbox Pattern (using static variables from parent classes)

> In summary, the further a project progresses, the harder it becomes to modify a Singleton. However, Singleton is not inherently unusable—it just needs to be applied cautiously and never overused.

### References

- [Difference from the Static Class](../README.md#the-difference-between-singleton-pattern-and-static-class)
