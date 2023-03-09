using Leviathan.Mathematics;

using Raylib_cs;

using System.Diagnostics.CodeAnalysis;

using Transform = Leviathan.GameObjects.Components.Transform;

namespace Leviathan.UI
{
	[SuppressMessage("ReSharper", "MemberCanBeProtected.Global")]
	public abstract class Widget : IComparable<Widget>
	{
		public Rectangle Rect => new(Transform!.LocalPosition.x, Transform!.LocalPosition.y, Transform!.LocalScale.x, Transform!.LocalScale.y);
		
		public Transform? Transform { get; }
		
		public int Layer { get; set; }

		protected Widget(Vec2 _pos, Vec2 _scale)
		{
			Transform = new Transform
			{
				LocalPosition = _pos,
				LocalScale = _scale
			};
		}

		public abstract void Render();

		public virtual void Tick(Vec2 _mousePos) { }

		public override string ToString()
		{
			// Widget:
			//   Transform:
			//     Position: (0, 0)
			//     Size: (50, 50)
			//     Scale: (50, 50)
			//   Draw Layer: 5
			return $"Widget:\n  Transform: {Transform}\n  Layer: {Layer}";
		}
		
		public int CompareTo(Widget? _other)
		{
			if(ReferenceEquals(this, _other))
				return 0;

			return ReferenceEquals(null, _other) ? 1 : Layer.CompareTo(_other.Layer);
		}
	}
}