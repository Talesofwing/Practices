namespace DesignPattern.FactoryMethod
{
	public class MagicAttack : BaseAttack
	{
		public MagicAttack(int atk) : base(atk) { }

		public void MagicSpecialSetup()
		{
			UnityEngine.Debug.Log("MagicAttack SpecialSetup");
		}

		public override void Attack()
		{
			UnityEngine.Debug.Log("MagicAttack Attack: " + _atk);
		}
	}
}
