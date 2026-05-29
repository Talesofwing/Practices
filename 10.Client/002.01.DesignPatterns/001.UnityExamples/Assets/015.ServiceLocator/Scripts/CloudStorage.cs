namespace DesignPattern.ServiceLocator
{
	public class CloudStorage : IStorage
	{
		public void Save(string data)
		{
			UnityEngine.Debug.Log("Save data to cloud storage: " + data);
		}

		public string Load()
		{
			return "data from cloud storage";
		}
	}
}
