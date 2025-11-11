namespace DesignPattern.FactoryMethod
{
	public class PhysicsAttack : BaseAttack
	{
		public PhysicsAttack(int atk) : base(atk) { }

		public void PhysicsAttackSetup()
		{
			UnityEngine.Debug.Log("PhysicsAttack SpecialSetup");
		}

		public override void Attack()
		{
			UnityEngine.Debug.Log("PhysicsAttack Attack: " + _atk);
		}
	}
}
