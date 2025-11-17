# Spatial Partition

> Game Programming Pattern
>
> Efficiently locate objects by storing them in a data structure organized by their positions.

In game worlds, it is often necessary to traverse entities within the scene. For example, finding the nearest target within an attack range to perform an attack. If you directly traverse and determine the closest target, the time complexity would be $O(n^2)$. This becomes very time-consuming in scenes with many entities. Therefore, spatial partitioning is needed to reduce the search count $n$

There are many methods for spatial partitioning, each suitable for different scenarios, such as:

- Grid
- Quadtree
- BSP (Binary Space Partitioning)
- k-d tree
- Bounding Volume Hierarchy (commonly used in ray tracing)

The choice of partitioning method should be based on the specific problem at hand.

In the example, 100,000 spheres are used, with grid cells sized 300x300. Without optimization, it takes `29ms`, while with optimization, it only takes `0ms`.

One point to note is that when using spatial partitioning for the search, only the nearest 9 grid cells are searched, so it is possible that some targets may not be found.
