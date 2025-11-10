# Observer Pattern

> Behavioral Pattern

> **Gof**
>
> Define a one-to-many dependency between objects so that when one object changes state, all its dependents are notified and updated automatically.

> **Refactoring guru**
>
> **Observer** is a behavioral design pattern that lets you define a subscription mechanism to notify multiple objects about any events that happen to the object they’re observing.

The purpose of the `Observer pattern` is decouple the communication between objects and facilitate a one-to-many relationship, where one subject notifies multiple observers of state changes.

In the traditional `Observer Pattern`, observers are typically registered as concrete instances. However, in modern development, functions are often used as notification targets — for example, `event Action` in C#. This approach is commonly referred to as the `event/delegate pattern`.

```csharp
// Calling an instance API
private List<IListener> Listeners = new();
Listeners.Add(Listener);
foreach (var l in Listeners) {
	l.OnNotify();
}

// Calling a function
public event Action<bool> SomeEvent;
bool someCondition = true;
SomeEvent?.Invoke(someCondition);
```

However, this pattern also has some drawbacks:
- Uncontrolled execution order: This can be mitigated by introducing a priority-based ordering mechanism.
- Difficult to debug and trace: This issue is generally hard to solve effectively.

The structure is as follows:
- Subject: acts as the event publisher
- Object: acts as the listener

In the example, a [Mediator pattern](Mediator.md) is also introduced to build an `EventBus`:
- EventBus: the actual event system
- IEvent: used to hold the data of each event
- Observer: registers events using the `EventBus`
- Publisher: publishes events using the `EventBus`

### References
- [Difference from the Event Queue](../README.md#the-difference-between-event-queue-and-observer-pattern)
