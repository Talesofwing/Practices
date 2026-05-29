using UnityEngine;

namespace DesignPattern.Composite
{
	public interface IHittable
	{
		bool Hit(Ray ray, out IHittable hitObject);
	}
}
