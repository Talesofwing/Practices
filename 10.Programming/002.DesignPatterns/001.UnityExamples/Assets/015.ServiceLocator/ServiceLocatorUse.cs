using UnityEngine;

namespace DesignPattern.ServiceLocator
{
	public class ServiceLocatorUse : MonoBehaviour
	{
		private void Awake()
		{
			ServiceLocator.Register<IStorage>(new LocalStorage());
		}

		private void Start()
		{
			IStorage storage = ServiceLocator.Resolve<IStorage>();
			storage.Save("data");
			Debug.Log(storage.Load());
		}
	}
}
