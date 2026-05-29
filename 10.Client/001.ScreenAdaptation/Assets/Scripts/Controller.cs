using UnityEngine;

public class Controller : MonoBehaviour
{
	public static Controller Instance { get; private set; }

	[SerializeField]
	private MenuUI _menuUI;

	[SerializeField]
	private GameUI _gameUI;

	[SerializeField]
	private GameObject _gameScene;

	[SerializeField]
	private Camera _camera;

	private void Awake()
	{
		if (Instance == null)
		{
			Instance = this;
		}
		else
		{
			Destroy(this.gameObject);
			return;
		}

		AdjustCamera();
	}

	private void AdjustCamera()
	{
		const float devSize = 7f;
		const float devAspect = 9f / 16f;
		float curAspect = (float)Screen.height / Screen.width;

		if (curAspect <= devAspect)
		{
			// No-Loss Scaling
			// When the current aspect ratio is less than dev aspect ratio,
			// To ensure no clipping, directly using the development size guarantees no content will be clipped.
			_camera.orthographicSize = devSize;
		}
		else
		{
			// Match Width
			float ratio = curAspect / devAspect;
			_camera.orthographicSize = devSize * ratio;
		}
	}

	public void GameStart()
	{
		_menuUI.gameObject.SetActive(false);
		_gameUI.gameObject.SetActive(true);
		_gameScene.SetActive(true);
	}
}
