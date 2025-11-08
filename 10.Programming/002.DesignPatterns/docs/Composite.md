# Composite Pattern

> Structural Pattern

> **Gof**
>
> Compose objects into tree structures to represent part-whole hierarchies. Composite lets clients treat individual objects and compositions of objects uniformly.

> **Refactoring guru**
>
> **Composite** is a structural design pattern that lets you compose objects into tree structures and then work with these structures as if they were individual objects.

The Part-Whole Hierarchy refers to a relationship that can be represented as a tree structure.
- Part: an individual element within the whole (e.g., a leaf node)
- Whole: a composite made up of multiple parts (e.g., multiple leaf nodes forming a parent node)

Users can operate on both single objects and collections of objects in a uniform way.

The main advantage is that you don’t need to care about the concrete class of each element in the tree. Whether an object is a leaf or a composite node, you can treat them uniformly through a shared interface.

A good example can be found in [Ray Tracing in One Weekend](https://raytracing.github.io/):
- hittable → Part
- hittable_list → Whole

Both are used in exactly the same way.

> However, the structure must be hierarchical (tree-shaped).

It can be perfectly combined with the [Visitor Pattern](./Visitor.md). The following is an example.

```csharp
using System;
using System.Collections.Generic;

abstract class FileSystemNode
{
    public string Name { get; }
    protected FileSystemNode(string name) => Name = name;

    public abstract void Accept(IVisitor visitor);
}

class File : FileSystemNode
{
    public int Size { get; }
    public File(string name, int size) : base(name) => Size = size;

    public override void Accept(IVisitor visitor)
    {
        visitor.Visit(this);
    }
}

class Directory : FileSystemNode
{
    private readonly List<FileSystemNode> _children = new();
    public Directory(string name) : base(name) { }

    public void Add(FileSystemNode node) => _children.Add(node);
    public IReadOnlyList<FileSystemNode> Children => _children;

    public override void Accept(IVisitor visitor)
    {
        visitor.Visit(this);
    }
}

interface IVisitor
{
    void Visit(File file);
    void Visit(Directory directory);
}

class SizeCalculatorVisitor : IVisitor
{
    public int TotalSize { get; private set; } = 0;

    public void Visit(File file)
    {
        TotalSize += file.Size;
    }

    public void Visit(Directory directory)
    {
        foreach (var child in directory.Children)
            child.Accept(this);
    }
}

class Program
{
    static void Main()
    {
        var root = new Directory("root");
        root.Add(new File("a.txt", 120));
        root.Add(new File("b.log", 200));

        var sub = new Directory("sub");
        sub.Add(new File("c.bin", 300));
        root.Add(sub);

        var calc = new SizeCalculatorVisitor();
        root.Accept(calc);

        Console.WriteLine($"Total size: {calc.TotalSize}");
    }
}
```
