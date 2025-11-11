namespace DesignPattern.FactoryMethod
{
	public class PhysicsAttackFactory : IAttackFactory
	{
		public BaseAttack CreateAttack()
		{
			var attack = new PhysicsAttack(100);
			attack.PhysicsAttackSetup();
			return attack;
		}
	}
}
