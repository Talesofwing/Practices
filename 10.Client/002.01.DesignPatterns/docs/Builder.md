# Builder Pattern

> Creational Pattern

> **Gof**
>
> Separate the construction of a complex object from its representation so that the same construction process can create different representations.

> **Refactoring guru**
>
> **Builder** is a creational design pattern that lets you construct complex objects step by step. The pattern allows you to produce different types and representations of an object using the same construction code.

Used to create complex objects. When an object has multiple configurable parameters and not all of them are required, the Builder Pattern can simplify the initialization process.

Additionally, a Director class can be created to manage the construction process. The client only needs to call the APIs provided by the Director to obtain the object.

Three types of Builder usage:

- One-time Builder
	```csharp
	Product product1 = new Product.Builder().setName("A").setPrice(100).build();
	```

- Reusable Builder
	```csharp
	public class ProductBuilder {
	   private String name;
	   private int price;

	   public ProductBuilder setName(String name) {
			this.name = name;
	      return this;
	    }

	   public ProductBuilder setPrice(int price) {
		    this.price = price;
		    return this;
		}

		public Product build() {
			return new Product(name, price);
		}

		public ProductBuilder reset() {
			this.name = null;
			this.price = 0;
			return this;
		}
	}
	```

- Reference-holding Builder
	```csharp
	public class ConfigBuilder {
		private Config config;

		public ConfigBuilder(Config config) {
	      this.config = config;
	   }

	   public ConfigBuilder setTimeout(int timeout) {
		   config.setTimeout(timeout);
		   return this;
		}

		public Config build() {
			return config;
		}
	}
	```

### References

- [Difference from the Abstract Factory Pattern](../README.md#the-difference-between-abstract-factory-pattern-and-builder-pattern)
