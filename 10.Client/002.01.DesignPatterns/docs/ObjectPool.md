# Object Pool

> Game Programming Pattern
>
> Allow a single entity to span multiple domains without coupling the domains to each other.

In game development, frequent creation and destruction of objects can easily lead to memory fragmentation.

This can be mitigated by using an `Object Pool` to reuse memory and reduce fragmentation. The `Object Pool` maintains persistent references to objects and uses an `IsUsing` flag to manage object reuse.

- Users request objects from the `Object Pool`.

- The `Object Pool` returns an object with `IsUsing = false` from the pool and sets `IsUsing = true`.

	- If none are available, it either creates a new one or returns null.

- After the object is used, it is returned to the pool and marked `IsUsing = false` for future reuse.

This technique typically trades space for time and can reduce:

- Memory fragmentation

- The time spent on Allocate and Free operations.
