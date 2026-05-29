using UnityEngine;

namespace DesignPattern.Component
{
	public class ComponentUse : MonoBehaviour
	{
		private ObjectContainer _objectContainer;

		private void Start()
		{
			_objectContainer = new ObjectContainer();
			// _objectContainer.AddComponent(new FlyMoveComponent(_objectContainer, 10f, 10f, 10f));
			_objectContainer.AddComponent(new MagicAttackComponent(_objectContainer, 10f, 10f));
		}

		private void Update()
		{
			_objectContainer.Update(Time.deltaTime);
		}
	}
}
