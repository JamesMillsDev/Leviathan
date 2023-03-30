using Leviathan.GameObjects;
using Leviathan.Resources;

namespace Leviathan.Events
{
	public class ConfigReloadEvent : BaseEvent
	{
		
	}

	public abstract class GameObjectEvent : BaseEvent
	{
		public readonly GameObject? gameObject;

		protected GameObjectEvent(GameObject _gameObject) => gameObject = _gameObject;
	}

	public class GameObjectSpawnedEvent : GameObjectEvent
	{
		public GameObjectSpawnedEvent(GameObject _gameObject) : base(_gameObject) { }
	}

	public class GameObjectDestroyedEvent : GameObjectEvent
	{
		public GameObjectDestroyedEvent(GameObject _gameObject) : base(_gameObject) { }
	}

	public class ResourceManagerLoadEvent : BaseEvent
	{
		public readonly ResourceManager resourceManager;

		public ResourceManagerLoadEvent(ResourceManager _resourceManager) => resourceManager = _resourceManager;
	}

	public class ResourceManagerCleanupEvent : BaseEvent
	{
		public readonly ResourceManager resourceManager;

		public ResourceManagerCleanupEvent(ResourceManager _resourceManager) => resourceManager = _resourceManager;
	}
}