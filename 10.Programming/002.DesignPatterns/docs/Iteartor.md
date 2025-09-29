# Iterator

> Behavioral Pattern

> **Gof**
>
>  Provide a way to access the elements of an aggregate object sequentially without exposing its underlyling representation.

> **Refactoring guru**
>
> **Iterator** is a behavioral design pattern that lets you traverse elements of a collection without exposing its underlying representation (list, stack, tree, etc.).

An `iterator` mainly encapsulates the “traversal” operation, allowing users to traverse a container without worrying about its internal implementation. Using an `iterator`, one can traverse different containers in a uniform way, and it has the following characteristics:
- Each `iterator` can traverse the same container independently, as each `iterator` maintains its own state.
- An `iterator` can pause the traversal and retain its state; when needed, it can resume from where it was paused.

In C#, `IEnumerator` and `IEnumerable` serve as implementations of the `Iterator pattern`.
In C++’s STL, iterators are mainly implemented using templates.
