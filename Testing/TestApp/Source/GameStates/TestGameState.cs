using Leviathan;
using Leviathan.Debugging;
using Leviathan.GameObjects;
using Leviathan.GameObjects.Components;
using Leviathan.GameStates;
using Leviathan.Mathematics;
using Leviathan.UI;

using TestApp.GameObjects.Components;

namespace TestApp.GameStates
{
	public class TestGameState : IGameState
	{
		public string ID => "Test";

		private GameObject? player;
		private GameObject? turret;

		private Button? button;

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
			player.AddComponent<RotationComponent>(5f, "rotateBase");

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

			turret.AddComponent<RotationComponent>(5f, "rotateTurret");

			GameObjectManager.Spawn(turret);

			button = new Button(Vec2.zero, "banana", new Button.RenderSettings(50, Raylib_cs.Color.RED));

			UIManager.Add(button);
		}

		public void Tick() { }

		public void Render() { }

		public void Exit()
		{
			GameObjectManager.Destroy(player);
		}
	}
}