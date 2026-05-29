# Proxy Pattern

> Structural Pattern

> **Gof**
>
> Provide a surrogate or placeholder for another object to control access to it.

> **Refactoring guru**
>
> **Proxy** is a structural design pattern that lets you provide a substitute or placeholder for another object. A proxy controls access to the original object, allowing you to perform something either before or after the request gets through to the original object.

The `Proxy Pattern` extends the functionality of an existing class by creating a proxy class. The proxy class maintains the same interface as the original class. Its main purpose is to add additional behavior during the access process without changing the interface.

> Typically, it directly implements all the interfaces of the original class.

It is suitable for extending functionality in later stages of development, such as:
- Lazy loading
- Caching results
- Post-loading behavior
Any additional functionality can be incorporated as needed.

### References
- [Difference from the Adapter Pattern](../README.md#the-difference-between-mediator-pattern-and-adapter-pattern)
