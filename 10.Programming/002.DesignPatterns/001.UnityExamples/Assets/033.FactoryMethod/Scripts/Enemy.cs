namespace DesignPattern.FactoryMethod
{
	public class Enemy
	{
		private BaseAttack _attack;

		public Enemy(IAttackFactory attackFactory)
		{
			_attack = attackFactory.CreateAttack();
		}

		public void Attack()
		{
			_attack.Attack();
		}
	}
}
