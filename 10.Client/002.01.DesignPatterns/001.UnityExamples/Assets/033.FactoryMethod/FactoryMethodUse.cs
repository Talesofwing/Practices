using UnityEngine;

namespace DesignPattern.FactoryMethod
{
	public class FactoryMethodUse : MonoBehaviour
	{
		private void Start()
		{
			var enemy = new Enemy(new MagicAttackFactory());
			enemy.Attack();

			var enemy2 = new Enemy(new PhysicsAttackFactory());
			enemy2.Attack();
		}
	}
}
