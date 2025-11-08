using UnityEngine;

namespace DesignPattern.Facade
{
	public class FacadeUse : MonoBehaviour
	{
		private void Start()
		{
			string savedata = "Save data";
			GameFacade.SaveGame(savedata);
		}
	}
}
