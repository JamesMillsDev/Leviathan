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

		public Vector3 Rotation => Parent != null ? (transform * Parent.transform).GetRotation() : transform.GetRotation();

		public Vector3 LocalRotation => transform.GetRotation();

		public Vector2 Forward
		{
			get
			{
				float radians = Rotation.x * LMath.DEG_2_RAD;

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

		public override string ToString() => $"\tPosition: {Position}\n\tRotation: {Rotation}\n\tScale: {Scale}";
	}
}