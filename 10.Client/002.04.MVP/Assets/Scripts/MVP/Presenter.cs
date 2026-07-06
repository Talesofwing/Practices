// In practice, even when using MVP,
// this role is usually named "Controller" rather than "Presenter".
public class Presenter
{
	private Model _model;
	private View _view;

	public Presenter(Model model, View view)
	{
		_model = model;
		_view = view;

		_model.OnHPChanged += OnHPChanged;
	}

	private void OnHPChanged(int hp)
	{
		_view.HPText.text = hp.ToString();
	}
}
