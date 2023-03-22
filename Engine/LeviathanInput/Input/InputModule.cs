﻿namespace Leviathan.Input
{
	internal class InputModule : ILeviathanModule
	{
		public void Load() => InputSystem.CreateInstance();

		public void Render() { }

		public void Tick() => InputSystem.Tick();

		public void Unload() => InputSystem.DestroyInstance();
	}
}