namespace DesignPattern.AbstractFactory
{
	public class EasyAI : BaseAI
	{
		public override void Attack()
		{
			UnityEngine.Debug.Log("EasyAI Attack");
		}

		public override void Move()
		{
			UnityEngine.Debug.Log("EasyAI Move");
		}

		public override void Die()
		{
			UnityEngine.Debug.Log("EasyAI Die");
		}
	}
}
