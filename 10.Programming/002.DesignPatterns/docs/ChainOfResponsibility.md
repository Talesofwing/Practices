# State Pattern

> Behavioral Pattern

> **Gof**
>
>  Avoid coupling the sender of a request to its receiver by giving more than one project a chance to handle the request. Chain the receiving objects and pass the request along the chain until an object handles it.

> **Refactoring guru**
>
> **Chain of Responsibility** is a behavioral design pattern that lets you pass requests along a chain of handlers. Upon receiving a request, each handler decides either to process the request or to pass it to the next handler in the chain.

Construct a chain of handlers for a request according to a specified order. The request will be evaluated by the handlers in the chain in the following way:

Check whether it can be handled:
- If yes, handle it and exit (in a skill system, it may not exit immediately).
- If not, pass it to the next handler.
This continues until the last handler in the chain.

> The key is a chain of responsibility, where each handler in the chain is responsible for processing the event.
