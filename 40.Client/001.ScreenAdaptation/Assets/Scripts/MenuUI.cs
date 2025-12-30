using UnityEngine;

public class MenuUI : MonoBehaviour
{
	public void Show()
	{
		this.gameObject.SetActive(true);
	}

	public void Hide()
	{
		this.gameObject.SetActive(false);
	}

	public void OnStartButtonClick()
	{
		Controller.Instance.GameStart();
	}
}
