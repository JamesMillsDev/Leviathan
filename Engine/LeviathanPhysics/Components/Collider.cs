using Leviathan.GameObjects;
using Leviathan.Mathematics;

namespace Leviathan.Physics.Components
{
	public abstract class Collider : Component
	{
		internal abstract CollisionFunctions.Shape Shape { get; }
		
		public bool isTrigger;
		
		internal PhysicsTreeData? data;

		private readonly List<Collider> objectsInside = new();
		private readonly List<Collider> objectsInsideThisFrame = new();

		protected internal Vector2 localXAxis;
		protected internal Vector2 localYAxis;

		protected Vector2 lastPos;
		protected float lastRot;

		public override void Tick()
		{
			if(GameObject is { Transform: { } })
			{
				float cos = Leviamath.Cos(GameObject.Transform.Rotation);
				float sin = Leviamath.Sin(GameObject.Transform.Rotation);

				localXAxis = new Vector2(cos, sin).Normalized;
				localYAxis = new Vector2(-sin, cos).Normalized;

				lastPos = GameObject.Transform.Position;
				lastRot = GameObject.Transform.Rotation;
			}
		}

		public override void PhysicsTick()
		{
			if(isTrigger)
			{
				for(int i = 0; i < objectsInside.Count; i++)
				{
					Collider collider = objectsInside[i];
					
					if(!objectsInsideThisFrame.Contains(collider))
					{
						ProcessTriggerExit(collider);
						
						objectsInside.RemoveAt(i);
						i--;
					}
				}
				
				objectsInsideThisFrame.Clear();
			}
		}

		protected internal void TryTriggerEnter(Collider _other)
		{
			if(isTrigger && !objectsInside.Contains(_other))
			{
				ProcessTriggerEnter(_other);
				objectsInside.Add(_other);
			}
		}

		private void ProcessTriggerEnter(Collider _collider)
		{
			if(_collider.GameObject is not { })
				return;

			IPhysicsHandler[] handlers = _collider.GameObject.components
			                                      .Where(_c => _c is IPhysicsHandler)
			                                      .Cast<IPhysicsHandler>()
			                                      .ToArray();

			foreach(IPhysicsHandler handler in handlers)
				handler.OnTriggerEnter(this);
		}

		private void ProcessTriggerStay(Collider _collider)
		{
			if(_collider.GameObject is not { })
				return;

			IPhysicsHandler[] handlers = _collider.GameObject.components
			                                            .Where(_c => _c is IPhysicsHandler)
			                                            .Cast<IPhysicsHandler>()
			                                            .ToArray();

			foreach(IPhysicsHandler handler in handlers)
				handler.OnTriggerStay(this);
		}

		private void ProcessTriggerExit(Collider _collider)
		{
			if(_collider.GameObject is not { })
				return;

			IPhysicsHandler[] handlers = _collider.GameObject.components
			                                            .Where(_c => _c is IPhysicsHandler)
			                                            .Cast<IPhysicsHandler>()
			                                            .ToArray();

			foreach(IPhysicsHandler handler in handlers)
				handler.OnTriggerExit(this);
		}
	}
}