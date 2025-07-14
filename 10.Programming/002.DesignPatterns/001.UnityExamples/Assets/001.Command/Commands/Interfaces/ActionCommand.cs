namespace DesignPattern.Command
{
	public abstract class ActionCommand : ICommand
	{
		public abstract void Execute();
		public abstract void Undo();
	}
}
