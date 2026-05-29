using UnityEngine;

namespace DesignPattern.Composite
{
	public abstract class Shape : IHittable
	{
		public string Name;

		public abstract bool Hit(Ray ray, out IHittable hitObject);
	}
}
