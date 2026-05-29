
namespace DesignPattern.Decorator
{
	public abstract class WeaponDecorator : Weapon
	{
		protected Weapon _weapon;

		public WeaponDecorator(Weapon weapon) : base(weapon.Atk)
		{
			_weapon = weapon;
		}

		public void SetWeapon(Weapon weapon)
		{
			_weapon = weapon;
		}

		public override void Attack()
		{
			if (_weapon != null)
			{
				_weapon.Attack();
			}
			else
			{
				UnityEngine.Debug.LogWarning("Weapon is not set");
			}
		}
	}
}
