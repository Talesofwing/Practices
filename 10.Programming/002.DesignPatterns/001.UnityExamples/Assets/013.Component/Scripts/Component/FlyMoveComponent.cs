using UnityEngine;

namespace DesignPattern.Component
{
	public class FlyMoveComponent : MoveComponent
	{
		private float _height;
		private float _multiplier;

		public FlyMoveComponent(ObjectContainer owner, float speed, float height, float multiplier) : base(owner, speed)
		{
			_height = height;
			_multiplier = multiplier;
		}

		public override void Update(float deltaTime)
		{
			Owner.Position += new Vector3(0, _height, _speed * _multiplier * deltaTime);

			Debug.Log("FlyMoveComponent Update: " + Owner.Position);
		}
	}
}
