namespace DesignPattern.FactoryMethod
{
	public abstract class BaseAttack
	{
		protected int _atk;

		public BaseAttack(int atk)
		{
			_atk = atk;
		}

		public virtual void Attack() { }
	}
}
