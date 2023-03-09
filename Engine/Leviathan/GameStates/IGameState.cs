namespace Leviathan.GameStates
{
	public interface IGameState
	{
		// ReSharper disable once InconsistentNaming
		public string ID { get; }

		public void Enter();

		public void Tick();

		public void Render();

		public void Exit();

		public void OnRenderGizmos() { }
	}
}