# Double Buffer

> Game Programming Pattern
> Cause a series of sequential operations to appear instantaneous or simultaneous.

It is mainly used to unify behavior. For example, in rendering, the commonly used `double buffering`. The core idea is to split the act of `changing state` into two steps:
- updating the state
- swapping the state

in order to achieve consistency of behavior.

When switching between buffers, there are generally two approaches:
- pointer swapping
- memory copying

Each comes with its own issues. `Pointer swapping` can be done very quickly, but it discards the data in the previous buffer, and external code cannot persistently hold the correct buffer pointer. In rendering, if one wants to implement `motion blur`, the buffer data from previous frames is required.

On the other hand, the main problem with `memory copying` is the performance cost during the copy.
