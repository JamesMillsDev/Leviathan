using Leviathan.Mathematics;

namespace Leviathan.Physics.Shapes
{
	public struct OrientedRectangle : IShape
	{
		public float ThetaRotation => rotation * Leviamath.DEG_2_RAD;
		
		public Vector2 center;
		public Vector2 halfExtents;
		public float rotation;

		public OrientedRectangle(Vector2? _position = null, Vector2? _halfExtents = null, float _rotation = 0f)
		{
			center = _position ?? Vector2.Zero;
			halfExtents = _halfExtents ?? Vector2.One;
			rotation = _rotation;
		}

		public bool Contains(Vector2 _point)
		{
			Vector2 rotVector = _point - center;
			Matrix2x2 rotationMat = Matrix2x2.FromAngle(-ThetaRotation);

			if(!MatrixMath.Multiply(out float[]? output, rotVector, 1, 2, rotationMat, 2, 2) && output != null)
				return false;

			Rectangle localRect = new()
			{
				center = Vector2.Zero,
				size = halfExtents * 2.0f
			};

			Vector2 localPoint = rotVector + output!;
			
			return localRect.Contains(localPoint);
		}
		
		public bool Intersects<SHAPE>(SHAPE _other) where SHAPE : IShape => _other switch
		{
			Circle circle => circle.Intersects(this),
			Rectangle rectangle => rectangle.Intersects(this),
			OrientedRectangle oriented => oriented.Intersects(this),
			_ => throw new ArgumentOutOfRangeException(nameof(_other), _other, null)
		};

		public bool Intersects(OrientedRectangle _other)
		{
			Rectangle local1 = new(Vector2.Zero, _other.halfExtents * 2.0f);
			OrientedRectangle local2 = new(_other.center, _other.halfExtents)
			{
				rotation = _other.rotation - rotation
			};
			
			Vector2 rotVector = center - _other.center;
			Matrix2x2 rotationMat = Matrix2x2.FromAngle(ThetaRotation);
			
			if(!MatrixMath.Multiply(out float[]? output, rotVector, 1, 2, rotationMat, 2, 2))
				return false;

			local2.center = output! + _other.halfExtents;
			
			return local1.Intersects(local2);
		}
	}
}