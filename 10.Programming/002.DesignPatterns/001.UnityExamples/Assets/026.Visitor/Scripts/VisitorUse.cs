using UnityEngine;

namespace DesignPattern.Visitor
{
	public class VisitorUse : MonoBehaviour
	{
		private void Start()
		{
			RenderVisitor renderVisitor = new RenderVisitor();
			PhysicsVisitor physicsVisitor = new PhysicsVisitor();
			Shape cube = new Cube();
			cube.Accept(renderVisitor);
			cube.Accept(physicsVisitor);
			Shape sphere = new Sphere();
			sphere.Accept(renderVisitor);
			sphere.Accept(physicsVisitor);
		}
	}
}
