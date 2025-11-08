namespace DesignPattern.Decorator
{
	public class FireWeaponDecorator : WeaponDecorator
	{
		public FireWeaponDecorator(Weapon weapon) : base(weapon)
		{
		}

		public override void Attack()
		{
			UnityEngine.Debug.Log("FireWeaponDecorator Attack.");

			base.Attack();
		}
	}
}
