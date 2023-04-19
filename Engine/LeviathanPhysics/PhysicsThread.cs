using Leviathan.GameObjects;
using Leviathan.Physics.Components;
using Leviathan.Physics.Structures.Graphs;
using Leviathan.Structures;

using System.Diagnostics.CodeAnalysis;

namespace Leviathan.Physics
{
	internal static class PhysicsThread
	{
		internal const float TIME_STEP = 0.01f;

		private static float accumulatedTime;
		
		internal static async void WorkerFunction(PhysicsGraph? _graph)
		{
			while(Application.IsRunning)
			{
				if(_graph is not { })
					return;

				await LeviathanTasks.WhenComplete(() => GameObjectManager.TickComplete);

				accumulatedTime += Time.deltaTime;

				while(accumulatedTime >= TIME_STEP)
				{
					foreach(GameObject? gameObject in GameObjectManager.All)
						gameObject?.components.ForEach(_c => _c.PhysicsTick(TIME_STEP));
					
					accumulatedTime -= TIME_STEP;
					
					foreach(GameObject? gameObject in GameObjectManager.All)
					{
						if(gameObject is { })
						{
							IEnumerable<Collider?> aColliders = gameObject.GetComponents<Collider>();
							IEnumerable<Collider?> queried = _graph.Query(gameObject.Bounds.Scaled(2.0f))
							                                       .Where(_q => !aColliders.Contains(_q));

							CheckAgainst(aColliders, queried);
						}
					}
				}
			}
		}

		[SuppressMessage("ReSharper", "PossibleMultipleEnumeration")]
		private static void CheckAgainst(IEnumerable<Collider?> _current, IEnumerable<Collider?> _queried)
		{
			foreach(Collider? collider in _current)
			{
				foreach(Collider? other in _queried)
				{
					CheckCollisions(collider, other);
				}
			}
		}

		private static void CheckCollisions(Collider? _a, Collider? _b)
		{
			if(_a is not { } || _b is not { })
				return;
			
			int id1 = (int) _a.Shape;
			int id2 = (int) _b.Shape;
			
			int funcIndex = id1 * (int) CollisionFunctions.Shape.Max + id2;
			CollisionFunctions.collisionFunctions[funcIndex](_a, _b);
		}
	}
}