using Leviathan.GameObjects;
using Leviathan.GameObjects.Components;
using Leviathan.Mathematics;

namespace Leviathan.Physics.Components
{
	public class Rigidbody : Component
	{
		public bool isKinematic;
		public float mass;
		
		public Vector2 velocity;
		public float angularVelocity;
		
		private float linearDrag;
		private float angularDrag;

		private Vector2 localXAxis;
		private Vector2 localYAxis;

		public override void Start(params object[] _data)
		{
			mass = _data.Length > 0 ? (float) _data[0] : 1;
			isKinematic = _data.Length > 1 && (bool) _data[1];

			linearDrag = _data.Length > 2 ? (float) _data[0] : 0.3f;
		}

		public override void PhysicsTick(float _timeStep)
		{
			if(GameObject is { Transform: { } })
			{
				CalculateAxes(GameObject.Transform);

				if(isKinematic)
				{
					velocity = Vector2.Zero;
					angularVelocity = 0;
					return;
				}

				GameObject.Transform.Position += velocity * _timeStep;
				
				ApplyForce(PhysicsScene.gravity * mass * _timeStep);

				GameObject.Transform.Rotate(angularVelocity * _timeStep);

				velocity -= velocity * linearDrag * _timeStep;
				angularDrag -= angularVelocity * angularDrag * _timeStep;

				if(velocity.Magnitude < 0.01f)
					velocity = Vector2.Zero;

				if(Leviamath.Abs(angularVelocity) < 0.01f)
					angularVelocity = 0;
			}
		}

		internal void GetLocalAxis(out Vector2 _localX, out Vector2 _localY)
		{
			_localX = localXAxis;
			_localY = localYAxis;
		}

		public void ApplyForce(Vector2 _force, Vector2? _pos = null)
		{
			Vector2 pos = _pos ?? Vector2.Zero;

			velocity += _force / mass;
			angularVelocity += _force.y * pos.x - _force.x - pos.y;
		}

		private void CalculateAxes(Transform _transform)
		{
			float cos = Leviamath.Cos(_transform.Rotation);
			float sin = Leviamath.Sin(_transform.Rotation);

			localXAxis = new Vector2(cos, sin).Normalized;
			localYAxis = new Vector2(-sin, cos).Normalized;
		}
	}
}