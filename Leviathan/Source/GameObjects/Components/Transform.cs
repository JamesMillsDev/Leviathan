using Leviathan.Mathematics;

using Math = Leviathan.Mathematics.Math;

namespace Leviathan.GameObjects.Components
{
	public class Transform : Component
	{
		public Transform? Parent { get; set; }

		public Vec2 Position
		{
			get => Parent != null ? (transform * Parent.transform).Translation : transform.Translation;
			set => transform.Translation = value;
		}

		public Vec2 LocalPosition
		{
			get => transform.Translation;
			set => transform.Translation = value;
		}

		public Vec2 Scale
		{
			get => Parent != null ? (transform * Parent.transform).Scale : transform.Scale;
			set => transform.Scale = value;
		}

		public Vec2 LocalScale
		{
			get => transform.Scale;
			set => transform.Scale = value;
		}

		public Vec3 Rotation => Parent != null ? (transform * Parent.transform).GetRotation() : transform.GetRotation();

		public Vec3 LocalRotation => transform.GetRotation();

		public Vec2 Forward
		{
			get
			{
				float radians = Rotation.x * Math.DEG2RAD;

				return Vec2.Normalise(Vec2.Rotate(new Vec2(MathF.Cos(radians), MathF.Sin(radians)), -90f));
			}
		}

		public Vec2 Right => Vec2.Normalise(Vec2.Rotate(Forward, 90));

		private Mat3 transform;

		internal Transform() => transform = Mat3.CreateScale(Vec2.one);

		public void Rotate(float _rotation) => transform.SetRotationZ(transform.GetRotationX() + _rotation);
	}
}