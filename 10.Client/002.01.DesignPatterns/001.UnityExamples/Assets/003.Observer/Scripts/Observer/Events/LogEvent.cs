namespace DesignPattern.Observer
{
	public readonly struct LogEvent : IEvent
	{
		public readonly string Message;

		public LogEvent(string message) => Message = message;
	}
}
