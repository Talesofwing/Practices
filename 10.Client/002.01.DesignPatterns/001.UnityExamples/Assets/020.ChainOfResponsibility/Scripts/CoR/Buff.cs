namespace DesignPattern.ChainOfResponsibility
{
	public abstract class Buff : IDamageHandler
	{
		protected IDamageHandler _nextHandler;

		public virtual double Handle(double damage)
		{
			if (_nextHandler != null)
			{
				return _nextHandler.Handle(damage);
			}

			return damage;
		}

		public virtual void SetNextHandler(IDamageHandler nextHandler)
		{
			_nextHandler = nextHandler;
		}
	}
}
