namespace DesignPattern.Adapter
{
	/// <summary>
	/// This is the 3rd party cloud service that we want to save and load data from.
	/// </summary>
	public class Cloud
	{
		public void Save(CloudData data) => UnityEngine.Debug.Log("Save data to cloud: " + data.Name);
		public CloudData Load() => new CloudData { Name = "data from cloud" };
	}
}
