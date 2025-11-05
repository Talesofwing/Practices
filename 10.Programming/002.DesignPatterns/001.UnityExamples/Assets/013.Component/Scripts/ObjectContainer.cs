using System.Collections.Generic;

using UnityEngine;

namespace DesignPattern.Component
{
	public class ObjectContainer
	{
		private List<Component> _components = new List<Component>();

		public Vector3 Position;

		// In the practices, you need to check if the component is already added to the container.
		public void AddComponent(Component component)
		{
			_components.Add(component);
			component.Init();
			component.OnActive();
		}

		public void RemoveComponent(Component component)
		{
			_components.Remove(component);
			component.OnDeactive();
			component.OnDestroy();
		}

		public void Update(float deltaTime)
		{
			foreach (var component in _components)
			{
				component.Update(deltaTime);
			}
		}

		public void Broadcast(string message)
		{
			foreach (var component in _components)
			{
				component.OnMessage(message);
			}
		}
	}
}
