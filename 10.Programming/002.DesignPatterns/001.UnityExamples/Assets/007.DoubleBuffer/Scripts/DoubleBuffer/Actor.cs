namespace DesignPattern.DoubleBuffer
{
	public class Actor
	{
		private string _name;

		private Actor _facing = null;

		private bool _curSlapStatus = false;
		private bool _nextSlapStatus = false;

		public bool WasSlapped => _curSlapStatus;

		public Actor(string name)
		{
			_name = name;
		}

		public void SetFacing(Actor facing)
		{
			_facing = facing;
		}

		public void Slap()
		{
			_nextSlapStatus = true;
		}

		public void Update()
		{
			if (_curSlapStatus && _facing != null)
			{
				_facing.Slap();
			}
		}

		public void Swap()
		{
			_curSlapStatus = _nextSlapStatus;
			_nextSlapStatus = false;
		}

		public override string ToString()
		{
			return $"[Actor] Name: {_name}, CurSlapStatus: {_curSlapStatus}, NextSlapStatus: {_nextSlapStatus}";
		}
	}
}
