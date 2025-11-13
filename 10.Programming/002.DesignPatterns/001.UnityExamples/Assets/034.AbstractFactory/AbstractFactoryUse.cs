using UnityEngine;

namespace DesignPattern.AbstractFactory
{
	public class AbstractFactoryUse : MonoBehaviour
	{
		private void Start()
		{
			IEnemyFactory enemyFactory = new EasyEnemyFactory();
			BaseAI ai = enemyFactory.CreateAI();
			BaseMovement movement = enemyFactory.CreateMovement(10f);
			ai.Attack();
			movement.Move();

			enemyFactory = new HardEnemyFactory();
			ai = enemyFactory.CreateAI();
			movement = enemyFactory.CreateMovement(10f);
			ai.Attack();
			movement.Move();
		}
	}
}
