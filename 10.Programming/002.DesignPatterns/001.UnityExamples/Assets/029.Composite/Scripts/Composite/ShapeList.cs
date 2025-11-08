using System.Collections.Generic;

using UnityEngine;

namespace DesignPattern.Composite
{
	public class ShapeList : Shape
	{
		private List<Shape> _shapes = new List<Shape>();

		public void AddShape(Shape shape)
		{
			_shapes.Add(shape);
		}

		public void RemoveShape(Shape shape)
		{
			_shapes.Remove(shape);
		}

		public override bool Hit(Ray ray, out IHittable hitObject)
		{
			hitObject = null;
			foreach (var shape in _shapes)
			{
				if (shape.Hit(ray, out IHittable hitShape))
				{
					Debug.Log("ShapeList Hit Shape: " + Name);
					hitObject = shape;
					return true;
				}
			}
			return false;
		}
	}
}
