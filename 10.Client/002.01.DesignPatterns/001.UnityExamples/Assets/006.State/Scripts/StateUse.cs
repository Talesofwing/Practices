using UnityEngine;

namespace DesignPattern.State
{
	public class StateUse : MonoBehaviour
	{
		[SerializeField]
		private Boss _boss;

		private void Update()
		{
			if (Input.GetKeyDown(KeyCode.A))
			{
				_boss.Attack();
			}
			else if (Input.GetKeyDown(KeyCode.D))
			{
				_boss.TakeDamage(10);
			}
			else if (Input.GetKeyDown(KeyCode.M))
			{
				_boss.Move();
			}
		}
	}
}
