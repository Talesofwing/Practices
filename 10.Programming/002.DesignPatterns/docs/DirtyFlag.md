# Dirty Flag

> Game Programming Pattern
>
> Avoid unnecessary work by deferring it until the result is needed.

In simple terms, a dirty flag marks whether a change has occurred and defers the update until the moment the data is actually needed. The advantage is that it eliminates unnecessary computations and performs the update only on demand, which can be considered a form of lazy evaluation.

This is a typical optimization technique that trades space for time, since the system must retain previously computed results for later use. In game engines, this pattern is commonly applied in several areas:

- Transform

	When a change occurs, the transformation matrix must be recomputed.

- Rendering data

	When data changes, it must be re-bound or re-uploaded to the GPU.

Moreover, the flag does not have to be a bool; it can also be an int to indicate how many times an update is required.

In Unity’s example, this technique is implemented inside the `SaveSystem`. However, in practice it is unlikely to be used directly in a `SaveSystem`, since the game world typically changes frequently and needs to be saved. A more practical approach is to divide the save data into segments—for example, player data, terrain data, and so on—so that only the parts that have actually changed are written to disk. This reduces the amount of data saved each time and lowers CPU usage.
