using UniRx;

public sealed class HeroModel
{
	public readonly ReactiveProperty<int> Hp = new ReactiveProperty<int>();
}
