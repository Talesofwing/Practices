using UnityEngine;

namespace DesignPattern.SubclassSandbox
{
	public class SubclassSandboxUse : MonoBehaviour
	{
		private void Start()
		{
			Player player = new Player();
			player.Attack();
			player.TakeDamage(10);
		}
	}
}
