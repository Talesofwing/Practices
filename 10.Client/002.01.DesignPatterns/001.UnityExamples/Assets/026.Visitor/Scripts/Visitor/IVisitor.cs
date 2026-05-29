namespace DesignPattern.Visitor
{
	public interface IVisitor
	{
		void Visit(Cube cube);
		void Visit(Sphere sphere);
	}
}
