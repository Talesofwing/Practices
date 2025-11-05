# Type Object

> Game Programming Pattern
>
> Allow the flexible creation of new “classes” by creating a single class, each instance of which represents a different type of object.

The purpose of the `Type Object` pattern is to reduce inheritance by defining a “type” object.

In the traditional approach, implementing behavior differences between types might rely on inheritance. For example, you could have Dragon and Orc both inherit from Monster and override attack and movement functions. This can lead to a large number of subclasses.

With a type object, you create a separate object that stores the concrete attributes of that type, such as:

- Health

- Attack power

- Attack type

- Defense type

- …

In the `Monster` class, you reference a specific type object and perform behavior based on the attributes stored in that object.

This is usually implemented using configuration tables, such as:

- Google Sheet

- Excel

> It can be simply understood as data-driven design.

### References

- [Difference from the Flyweight Pattern](../README.md#the-difference-between-type-object-and-flyweight-pattern)
