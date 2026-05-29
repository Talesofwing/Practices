using UnityEngine;

namespace DesignPattern.Adapter
{
	public class AdapterUse : MonoBehaviour
	{
		private void Start()
		{
			Cloud cloud = new Cloud();
			GameData gameData = new GameData { Name = "Game Data" };
			CloudAdapter cloudAdapter = new CloudAdapter();

			cloudAdapter.Save(cloud, gameData);

			gameData = cloudAdapter.Load(cloud);
			UnityEngine.Debug.Log("Game Data: " + gameData.Name);
		}
	}
}
