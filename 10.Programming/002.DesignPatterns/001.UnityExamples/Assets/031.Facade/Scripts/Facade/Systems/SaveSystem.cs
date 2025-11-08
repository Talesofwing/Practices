namespace DesignPattern.Facade
{
	public static class SaveSystem
	{
		public static void Save(string savedata)
		{
			UnityEngine.Debug.Log("Save data: " + savedata);
		}
	}
}
