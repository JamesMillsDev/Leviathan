using Leviathan.Configuration;
using Leviathan.Configuration.Converters.Math;
using Leviathan.Events;
using Leviathan.GameObjects;
using Leviathan.Mathematics;

using Raylib_cs;

using Color = Leviathan.Mathematics.Color;

namespace Leviathan
{
	public sealed class Window : IEventHandler
	{
		public ref Vector2Int ScreenSize => ref screenSize;
		public ref Color ClearColor => ref clearColor;
		public bool IsFullscreen { get; private set; }
		public string? Title { get; private set; }
		public Rectangle ScreenBounds => new(0, 0, screenSize.x, screenSize.y);

		private Vector2Int screenSize;
		private Color clearColor;
		private long frameRate;
		private bool lockFrameRate;
		private long fullscreenKey;

		private readonly Config<ApplicationConfigData>? programConfig;

		internal Window(Config<ApplicationConfigData>? _programConfig)
		{
			programConfig = _programConfig ?? throw new NullReferenceException($"Program config is null!");
			
			screenSize = programConfig.GetValue("window.screenSize", Int2Converter.Instance);
			Title = programConfig.GetValue<string>("application.name");
			clearColor = programConfig.GetValue("application.clearColor", ColorConverter.Instance);
			IsFullscreen = programConfig.GetValue<bool>("window.useFullscreen");
			fullscreenKey = programConfig.GetValue<long>("window.fullscreenKey");
			frameRate = programConfig.GetValue<long>("application.maxFrameRate");
			lockFrameRate = programConfig.GetValue<bool>("application.lockFrameRate");
			
			if(lockFrameRate)
				Raylib.SetTargetFPS((int)frameRate);
		}

		public void ClearScreen() => Raylib.ClearBackground(clearColor);

		internal void Open()
		{
			EventBus.RegisterObject(this);
			
			Application.raylibLogger.LogWarn($"Opening window with size {screenSize} and name {Title}");
			Raylib.InitWindow(screenSize.x, screenSize.y, Title!);
			
			if(IsFullscreen)
			{
				screenSize = new Vector2Int
				{
					x = Raylib.GetMonitorWidth(0),
					y = Raylib.GetMonitorHeight(0),
				};
				
				Raylib.ToggleFullscreen();
				Raylib.SetWindowSize(screenSize.x, screenSize.y);
			}
		}

		internal void Close()
		{
			Application.raylibLogger.LogWarn($"Closing window with size {screenSize} and name {Title}");
			Raylib.CloseWindow();
			
			EventBus.RemoveObject(this);
		}

		internal void Render()
		{
			Raylib.BeginDrawing();
			ClearScreen();
			
			GameObjectManager.Render();
			
			Raylib.EndDrawing();
		}

		internal void Tick()
		{
			if(Raylib.IsKeyPressed((KeyboardKey) fullscreenKey))
				SwapFullscreenMode();
		}

		public void SwapFullscreenMode()
		{
			if(programConfig == null)
				throw new NullReferenceException("Program config is null!");
			
			IsFullscreen = !IsFullscreen;
			
			if(!IsFullscreen)
				Raylib.ToggleFullscreen();

			Vector2Int size = programConfig.GetValue("window.screenSize", Int2Converter.Instance);
			screenSize = new Vector2Int
			{
				x = IsFullscreen ? Raylib.GetMonitorWidth(0) : size.x,
				y = IsFullscreen ? Raylib.GetMonitorHeight(0) : size.y,
			};
			Raylib.SetWindowSize(screenSize.x, screenSize.y);
			
			if(IsFullscreen)
				Raylib.ToggleFullscreen();
		}

		[SubscribeEvent]
		// ReSharper disable once UnusedMember.Local
		// ReSharper disable once UnusedParameter.Local
		private void Reconfigure(ConfigReloadEvent _event)
		{
			if(programConfig == null)
				throw new NullReferenceException("Program config is null!");

			bool wasFullscreen = IsFullscreen;

			screenSize = programConfig.GetValue("window.screenSize", Int2Converter.Instance);
			Title = programConfig.GetValue<string>("application.name");
			clearColor = programConfig.GetValue("application.clearColor", ColorConverter.Instance);
			IsFullscreen = programConfig.GetValue<bool>("window.useFullscreen");
			fullscreenKey = programConfig.GetValue<long>("window.fullscreenKey");
			frameRate = programConfig.GetValue<long>("application.maxFrameRate");
			lockFrameRate = programConfig.GetValue<bool>("application.lockFrameRate");
			
			Raylib.SetWindowTitle(Title!);
			Raylib.SetWindowSize(screenSize.x, screenSize.y);
			if(lockFrameRate)
				Raylib.SetTargetFPS((int)frameRate);

			if(!wasFullscreen && IsFullscreen)
			{
				Raylib.ToggleFullscreen();
				screenSize = new Vector2Int
				{
					x = Raylib.GetMonitorWidth(0),
					y = Raylib.GetMonitorHeight(0),
				};
				Raylib.SetWindowSize(screenSize.x, screenSize.y);
			}
			else if(wasFullscreen && !IsFullscreen)
			{
				Raylib.ToggleFullscreen();
				Raylib.SetWindowSize(screenSize.x, screenSize.y);
			}
		}
	}
}