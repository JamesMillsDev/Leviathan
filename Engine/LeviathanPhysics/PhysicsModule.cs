using Leviathan.Events;
using Leviathan.GameObjects;
using Leviathan.Physics.Components;

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
			if(container is not { })
				return;

			Stopwatch stopwatch = new();
			stopwatch.Start();

			foreach(GameObject? gameObject in GameObjectManager.All)
			{
				if(gameObject is { })
				{
					List<Collider?> aColliders = new(gameObject.GetComponents<Collider>());

					Collider?[] queried = container.Query(gameObject.Bounds.Scaled(2.0f))
					                               .Where(_q => !aColliders.Contains(_q))
					                               .ToArray();

					foreach(Collider? collider in aColliders)
					{
						if(collider is { })
						{
							int id1 = (int) collider.Shape;

							foreach(Collider? other in queried)
							{
								if(other is { })
								{
									int id2 = (int) other.Shape;
									if(id1 >= 0 && id2 >= 0)
									{
										int funcIndex = id1 * (int) CollisionFunctions.Shape.Max + id2;
										Collision? collision = CollisionFunctions.collisionFunctions[funcIndex](collider, other);
										
										if(collision != null)
										{
											Console.WriteLine("COLLISION");
										}
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