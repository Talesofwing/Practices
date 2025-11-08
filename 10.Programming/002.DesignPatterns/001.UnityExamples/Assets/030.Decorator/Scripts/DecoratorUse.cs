using UnityEngine;

namespace DesignPattern.Decorator
{
	public class DecoratorUse : MonoBehaviour
	{
		private void Start()
		{
			Weapon weapon = new FireWeaponDecorator(new Weapon(10));
			weapon.Attack();
		}
	}
}
