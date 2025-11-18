# Dependency Injection

> Dependency Injection is a technique whereby one object supplies the dependencies of another object.

`Dependency Injection(DI)` refers to the practice of "injecting" the resources or instances that an object depends on from the outside, rather than the object creating or managing its own dependencies. It is a concrete implementation of `Inversion of Control(IoC)`.

An `IoC` container is a framework or architectural component that supports DI. For example, the simplest `IoC` container can be implemented using a [Service Locator](./ServiceLocator.md). DI operations are performed externally.

There are generally three types of DI methods:

- Constructor Injection

	Dependencies are passed through the object's constructor parameters.

- Property Injection

	Dependencies are injected via the object's public properties.

- Interface Injection

	Dependencies are injected through a public interface implemented by the object.

In [Zenject](https://github.com/modesttree/Zenject), automatic injection is achieved using C# `Attributes` combined with `Reflection` features.

The benefits are:

- Reduced Coupling

	Users do not need to know the specific implementation types of dependencies; they only depend on abstract interfaces or base classes. This lowers coupling between modules, facilitating system scalability and maintenance.

- Increased Flexibility and Replaceability

	The underlying implementation can be easily replaced without affecting user code, allowing for convenient feature changes or system upgrades based on requirements.

- Facilitated Unit Testing

	By injecting mock objects, testing becomes more effective, improving the independence and accuracy of tests.

- Improved Code Readability and Maintainability

	Dependency relationships are explicitly expressed, reducing implicit dependencies and making the code structure clearer.

- Supports Inversion of Control (IoC)

	The creation and management of dependencies are delegated to an external container, allowing users to focus on business logic and enhancing the overall clarity and consistency of the system architecture.
