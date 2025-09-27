namespace DesignPattern.ChainOfResponsibility
{
	public class FragileBuff : Buff
	{
		private double _modifier;

		public FragileBuff(double modifier)
		{
			_modifier = modifier;
		}

		public override double Handle(double damage)
		{
			damage *= _modifier;

			UnityEngine.Debug.Log("FragileBuff Handle: " + damage);

			return base.Handle(damage);
		}
	}
}
