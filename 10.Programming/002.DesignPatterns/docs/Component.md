# Component

> Game Programming Pattern
>
> Allow a single entity to span multiple domains without coupling the domains to each other.

Just like the relationship between Unity’s `GameObject` and `Component`, components can be flexibly added to or removed from a `GameObject` to compose different functionalities.

Design Decision Issues
- How does an object obtain its components?
	- Created by the object itself
	- Provided by external code
- How do components communicate with each other? (There is no perfect solution)
	- Modifying the object's state (variables)
		- Other components that do not require that state can still access or modify it, which may cause confusion
		- Some compositions might not need certain states at all, leading to wasted memory
		- The calling order can cause issues—for example, rendering components called before movement components
		- Can be used for some shared states like position, size, etc.
	- Mutual references
		- Causes coupling
		- Easy and fast to implement
		- Components with strong references can reference each other directly
	- Via message mechanisms
		- Similar to Unity’s Broadcast function, notifying components in child objects to invoke certain methods
		- Slow and hard to debug
		- Suitable when no response or waiting is needed

### References

- [Difference from the Strategy Pattern](../README.md#the-difference-between-component-and-strategy-pattern)
