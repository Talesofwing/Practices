using System.Diagnostics;

namespace DesignPattern.ChainOfResponsibility
{
	public class ToughBuff : Buff
	{
		private double _modifier;

		public ToughBuff(double modifier)
		{
			_modifier = modifier;
		}

		public override double Handle(double damage)
		{
			damage *= _modifier;

			UnityEngine.Debug.Log("ToughBuff Handle: " + damage);

			return base.Handle(damage);
		}
	}
}
