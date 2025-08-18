using UnityEngine;

namespace DesignPattern.Singleton
{
	public class ResourceManager
	{
		private static ResourceManager _instance = new();

		// Avoid using lazy loading.
		// public static ResourceManager Instance => _instance ??= new ResourceManager();
		public static ResourceManager Instance => _instance;

		private ResourceManager() { }

		public void LoadResource()
		{
			Debug.Log("Load Resource");
		}
	}
}
