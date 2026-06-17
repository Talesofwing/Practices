using UnityEngine;

public class Tester : MonoBehaviour
{
	[SerializeField]
	private View _view;

	private Model _model;
	private Controller _controller;

	private void Start()
	{
		_model = new Model();
		_controller = new Controller(_model, _view);

		_model.SetName("Player");
		_model.SetMaxHealth(100);
		_model.SetCurrentHealth(50);
	}

	private void Update()
	{
		if (Input.GetKeyDown(KeyCode.Space))
		{
			_model.SetCurrentHealth(_model.CurrentHealth + 10);
		}
		else if (Input.GetKeyDown(KeyCode.Backspace))
		{
			_model.SetCurrentHealth(_model.CurrentHealth - 10);
		}
	}
}
