# Strategy Pattern

> Behavioral Pattern

> **Gof**
>
> Define a family of algorithms, encapsulate each one, and make them interchangeable. Strategy lets the algorithm vary independently from clients that use it.

> **Refactoring guru**
>
> **Strategy** is a behavioral design pattern that lets you define a family of algorithms, put each of them into a separate class, and make their objects interchangeable.

The purpose of the `Strategy Pattern` is to abstract behavior, allowing it to be switched freely while hiding its internal details.

For example, in game development, a character may have the following behaviors:
- Attack
- Move
- …

These behaviors can have many different types, such as:
- Ranged attack, melee attack, …
- No movement, flying, burrowing, …

Each character has different capabilities.

In modern development, since most programming languages support functional types, we can directly use functions to replace traditional strategy classes.
```cpp
class Context {
private:
    std::function<int(int, int)> strategy_;
public:
    Context(std::function<int(int, int)> strategy) : strategy_(std::move(strategy)) {}
    int execute(int a, int b) const {
        return strategy_(a, b);
    }
};

int main() {
    // Use lambda to define strategy directly
    Context addContext([](int a, int b) { return a + b; });
    std::cout << addContext.execute(3, 5) << std::endl;  // 8

    Context multiplyContext([](int a, int b) { return a * b; });
    std::cout << multiplyContext.execute(3, 5) << std::endl;  // 15
}
```
If the strategy itself has complex internal logic, requires state, or involves multi-step behavior, it is still recommended to use classes rather than lambdas.

### References
- [Difference from the State Pattern](../README.md#the-difference-between-state-and-strategy)
- [Difference from the Command Pattern](../README.md#the-difference-between-command-and-strategy)
- [Difference from the Component Pattern](../README.md#the-difference-between-strategy-and-component)
