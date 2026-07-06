using System;

public class Model
{
	private int HP;

	public event Action<int> OnHPChanged;

	public void SetHP(int hp)
	{
		HP = hp;
		OnHPChanged?.Invoke(HP);
	}
}
