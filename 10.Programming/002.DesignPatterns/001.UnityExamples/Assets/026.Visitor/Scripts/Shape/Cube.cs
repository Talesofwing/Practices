namespace DesignPattern.Visitor
{
	public class Cube : Shape
	{
		public override void Accept(IVisitor visitor)
		{
			visitor.Visit(this);
		}
	}
}
