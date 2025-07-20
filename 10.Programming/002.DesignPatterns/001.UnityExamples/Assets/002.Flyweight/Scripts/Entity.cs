using UnityEngine;

namespace DesignPattern.Flyweight
{
	/// <summary>
	/// As extrinsic
	/// </summary>
	public class Entity
	{
		private EntityState _state = null;

		private int _curHp = 0;
		private Vector3 _pos;

		public string Name => _state.Name;
		public int MaxHp => _state.Hp;

		public int CurHp => _curHp;

		public Vector3 Pos
		{
			get { return _pos; }
			set { _pos = value; }
		}

		public void Init(EntityState state)
		{
			SetState(state);

			Pos = Vector3.zero;
		}

		public void SetState(EntityState state)
		{
			_state = state;

			_curHp = _state.Hp;
		}

		public void TakeDamage(int damage)
		{
			_curHp -= damage;
		}

		public override string ToString()
		{
			return $"[Entity] Name: {Name}, MaxHp: {MaxHp}, CurHp: {CurHp}, Pos: {Pos}";
		}
	}
}
