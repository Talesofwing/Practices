namespace DesignPattern.Builder
{
	public class Weapon
	{
		private int _atk;
		private string _effectID;

		private Weapon(Builder builder)
		{
			_atk = builder._atk;
			_effectID = builder._effectID;
		}

		public void Attack()
		{
			UnityEngine.Debug.Log("Weapon Attack: " + _atk);
		}

		// If needed, the Builder can be placed inside the particle class
		// or a Builder class can be created externally (not as an inner class)
		public class Builder
		{
			internal int _atk;
			internal string _effectID;

			public Builder SetAtk(int atk)
			{
				_atk = atk;
				return this;
			}

			public Builder SetAttackEffect(string effectID)
			{
				_effectID = effectID;
				return this;
			}

			public Weapon Build()
			{
				return new Weapon(this);
			}
		}
	}
}
