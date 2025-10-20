namespace DesignPattern.Visitor
{
	public abstract class Shape
	{
		public abstract void Accept(IVisitor visitor);
	}
}
