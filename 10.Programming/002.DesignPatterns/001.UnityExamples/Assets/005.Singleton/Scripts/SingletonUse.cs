using UnityEngine;

namespace DesignPattern.Singleton
{
	public class SingletonUse : MonoBehaviour
	{
		private void Start()
		{
			ResourceManager.Instance.LoadResource();
		}
	}
}
