using UnityEngine;

namespace DesignPattern.Mediator
{
	public class MediatorUse : MonoBehaviour
	{
		private void Start()
		{
			for (int i = 0; i < 5; ++i)
			{
				CombatSystem.Instance.GetRandomEntity().PerformAttack();
			}
		}
	}
}
