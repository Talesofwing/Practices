namespace DesignPattern.Strategy
{
	/// <summary>
	/// Context
	/// 	Can switch between different attack strategies.
	/// </summary>
	public class Entity
	{
		private BaseAttack _attack;

		public Entity(BaseAttack attack)
		{
			_attack = attack;
		}

		public void Attack()
		{
			_attack.Attack();
		}
	}
}
