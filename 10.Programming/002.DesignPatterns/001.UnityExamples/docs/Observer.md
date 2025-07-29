# Observer Pattern

The purpose of the `Observer pattern` is decouple the communication between objects and facilitate a one-to-many relationship, where one subject notifies multiple observers of state changes.

In modern implementations, `observers` are generally not `instances` but `functions`.

The structure is as follows:
- Subject: acts as the event publisher
- Object: acts as the listener

In the example, a [Mediator pattern](Mediator.md) is also introduced to build an `EventBus`:
- EventBus: the actual event system
- IEvent: used to hold the data of each event
- Observer: registers events using the `EventBus`
- Publisher: publishes events using the `EventBus`
