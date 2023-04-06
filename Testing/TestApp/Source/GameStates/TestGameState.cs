using Leviathan;
using Leviathan.GameObjects;
using Leviathan.GameObjects.Components;
using Leviathan.GameStates;
using Leviathan.Mathematics;
using Leviathan.Physics.Components;

using Raylib_cs;

using TestApp.GameObjects.Components;

using Color = Leviathan.Mathematics.Color;

namespace TestApp.GameStates
{
	public class TestGameState : IGameState
	{
		public string ID => "Test";

		private GameObject? player;
		private GameObject? turret;

		// private Button? button;

		public void Enter()
		{
			player = new GameObject("Player");
			if(player is { Transform: { } } && Application.Window is { })
			{
				player.Transform.Position = new Vector2(Application.Window.ScreenSize.x, Application.Window.ScreenSize.y) * 0.5f;
				player.Transform.LocalScale = new Vector2(200, 200);
			}

			player.AddComponent<SpriteRenderer>("player");
			player.AddComponent<MovementComponent>(100f);
			player.AddComponent<RotationComponent>(5f, "rotateBase");
			player.AddComponent<BoxCollider>();

			GameObjectManager.Spawn(player);

			turret = new GameObject("Turret");
			if(turret is { Transform: { } } && player is { Transform: { } })
			{
				turret.Transform.Parent = player.Transform;
				turret.Transform.Scale = Vector2.One * 0.5f;
			}

			SpriteRenderer? renderer = turret.AddComponent<SpriteRenderer>("player");
			if(renderer is { })
			{
				renderer.tint = Color.Yellow;
			}

			turret.AddComponent<RotationComponent>(5f, "rotateTurret");

			GameObjectManager.Spawn(turret);

			/*for(int i = 0; i < 150; i++)
			{
				GameObject test = new($"Banana ({i + 1})");
				if(test is { Transform: { } })
					test.Transform.Position = new Vector2(Raylib.GetRandomValue(0, Application.Window!.ScreenSize.x), Raylib.GetRandomValue(0, Application.Window.ScreenSize.y));

				GameObjectManager.Spawn(test);
			}*/

			GameObject empty = new("Test Collider");
			if(empty.Transform is { })
			{
				empty.Transform.LocalScale = Vector2.One * 250f;
			}

			BoxCollider? b = empty.AddComponent<BoxCollider>();
			b!.isTrigger = true;
			
			GameObjectManager.Spawn(empty);

			// button = new Button(Vector2.Zero, "banana", new Button.RenderSettings(50, Color.Red));

			//UIManager.Add(button);
		}

		public void Tick() { }

		public void Render() { }

		public void Exit()
		{
			GameObjectManager.Destroy(player);
		}
	}
}