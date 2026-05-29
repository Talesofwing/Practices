namespace DesignPattern.Visitor
{
	public class PhysicsVisitor : IVisitor
	{
		public void Visit(Cube cube)
		{
			UnityEngine.Debug.Log("Physics Cube");
		}

		public void Visit(Sphere sphere)
		{
			UnityEngine.Debug.Log("Physics Sphere");
		}
	}
}
