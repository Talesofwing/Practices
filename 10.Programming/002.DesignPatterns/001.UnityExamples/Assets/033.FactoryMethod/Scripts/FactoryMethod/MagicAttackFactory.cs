namespace DesignPattern.FactoryMethod
{
	public class MagicAttackFactory : IAttackFactory
	{
		public BaseAttack CreateAttack()
		{
			var attack = new MagicAttack(100);
			attack.MagicSpecialSetup();
			return attack;
		}
	}
}
