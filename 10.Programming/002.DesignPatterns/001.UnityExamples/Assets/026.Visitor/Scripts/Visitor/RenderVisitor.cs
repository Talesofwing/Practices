namespace DesignPattern.Visitor
{
	public class RenderVisitor : IVisitor
	{
		public void Visit(Cube cube)
		{
			UnityEngine.Debug.Log("Render Cube");
		}

		public void Visit(Sphere sphere)
		{
			UnityEngine.Debug.Log("Render Sphere");
		}
	}
}
