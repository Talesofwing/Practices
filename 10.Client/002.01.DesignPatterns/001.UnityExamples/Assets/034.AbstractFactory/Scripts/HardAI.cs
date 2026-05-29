namespace DesignPattern.AbstractFactory
{
	public class HardAI : BaseAI
	{
		public override void Attack()
		{
			UnityEngine.Debug.Log("HardAI Attack");
		}

		public override void Move()
		{
			UnityEngine.Debug.Log("HardAI Move");
		}

		public override void Die()
		{
			UnityEngine.Debug.Log("HardAI Die");
		}
	}
}
