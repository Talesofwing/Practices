using UnityEngine;

namespace DesignPattern.Composite
{
	public class CompositeUse : MonoBehaviour
	{
		private void Start()
		{
			ShapeList shapeList = new ShapeList();
			shapeList.Name = "ShapeList1";
			shapeList.AddShape(new Sphere(new Vector3(-5, -5, 8), 1));

			ShapeList shapeList2 = new ShapeList();
			shapeList2.Name = "ShapeList2";
			shapeList2.AddShape(new Sphere(new Vector3(0, 0, 0), 1));
			shapeList2.AddShape(new Sphere(new Vector3(1, 1, 1), 1));
			shapeList.AddShape(shapeList2);

			Ray ray = new Ray(new Vector3(0, 0, 0), new Vector3(1, 1, 1));
			CastRay(shapeList, ray);

			Ray ray2 = new Ray(new Vector3(5, 5, 5), new Vector3(1, 1, 1));
			CastRay(shapeList, ray2);
		}

		private void CastRay(ShapeList shapeList, Ray ray)
		{
			if (shapeList.Hit(ray, out IHittable hitObject))
			{
				Debug.Log("Hit Object: " + hitObject.GetType().Name);
			}
			else
			{
				Debug.Log("No hit");
			}
		}
	}
}
