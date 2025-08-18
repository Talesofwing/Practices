using UnityEngine;

namespace DesignPattern.Prototype
{
	public class Entity
	{
		#region Prototypes

		public Entity Clone()
		{
			return new Entity(_atk, _hp);
		}

		#endregion Prototypes

		private int _atk;
		private int _hp;

		public Entity(int atk, int hp)
		{
			_atk = atk;
			_hp = hp;
		}

		private void Attack()
		{
			Debug.Log("Attack: " + _atk);
		}

		public void TakeDamage(int damage)
		{
			_hp -= damage;

			if (_hp > 0)
			{
				Debug.Log("TakeDamage: " + damage + ", HP: " + _hp);
			}
			else
			{
				Death();
			}
		}

		private void Death()
		{
			Debug.Log("Death");
		}

		public override string ToString()
		{
			return $"ATK: {_atk}, HP: {_hp}";
		}
	}
}
