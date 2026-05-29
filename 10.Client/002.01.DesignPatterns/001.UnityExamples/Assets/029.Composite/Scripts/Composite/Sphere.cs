using UnityEngine;

namespace DesignPattern.Composite
{
	public class Sphere : Shape
	{
		private Vector3 _center;
		private float _radius;

		public Sphere(Vector3 center, float radius)
		{
			_center = center;
			_radius = radius;
		}

		public override bool Hit(Ray ray, out IHittable hitObject)
		{
			hitObject = null;

			Vector3 origin = ray.origin - _center;
			float a = Vector3.Dot(origin, origin);
			float b = 2 * Vector3.Dot(origin, ray.direction);
			float c = Vector3.Dot(ray.direction, ray.direction) - _radius * _radius;
			float discriminant = b * b - 4 * a * c;
			if (discriminant < 0)
			{
				return false;
			}
			float t = (-b - Mathf.Sqrt(discriminant)) / (2 * a);
			if (t < 0)
			{
				return false;
			}
			hitObject = this;
			return true;
		}
	}
}
