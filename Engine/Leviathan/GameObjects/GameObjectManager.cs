using Leviathan.Debugging;
using Leviathan.Events;

namespace Leviathan.GameObjects
{
	public class GameObjectManager : Singleton<GameObjectManager>
	{
		public static IEnumerable<GameObject?> All => Instance == null ? new List<GameObject?>() : Instance.gameObjects;
		
		internal static bool TickComplete { get; private set; }

		private static readonly Logger logger = new("GameObjectManager");

		public static void Spawn(GameObject? _gameObject)
		{
			if(Instance == null)
			{
				logger.LogException(new NullReferenceException("Not yet initialised!"));

				return;
			}
			
			if(!Instance.gameObjects.Contains(_gameObject) && _gameObject != null)
			{
				Instance.listUpdates.Add(() =>
				{
					Instance.gameObjects.Add(_gameObject);
					EventBus.Raise(new GameObjectSpawnedEvent(_gameObject));
				});
			}
		}

		public static void Destroy(GameObject? _gameObject)
		{
			if(Instance == null)
			{
				logger.LogException(new NullReferenceException("Not yet initialised!"));

				return;
			}
			
			if(Instance.gameObjects.Contains(_gameObject) && _gameObject != null)
			{
				Instance.listUpdates.Add(() =>
				{
					foreach(Component? component in _gameObject.components)
						component.OnDestroy();

					Instance.gameObjects.Remove(_gameObject);
					EventBus.Raise(new GameObjectDestroyedEvent(_gameObject));
				});
			}
		}

		internal static void Render()
		{
			if(Instance == null)
			{
				logger.LogException(new NullReferenceException("Not yet initialised!"));

				return;
			}
			
			Instance.gameObjects.ForEach(_go => _go?.components.ForEach(_c => _c.Render()));
		}

		internal static void Tick()
		{
			if(Instance == null)
			{
				logger.LogException(new NullReferenceException("Not yet initialised!"));

				return;
			}

			TickComplete = false;
			
			Instance.listUpdates.ForEach(_update => _update());
			Instance.listUpdates.Clear();

			Instance.gameObjects.ForEach(_go =>
			{
				if(_go == null)
					return;
				
				_go.components.ForEach(_c =>
				{
					_c.Tick();
				});
			});

			TickComplete = true;
		}

		internal static void OnRenderGizmos()
		{
			if(Instance == null)
			{
				logger.LogException(new NullReferenceException("Not yet initialised!"));

				return;
			}

			Instance.gameObjects.ForEach(_go => _go?.components.ForEach(_c => _c.OnRenderGizmos()));
		}

		private readonly List<GameObject?> gameObjects = new();
		private readonly List<Action> listUpdates = new();
	}
}