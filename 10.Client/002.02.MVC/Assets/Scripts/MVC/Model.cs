using System;

using UnityEngine;

public class Model
{
	public string Name { get; private set; }
	public int MaxHealth { get; private set; }
	public int CurrentHealth { get; private set; }

	public event Action Changed;

	public void SetName(string name)
	{
		Name = name;
		Changed?.Invoke();
	}

	public void SetMaxHealth(int maxHealth)
	{
		MaxHealth = maxHealth;
		Changed?.Invoke();
	}

	public void SetCurrentHealth(int currentHealth)
	{
		CurrentHealth = Mathf.Clamp(currentHealth, 0, MaxHealth);
		Changed?.Invoke();
	}
}
