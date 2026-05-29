namespace DesignPattern.Adapter
{
	public class CloudAdapter
	{
		public void Save(Cloud cloud, GameData data)
		{
			CloudData customData = new CloudData { Name = data.Name };
			cloud.Save(customData);
		}

		public GameData Load(Cloud cloud)
		{
			CloudData customData = cloud.Load();
			return new GameData { Name = customData.Name };
		}
	}
}
