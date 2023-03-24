using Leviathan.Mathematics;

namespace Leviathan.Physics
{
	public struct OrientedRectangle
	{
		public Vector2 Center
		{
			get => transform.Translation;
			set => transform.Translation = value;
		}

		public Vector2 HalfExtents => transform.Scale * .5f;
		public float Rotation
		{
			get => transform.GetRotationX();
			set => transform.SetRotationZ(value);
		}

		private Matrix3x3 transform;

		public OrientedRectangle(Vector2? _position = null, Vector2? _halfExtents = null, float _rotation = 0f)
		{
			Vector2 pos = _position ?? Vector2.Zero;
			Vector2 halfExtents = _halfExtents ?? Vector2.One;

			transform = Matrix3x3.CreateTranslation(pos) * Matrix3x3.CreateZRotation(_rotation) * Matrix3x3.CreateScale(halfExtents);
		}

		public bool Contains(Vector2 _point)
		{
			Matrix3x3 rotMat = Matrix3x3.CreateZRotation(Rotation);
			Vector2 rotated = (_point - Center) * rotMat;

			Rectangle local = new(Vector2.Zero, HalfExtents * 2f);
			Vector2 localPoint = rotated + HalfExtents;

			return local.Contains(localPoint);
		}

		public bool Intersects(OrientedRectangle _other)
		{
			Rectangle local1 = new(Vector2.Zero, HalfExtents * 2.0f);

			OrientedRectangle local2 = new(_other.Center, _other.HalfExtents, 0)
			{
				Rotation = _other.Rotation - Rotation
			};
			
			Matrix3x3 rotMat = Matrix3x3.CreateZRotation(-Rotation);
			Vector2 r = (_other.Center - Center) * rotMat;
			local2.Center = r + HalfExtents;

			return local1.Intersects(local2);
		}
	}
}