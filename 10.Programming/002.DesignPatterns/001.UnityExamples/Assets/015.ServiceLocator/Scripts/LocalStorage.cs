namespace DesignPattern.ServiceLocator
{
	public class LocalStorage : IStorage
	{
		public void Save(string data)
		{
			UnityEngine.Debug.Log("Save data to local storage: " + data);
		}

		public string Load()
		{
			return "data from local storage";
		}
	}
}
