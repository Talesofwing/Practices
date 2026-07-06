using UnityEngine;
using UnityEngine.InputSystem;

public class MVPTester : MonoBehaviour
{
	[SerializeField]
	private View _view;

	private Model _model;
	private Presenter _presenter;

	private void Start()
	{
		_model = new Model();
		_presenter = new Presenter(_model, _view);
	}

	private void Update()
	{
		if (Keyboard.current.spaceKey.wasPressedThisFrame)
		{
			_model.SetHP(Random.Range(0, 100));
		}
	}
}
