using UnityEngine;

namespace DesignPattern.Prototype
{
	public class PrototypeUse : MonoBehaviour
	{
		private void Start()
		{
			EntityRegistry.Register("Noob", new Entity(10, 10));
			EntityRegistry.Register("Elite", new Entity(1000, 1000));
		}

		private void Update()
		{
			if (Input.GetKeyDown(KeyCode.N))
			{
				Entity entity = EntityRegistry.Create("Noob");
				entity.TakeDamage(10);
			}
			else if (Input.GetKeyDown(KeyCode.E))
			{
				Entity entity = EntityRegistry.Create("Elite");
				entity.TakeDamage(100);
			}
		}
	}
}
