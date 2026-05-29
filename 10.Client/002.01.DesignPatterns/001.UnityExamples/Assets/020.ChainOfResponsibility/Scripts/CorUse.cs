using UnityEngine;

namespace DesignPattern.ChainOfResponsibility
{
	public class CorUse : MonoBehaviour
	{
		private IDamageHandler _damageHandler;

		private void Start()
		{
			FragileBuff fragileBuff = new FragileBuff(3);
			ToughBuff toughBuff = new ToughBuff(0.5);

			fragileBuff.SetNextHandler(toughBuff);

			_damageHandler = fragileBuff;
		}

		private void Update()
		{
			if (Input.GetKeyDown(KeyCode.Space))
			{
				double damage = Random.Range((int)10, (int)1000);
				Debug.Log("Damage: " + damage);
				damage = _damageHandler.Handle(damage);
				Debug.Log("Damage: " + damage);
			}
		}
	}
}
