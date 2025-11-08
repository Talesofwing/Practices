namespace DesignPattern.Decorator
{
	public class Weapon
	{
		private int _atk;

		public int Atk { get => _atk; }

		public Weapon(int atk)
		{
			_atk = atk;
		}

		public virtual void Attack()
		{
			UnityEngine.Debug.Log("Weapon Attack: " + _atk);
		}
	}
}
