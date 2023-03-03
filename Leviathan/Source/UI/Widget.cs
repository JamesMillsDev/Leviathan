using Leviathan.Mathematics;

using Raylib_CsLo;

using Transform = Leviathan.GameObjects.Components.Transform;

namespace Leviathan.UI
{
	public abstract class Widget
	{
		public Rectangle Bounds => new(Transform!.LocalPosition.x, Transform!.LocalPosition.y, Transform!.LocalScale.x, Transform!.LocalScale.y);
		
		public Transform? Transform { get; }

		protected Widget(Vec2 _pos, Vec2 _scale)
		{
			Transform = new Transform
			{
				LocalPosition = _pos,
				LocalScale = _scale
			};
		}

		public abstract void Render();

		public abstract void Tick();
	}
}