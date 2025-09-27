using UnityEngine;

namespace DesignPattern.ChainOfResponsibility
{
	public interface IDamageHandler
	{
		double Handle(double damage);
		void SetNextHandler(IDamageHandler nextHandler);
	}
}
