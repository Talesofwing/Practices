namespace DesignPattern.Visitor
{
	public class Sphere : Shape
	{
		public override void Accept(IVisitor visitor)
		{
			visitor.Visit(this);
		}
	}
}
