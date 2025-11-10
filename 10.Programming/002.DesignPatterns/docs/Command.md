# Command Pattern

> Behavioral Pattern

> **Gof**
>
> Encapsulate a request as an object, thereby letting users parameterize clients with different requests, queue or log requests, and support undoable operations.

> **Refactoring guru**
>
> **Command** is a behavioral design pattern that turns a request into a stand-alone object that contains all information about the request. This transformation lets you pass requests as a method arguments, delay or queue a request’s execution, and support undoable operations

The purpose of the `Command Pattern` is to encapsulate a `request` as an object, thereby allowing different requests, queues, or logs to parameterize other objects. This pattern generally supports undoable operations.

In general, the `Invoker` does not create the `Command`; instead, the `Command` is created by the `Client(Command User)` and then passed to the `Invoker` for execution.

### References
- [Difference from the Strategy Pattern](../README.md#the-difference-between-command-pattern-and-strategy-pattern)
- [Difference from the Event Queue](../README.md#the-difference-between-event-queue-and-command-pattern)
