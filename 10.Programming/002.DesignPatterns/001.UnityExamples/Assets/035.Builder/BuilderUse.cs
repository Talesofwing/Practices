using UnityEngine;

namespace DesignPattern.Builder
{
	public class BuilderUse : MonoBehaviour
	{
		private void Start()
		{
			Weapon weapon = new Weapon.Builder().SetAtk(10).SetAttackEffect("effect1").Build();
			weapon.Attack();
		}
	}
}
