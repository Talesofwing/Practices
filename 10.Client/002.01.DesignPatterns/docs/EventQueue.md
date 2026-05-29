# Event Queue

> Game Programming Pattern
>
> Decouple when a message or event is sent from when it is processed.

If your only goal is to decouple the message sender from the receiver, patterns such as the [Observer Pattern](./Observer.md) or the [Command Pattern](./Command.md) can achieve this with much lower complexity.
You only need to introduce a queue when you want to decouple things in time.

However, because of this temporal decoupling, the sender cannot receive an immediate response.
If a response is required, an asynchronous mechanism must also be introduced.
The main issues that arise with asynchronous processing include:
- Events that require immediate feedback
- The need to preserve the state at the time the event occurred

Additionally, various issues may appear when handling events:
- Should identical events be merged?
- And so on.

When calling `AddEvent`, you can handle it differently depending on your requirements.(This is also one reason why different subsystems may each have their own Event Queue. <-Author think)

When creating a queue, you can choose among data structures such as:
- Linked list
- Circular array

Conceptual distinction between Event and Message (Request):
- An event represents something that has already happened.
- A message represents a request for something to happen.

In short, the `Event Queue` can be thought of as a hybrid between the [Observer Pattern](./Observer.md) and the [Command Pattern](./Command.md).

### References

- [Difference from the Observer Pattern](../README.md#the-difference-between-event-queue-and-observer-pattern)
- [Difference from the Command Pattern](../README.md#the-difference-between-event-queue-and-command-pattern)
