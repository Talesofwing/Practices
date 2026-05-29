# Update Method

> Game Programming Pattern
>
> Simulate a collection of independent objects by telling each to process one frame of behavior at a time.

A scheme where each object can update independently, with the specific logic implemented by the object itself, while the [Game Loop](GameLoop.md) is only responsible for calling `Update()`.

> This is essentially Unity’s `Update()`.

### Issues with Update
#### Order of state updates

Update is a linear operation, which may cause problems.

Suppose there are two objects, A and B. In a given frame, A is updated first and then B. If B needs to interact with A, it will receive A’s updated state for that frame instead of its original state.

In this scenario, the [Double Buffer](DoubleBuffer.md) pattern can be used as a solution.

#### Additions and removals during iteration

Since Update typically iterates through a `List`, adding or removing elements during this iteration can cause issues.

#### Which class should contain the Update method?

- Entity (corresponds to Unity’s GameObject)
- Component (corresponds to Unity’s UnityEngine.Object)

#### How to handle inactive objects?

If a large number of objects are inactive, repeatedly calling their `Update()` wastes resources.

A common approach is to maintain two lists:
- All List and Active List
- Active List and Inactive List

By calling `Update()` only on objects in the `Active List`, you can significantly reduce unnecessary calls.
