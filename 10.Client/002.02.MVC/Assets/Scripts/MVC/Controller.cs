using UnityEngine;

public class Controller
{
	private Model _model;
	private View _view;

	public Controller(Model model, View view)
	{
		_model = model;
		_view = view;

		_model.Changed += OnModelChanged;
	}

	private void OnModelChanged()
	{
		_view.SetName(_model.Name);
		_view.SetHealth(_model.CurrentHealth, _model.MaxHealth);
	}
}
