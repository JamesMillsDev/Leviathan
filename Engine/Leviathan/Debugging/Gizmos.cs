using Leviathan.Configuration;
using Leviathan.GameObjects;
using Leviathan.GameStates;
using Leviathan.Mathematics;

using Raylib_cs;

using Color = Leviathan.Mathematics.Color;
using Rectangle = Raylib_cs.Rectangle;

namespace Leviathan.Debugging
{
	/// <summary>A collection of useful drawing functions for rendering visual debug information in the game.</summary>
	public static class Gizmos
	{
		/// <summary>The flag that determines if gizmos will draw this frame. This is only able to be modified by <see cref="Application"/>.</summary>
		internal static bool drawGizmos;

		/// <summary></summary>
		internal static void Render(Config<ApplicationConfigData>? _config, List<ILeviathanModule> _modules)
		{
			if(drawGizmos)
			{
				// Only draw the FPS if it is enabled in the config 
				if(_config!.GetValue<bool>("debug.drawFpsGizmo"))
					Raylib.DrawFPS(10, 10);
				
				GameObjectManager.OnRenderGizmos();
				GameStateManager.OnRenderGizmos();
				
				_modules.ForEach(_module => _module.OnDrawGizmos());
			}
		}

		// /// <summary>Draws the passed transform's Forward and Right vector onto the screen.</summary>
		// /// <param name="_transform">The Transform that is being rendered.</param>
		// internal static void DrawTransform(TransformComponent _transform)
		// {
		// 	Raylib.DrawLineEx(_transform.Position, _transform.Position + _transform.Forward * (_transform.Scale.length / 3), 2, Color.BLUE);
		// 	Raylib.DrawLineEx(_transform.Position, _transform.Position + _transform.Right * (_transform.Scale.length / 3), 2, Color.RED);
		// }

		/// <summary>Renders a solid rectangle from the center with the specified rotation.</summary>
		/// <param name="_rectangle">The rectangle to draw.</param>
		/// <param name="_color">The colour to draw the rectangle</param>
		/// <param name="_rotation">The rotation of the rectangle.</param>
		public static void DrawRectangle(Rectangle _rectangle, Color _color, float _rotation = 0f)
		{
			Raylib.DrawRectanglePro(_rectangle, new Vector2(_rectangle.width / 2, _rectangle.height / 2), _rotation, _color);
		}

		/// <summary>Renders a hollow rectangle from the center with the specified rotation.</summary>
		/// <param name="_rectangle">The rectangle to draw.</param>
		/// <param name="_color">The colour to draw the rectangle</param>
		/// <param name="_rotation">The rotation of the rectangle.</param>
		public static void DrawWireRectangle(Rectangle _rectangle, Color _color, float _rotation = 0f)
		{
			// Calculate the forward and right vectors of the rectangle
			float radians = _rotation * Leviamath.DEG_2_RAD;
			Vector2 forward = new(MathF.Cos(radians), MathF.Sin(radians));
			Vector2 right = new(forward.y, -forward.x);

			// Convert the rectangle to a position and size vector
			Vector2 position = new(_rectangle.x, _rectangle.y);
			Vector2 halfSize = new(_rectangle.width * .5f, _rectangle.height * .5f);

			// Calculate the four corners of the rectangle in oriented space
			Vector2 topLeft = position + forward * halfSize.y - right * halfSize.x;
			Vector2 topRight = position + forward * halfSize.y + right * halfSize.x;
			Vector2 bottomLeft = position - forward * halfSize.y - right * halfSize.x;
			Vector2 bottomRight = position - forward * halfSize.y + right * halfSize.x;

			// Draw the four lines of the rectangle
			Raylib.DrawLineV(topLeft, bottomLeft, _color);
			Raylib.DrawLineV(bottomLeft, bottomRight, _color);
			Raylib.DrawLineV(bottomRight, topRight, _color);
			Raylib.DrawLineV(topRight, topLeft, _color);
		}

		/// <summary></summary>
		/// <param name="_position"></param>
		/// <param name="_radius"></param>
		/// <param name="_color"></param>
		public static void DrawCircle(Vector2 _position, float _radius, Color _color)
		{
			Raylib.DrawCircleV(_position, _radius, _color);
		}

		/// <summary></summary>
		/// <param name="_position"></param>
		/// <param name="_radius"></param>
		/// <param name="_color"></param>
		public static void DrawWireCircle(Vector2 _position, float _radius, Color _color)
		{
			Raylib.DrawCircleLines((int) _position.x, (int) _position.y, _radius, _color);
		}
	}
}