using UnityEngine;

namespace DesignPattern.Update
{
	public class Component
	{
		public Entity entity { get; private set; }

		public Component(Entity entity)
		{
			this.entity = entity;
		}

		public virtual void Update()
		{
			Debug.Log("Component Update: " + entity.Name);
		}
	}
}
