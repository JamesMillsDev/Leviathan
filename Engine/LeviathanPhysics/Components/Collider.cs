using Leviathan.GameObjects;
using Leviathan.Mathematics;
using Leviathan.Physics.Structures.Graphs;

namespace Leviathan.Physics.Components
{
	public abstract class Collider : Component
	{
		internal abstract CollisionFunctions.Shape Shape { get; }
		
		public bool isTrigger = false;
		
		internal PhysicsTreeData? data;

		private readonly List<Collider> objectsInside = new();
		private readonly List<Collider> objectsInsideThisFrame = new();

		internal Vector2 localXAxis;
		internal Vector2 localYAxis;

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

		public override void PhysicsTick(float _timeStep)
		{
			if(isTrigger)
			{
				List<Collider> objectsStaying = new();

				for(int i = 0; i < objectsInside.Count; i++)
				{
					Collider collider = objectsInside[i];
					
					if(!objectsInsideThisFrame.Contains(collider))
					{
						ProcessTriggerExit(collider);
						
						objectsInside.RemoveAt(i);
						i--;
					}
					else
					{
						objectsStaying.Add(collider);
					}
				}

				foreach(Collider collider in objectsStaying)
					ProcessTriggerStay(collider);

				objectsInsideThisFrame.Clear();
			}
		}

		internal void ResolveCollision(Collider _other, Collision _collision)
		{
			if(!objectsInsideThisFrame.Contains(_other))
				objectsInsideThisFrame.Add(_other);

			if(!isTrigger && !_other.isTrigger)
			{
				// This is a hard collision
			}
			else
			{
				ProcessTriggerEnter(_other);
			}
		}

		private void ProcessTriggerEnter(Collider _collider)
		{
			if(_collider.GameObject is not { })
				return;
			
			if(!objectsInside.Contains(_collider))
				objectsInside.Add(_collider);

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