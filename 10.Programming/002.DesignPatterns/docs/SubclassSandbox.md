# Subclass Sandbox

> Game Programming Pattern
>
> Define behavior in a subclass using a set of operations provided by its base class.

> When too many subclasses are used, a data-driven approach may be more suitable.

> The `Sandbox Method` refers to a method whose control flow is implemented by the subclass. The idea is that the subclass is allowed to freely combine logic within a controlled sandbox, but it cannot directly touch the base class’s internal implementation or system resources.

`Subclass Sandbox` typically relies on a “universal” base class, while subclasses either implement methods defined in the base class or make use of the helper methods provided by it, thereby reducing inheritance depth.

The advantage is that each subclass only couples with the base class, while all external coupling is handled by the base class in a centralized manner. This results in an architecture where the inheritance hierarchy is shallow but horizontally wide.

There are two main approaches:

- All required functions are implemented in the base class

	Subclasses only depend on the base class.

- Some functions remain in the subclasses

	Subclasses may still couple to external classes.

If many subclasses would otherwise need to couple with an external system, this pattern is advantageous: by moving the coupling into the base class’s provided operations, you centralize external dependencies. However, the base class may become larger and harder to maintain.

How to choose

- If only few subclasses need a certain feature, let them call the external system directly.

	However, if you want the operation to remain consistent across other subclasses, keep it in the base class.

- Methods that modify game state (e.g., character health) should be centralized in the base class for safety.

	In other words, integrate high-risk operations into base-provided functions for centralized management and easier maintenance.

- If a method merely forwards a call to an external system, letting subclasses call it directly can be simpler.

	Nonetheless, even simple forwarding can be useful—these base-provided methods often access state that the base class does not wish to expose directly to subclasses (e.g., references to external systems that subclasses don’t need to know about).

	```cpp
	// soundEngine is a variable in the base class that references the currently used SoundEngine instance. But don’t want the subclass to access the soundEngine directly.
	void playSound(int soundID) {
		soundEngine.Play(soundID);
	}
	```

Another way to reduce the burden on the base class is to return the instance instead of providing methods.
In this approach, the base class exposes the instance, and subclasses obtain it and directly call its API.

`Subclass Sandbox` is the opposite of the [Template Pattern](Template.md):
- [Template Pattern](Template.md): The base class controls the overall process, while subclasses provide the detailed implementations.
- `Subclass Sandbox`: The subclass controls the process, while the base class provides the necessary tools.

From the subclass’s perspective, the base class acts as a kind of [Facade Pattern](Facade.md):

- It hides most of the details of external systems.
- The subclass only needs to interact with the base class.

If the base class becomes too heavy in responsibility, other patterns—such as the [Component Pattern](Component.md) can be applied to reduce its duties.

### References
- [Difference from the Template Pattern](../README.md#the-difference-between-subclass-sandbox-and-template-method-pattern)
