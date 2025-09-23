using System.Collections.Generic;

namespace DesignPattern.Update
{
	public class Entity
	{
		private List<Component> _components = new List<Component>();

		public string Name;

		public Entity()
		{
			Name = "Entity";
		}

		public Entity(string name)
		{
			Name = name;
		}

		public void AttachComponent(Component component)
		{
			_components.Add(component);
		}

		public void DetachComponent(Component component)
		{
			_components.Remove(component);
		}

		public void Update()
		{
			foreach (var component in _components)
			{
				component.Update();
			}
		}
	}
}
