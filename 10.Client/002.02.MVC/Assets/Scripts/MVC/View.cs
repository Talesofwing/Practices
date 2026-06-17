using UnityEngine;

using TMPro;

public class View : MonoBehaviour
{
	[SerializeField]
	private TextMeshProUGUI _nameText;

	[SerializeField]
	private TextMeshProUGUI _maxHealthText;

	[SerializeField]
	private TextMeshProUGUI _curHealthText;

	public void SetName(string name)
	{
		_nameText.text = name;
	}

	public void SetMaxHealth(int maxHealth)
	{
		_maxHealthText.text = maxHealth.ToString();
	}

	public void SetCurHealth(int curHealth)
	{
		_curHealthText.text = curHealth.ToString();
	}

	public void SetHealth(int maxHealth, int curHealth)
	{
		SetMaxHealth(maxHealth);
		SetCurHealth(curHealth);
	}
}
