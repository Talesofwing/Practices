# Command Pattern

The purpose of the Command Pattern is to encapsulate a `request` as an object, thereby allowing different requests, queues, or logs to parameterize other objects. This pattern generally supports undoable operations.

In general, the `Invoker` does not create the `Command`; instead, the `Command` is created by the `Client(Command User)` and then passed to the `Invoker` for execution.

In this example:
- Invoker: `CommandManager`
- Client: `CommandUse`

It also supports `undo` and `redo` operations.
	