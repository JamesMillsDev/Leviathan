using Leviathan.Configuration;
using Leviathan.Configuration.Converters.Math;
using Leviathan.GameObjects;
using Leviathan.Mathematics;

using Raylib_CsLo;

using Color = Raylib_CsLo.Color;

namespace Leviathan
{
	public sealed class Window
	{
		public ref Int2 ScreenSize => ref screenSize;
		public ref Color ClearColor => ref clearColor;
		public bool IsFullscreen { get; private set; }
		public string? Title { get; private set; }

		private Int2 screenSize;
		private Color clearColor;
		private long frameRate;
		private bool lockFrameRate;
		private long fullscreenKey;

		private readonly Config<ApplicationConfigData>? programConfig;

		internal Window(Config<ApplicationConfigData>? _programConfig)
		{
			programConfig = _programConfig ?? throw new NullReferenceException($"Program config is null!");
			Application.onReconfigure += Reconfigure;
			
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
			Application.raylibLogger.LogWarn($"Opening window with size {screenSize} and name {Title}");
			Raylib.InitWindow(screenSize.x, screenSize.y, Title!);
			
			if(IsFullscreen)
			{
				screenSize = new Int2
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

			Int2 size = programConfig.GetValue("window.screenSize", Int2Converter.Instance);
			screenSize = new Int2
			{
				x = IsFullscreen ? Raylib.GetMonitorWidth(0) : size.x,
				y = IsFullscreen ? Raylib.GetMonitorHeight(0) : size.y,
			};
			Raylib.SetWindowSize(screenSize.x, screenSize.y);
			
			if(IsFullscreen)
				Raylib.ToggleFullscreen();
		}

		private void Reconfigure()
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
				screenSize = new Int2
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