using Leviathan.Debugging;
using Leviathan.Structures.Trees.Quad;

using Raylib_cs;

namespace Leviathan.GameObjects
{
	public class GameObjectManager : Singleton<GameObjectManager>
	{
		public static IEnumerable<GameObject?> All => Instance == null ? new List<GameObject?>() : Instance.gameObjects;

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
					_gameObject.quadTreeData = Instance.objectTree?.Insert(new QuadTreeData<GameObject?>(_gameObject, _gameObject.Bounds));
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
					if(_gameObject.quadTreeData != null)
						Instance.objectTree?.Remove(_gameObject.quadTreeData);
				});
			}
		}

		public static List<GameObject?> GetAllInBounds(Rectangle _bounds)
		{
			if(Instance == null)
			{
				logger.LogException(new NullReferenceException("Not yet initialised!"));

				return new List<GameObject?>();
			}

			return Instance.objectTree != null ? Instance.objectTree.Query(_bounds) : new List<GameObject?>();
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
			
			Instance.listUpdates.ForEach(_update => _update());
			Instance.listUpdates.Clear();

			Instance.gameObjects.ForEach(_go =>
			{
				if(_go == null)
					return;
				
				if(_go.Transform!.HasChanged && Instance.objectTree != null)
				{
					_go.quadTreeData!.bounds = _go.Bounds;
					Instance.objectTree.Update(_go.quadTreeData);
				}
				
				_go.components.ForEach(_c =>
				{
					_c.Tick();
					_c.PhysicsTick();
				});
			});
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
		private QuadTree<GameObject?>? objectTree;

		protected override void OnCreate() => objectTree = new QuadTree<GameObject?>(Application.Window!.ScreenBounds);
	}
}