using Leviathan.Mathematics;

namespace Leviathan.Physics
{
	public struct Box2D
	{
		public Vector2 Center => transform.Translation;
		public Vector2 HalfExtents => transform.Scale * .5f;
		public float Rotation => transform.GetRotationX();

		private Matrix3x3 transform;

		public Box2D(Vector2? _position = null, Vector2? _halfExtents = null, float _rotation = 0f)
		{
			Vector2 pos = _position ?? Vector2.Zero;
			Vector2 halfExtents = _halfExtents ?? Vector2.One;

			transform = Matrix3x3.CreateTranslation(pos) * Matrix3x3.CreateZRotation(_rotation) * Matrix3x3.CreateScale(halfExtents);
		}

		public bool Contains(Vector2 _point)
		{
			Vector2 rotated = _point - Center;
			float theta = -Rotation;

			float[] rotMat =
			{
				LMath.Cos(theta), LMath.Sin(theta),
				-LMath.Sin(theta), LMath.Cos(theta)
			};

			if(Matrix3x3.Multiply(out float[]? @out, rotated, 1, 2, rotMat, 2, 2) && @out == null)
				return false;
			
			rotated = @out!;

			Rectangle local = new(Vector2.Zero, HalfExtents * 2f);
			Vector2 localPoint = rotated + HalfExtents;

			return local.Contains(localPoint);
		}
	}
}