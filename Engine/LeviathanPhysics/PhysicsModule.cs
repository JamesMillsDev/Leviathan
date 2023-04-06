using Leviathan.Events;
using Leviathan.GameObjects;
using Leviathan.Physics.Components;
using Leviathan.Physics.Shapes;

using System.Diagnostics;

namespace Leviathan.Physics
{
	internal class PhysicsModule : ILeviathanModule, IEventHandler
	{
		private PhysicsGraph? container;

		public void Load()
		{
			if(Application.Window == null)
				return;

			EventBus.RegisterObject(this);

			container = new PhysicsGraph(Application.Window.ScreenBounds);
		}

		public void Tick()
		{
			Stopwatch stopwatch = new();
			stopwatch.Start();

			List<Collider> startCollisions = new();
			List<Collider> stayCollisions = new();
			
			foreach(GameObject? gameObject in GameObjectManager.All)
			{
				startCollisions.Clear();
				stayCollisions.Clear();
				
				// It should never be null, but for safety we will check anyway
				if(gameObject is { Transform: { } } && container is { })
				{
					IPhysicsHandler[] handlers = gameObject.components.Where(_comp => _comp is IPhysicsHandler)
					                                     .Cast<IPhysicsHandler>()
					                                     .ToArray();
					
					foreach(Collider? collider in gameObject.GetComponents<Collider>())
					{
						if(collider is { })
						{
							List<Collider> lastCollisions = collider.collisions;

							Rectangle queryRange = new()
							{
								center = gameObject.Transform.Position,
								size = collider.Bounds.size * 2.0f
							};

							collider.collisions = container.Query(queryRange)
							                               .Where(_q => _q != collider)
							                               .Where(_q => collider.CheckCollision(_q))
							                               .ToList();

							foreach(Collider collision in collider.collisions)
							{
								if(lastCollisions.Contains(collision))
								{
									lastCollisions.Remove(collision);
									stayCollisions.Add(collision);
								}
								else
								{
									startCollisions.Add(collision);
								}
							}

							if(lastCollisions.Count > 0 || startCollisions.Count > 0 || stayCollisions.Count > 0)
							{
								foreach(IPhysicsHandler handler in handlers)
								{
									foreach(Collider lastCollision in lastCollisions)
									{
										handler.OnTriggerExit(lastCollision);
									}

									foreach(Collider startCollision in startCollisions)
									{
										handler.OnTriggerEnter(startCollision);
									}

									foreach(Collider stayCollision in stayCollisions)
									{
										handler.OnTriggerStay(stayCollision);
									}
								}
							}
						}
					}
				}
			}
			
			stopwatch.Stop();
			Console.WriteLine(stopwatch.ElapsedMilliseconds);
		}

		public void OnDrawGizmos()
		{
			container?.Visualise();
		}

		public void Unload()
		{
			EventBus.RemoveObject(this);

			container = null;
		}

		[SubscribeEvent]
		// ReSharper disable once UnusedMember.Local
		private void OnObjectSpawned(GameObjectSpawnedEvent _event)
		{
			if(_event.gameObject == null)
				return;

			if(_event.gameObject.TryGetComponent(out Collider? collider) && collider != null)
				collider.data = container?.Insert(new PhysicsTreeData(collider, _event.gameObject.Bounds));
		}

		[SubscribeEvent]
		// ReSharper disable once UnusedMember.Local
		private void OnObjectDestroyed(GameObjectDestroyedEvent _event)
		{
			if(_event.gameObject == null)
				return;

			if(_event.gameObject.TryGetComponent(out Collider? collider) && collider is { data: { } })
				container?.Remove(collider.data);
		}
	}
}