using Leviathan;
using Leviathan.GameStates;

using TestApp.Source.GameStates;

namespace TestApp
{
	public class TestGame : Game
	{
		public override void Open()
		{
			GameStateManager.Add(new TestGameState());
			GameStateManager.Enter("Test");
		}

		public override void Close()
		{
		}
	}
}