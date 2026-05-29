using System.Collections.Generic;
using UnityEngine;

namespace DesignPattern.Update
{
	public class UpdateUse : MonoBehaviour
	{
		private List<Entity> _entities = new List<Entity>();

		private void Start()
		{
			for (int i = 0; i < 10; ++i)
			{
				Entity entity = new Entity("Entity " + i);
				entity.AttachComponent(new Component(entity));
				_entities.Add(entity);
			}
		}

		private void Update()
		{
			foreach (var entity in _entities)
			{
				entity.Update();
			}
		}
	}
}
