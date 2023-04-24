using Leviathan.Mathematics;

namespace Leviathan.GameObjects.Components
{
	public class Transform : Component
	{
		public bool HasChanged
		{
			get
			{
				bool wasChanged = hasChanged;
				hasChanged = false;
				
				return wasChanged;
			}
		}

		public Transform? Parent { get; set; }

		public Vector2 Position
		{
			get => Parent != null ? (transform * Parent.transform).Translation : transform.Translation;
			set
			{
				transform.Translation = value;
				hasChanged = true;
			}
		}

		public Vector2 LocalPosition
		{
			get => transform.Translation;
			set
			{
				transform.Translation = value;
				hasChanged = true;
			}
		}

		public Vector2 Scale
		{
			get => Parent != null ? (transform * Parent.transform).Scale : transform.Scale;
			set
			{
				transform.Scale = value;
				hasChanged = true;
			}
		}

		public Vector2 LocalScale
		{
			get => transform.Scale;
			set
			{
				transform.Scale = value;
				hasChanged = true;
			}
		}

		public float Rotation => (Parent != null ? (transform * Parent.transform).GetRotationX() : transform.GetRotationX()) * Leviamath.RAD_2_DEG;

		public float LocalRotation => transform.GetRotationX();

		public Vector2 Forward
		{
			get
			{
				float radians = Rotation * Leviamath.DEG_2_RAD;

				return Vector2.Rotate(new Vector2(MathF.Cos(radians), MathF.Sin(radians)), -90f).Normalized;
			}
		}

		public Vector2 Right => Vector2.Rotate(Forward, 90).Normalized;

		private Matrix3x3 transform;
		private bool hasChanged = false;

		internal Transform() => transform = Matrix3x3.CreateScale(Vector2.One);

		public void Rotate(float _rotation)
		{
			transform.SetRotationZ(transform.GetRotationX() + _rotation);
			hasChanged = true;
		}

		public void SetRotation(float _rotation)
		{
			transform.SetRotationZ(_rotation);
			hasChanged = true;
		}

		public Vector2 TransformVector(Vector2 _vector2) => transform * _vector2;

		public override string ToString() => $"\tPosition: {Position}\n\tRotation: {Rotation}\n\tScale: {Scale}";
	}
}