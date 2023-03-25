using Leviathan.GameObjects;

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
}