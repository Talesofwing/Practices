using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Tester : MonoBehaviour
{
	[SerializeField]
	private HeroStatusView _heroStatusView;

	private HeroStatusViewModel _viewModel;

	private void Start()
	{
		_viewModel = new HeroStatusViewModel();
		_heroStatusView.Initialize(_viewModel);
	}

	private void Update()
	{
		if (Input.GetKeyDown(KeyCode.Space))
		{
			_viewModel.Model.Hp.Value -= 10;
		}
	}
}
