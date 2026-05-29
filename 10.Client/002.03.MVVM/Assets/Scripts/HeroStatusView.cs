using UniRx;
using UnityEngine;
using UnityEngine.UI;

public class HeroStatusView : MonoBehaviour
{
	[SerializeField]
	private Text _hpText;

	public void Initialize(HeroStatusViewModel viewModel)
	{
		ApplyHp(viewModel.Model.Hp.Value);

		viewModel.Model.Hp.Subscribe(hp =>
		{
			ApplyHp(hp);
		}).AddTo(this);
	}

	public void ApplyHp(int hp)
	{
		_hpText.text = $"HP: {hp}";
	}
}
