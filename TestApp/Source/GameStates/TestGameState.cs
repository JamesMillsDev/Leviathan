using Leviathan;
using Leviathan.GameObjects;
using Leviathan.GameObjects.Components;
using Leviathan.GameStates;
using Leviathan.Mathematics;

using Raylib_CsLo;

using TestApp.Source.GameObjects.Components;

using Color = Leviathan.Mathematics.Color;

namespace TestApp.Source.GameStates
{
	public class TestGameState : IGameState
	{
		public string ID => "Test";

		private GameObject? player;
		private GameObject? turret;

		public void Enter()
		{
			player = new GameObject("Player");
			if(player is { Transform: { } } && Application.Window is { })
			{
				player.Transform.Position = new Vec2(Application.Window.ScreenSize.x, Application.Window.ScreenSize.y) * 0.5f;
				player.Transform.LocalScale = new Vec2(200, 200);
			}

			player.AddComponent<SpriteRenderer>("player");
			player.AddComponent<MovementComponent>(100f);
			player.AddComponent<RotationComponent>(5f, KeyboardKey.KEY_A, KeyboardKey.KEY_D);

			GameObjectManager.Spawn(player);

			turret = new GameObject("Turret");
			if(turret is { Transform: { } } && player is { Transform: { } })
			{
				turret.Transform.Parent = player.Transform;
				turret.Transform.Scale = Vec2.one * 0.5f;
			}

			SpriteRenderer? renderer = turret.AddComponent<SpriteRenderer>("player");
			if(renderer is { })
			{
				renderer.tint = new Color(255, 0, 0, 255);
			}

			turret.AddComponent<RotationComponent>(5f, KeyboardKey.KEY_Q, KeyboardKey.KEY_E);

			GameObjectManager.Spawn(turret);
		}

		public void Tick() { }

		public void Render() { }

		public void Exit()
		{
			GameObjectManager.Destroy(player);
		}
	}
}