using UnityEngine;

namespace DesignPattern.Strategy
{
	public class StrategyUse : MonoBehaviour
	{
		private void Start()
		{
			Entity entity = new Entity(new NoAttack());
			entity.Attack();

			Entity entity2 = new Entity(new RangedAttack());
			entity2.Attack();
		}
	}
}
