# Service Locator

> Game Programming Pattern
>
> Provide a global point of access to a service without coupling users to the concrete class that implements it.

`Service Locator` is used to decouple components from concrete “services”.

For example, in game development, there is a need to use an `IStorageService`, which is mainly responsible for the “persistent storage” functionality. By constructing a service container and using `Dependency Injection(DI)`, services can be registered to the container at appropriate times. This enables “service replacement” and “decoupling.” For example, there are:
- `CloudStorageService`
- `LocalStorageService`

In the `Bootstrap`, based on macros or certain conditions, the corresponding service can be switched at any time.

```csharp
public interface IStorageService {
	object Load();
	void Save(object saveData) ;
}

public class CloudStorageService : IStorageService {
	public void Save(object saveData) {  }
	public object Load() {  }
}

public class LocalStorageService : IStorageService {
	public void Save(object saveData) { }
	public object Load() { }
}

public static class ServiceLocator {
	private static readonly Dictionary<Type, object> services = new Dictionary<Type, object>();

	public static void Register<TService> (TService service) {
		services[typeof(T)] = service;
	}

	public static T Get<TService> (TService service) {
		return (T)services[typeof(T)];
	}
}

public class Bootstrap : MonoBehaviour {
	private void Start() {
		if (useCloudStorage) {
			Services.Register<IStorageService>(new CloudStorageService);
		} else {
			Services.Register<IStorageService>(new LocalStorageService);
		}
	}
}

public void GameDataHandler() {
	public void SaveGameData(object saveData) {
		Services.Get<IStorageService>().Save(saveData);
	}

	public object LoadGameData() {
		return Services.Get<IStorageService>().Load();
	}
}
```

Service registration methods:
- External code registration
- Compile-time binding
	```cpp
	class Locator {
	pulbic:
		static Audio& getAudio() { return _audioService; }

	private:
		#if DEBUG
			static DebugAudio _audioService;
		#else
			static ReleaseAudio _audioService;
		#endif
	}
	```
- Runtime configuration

### References
- [Service Locator パターンについて](https://qiita.com/tassi-yuzukko/items/a81a7b9aaa42198df689)
