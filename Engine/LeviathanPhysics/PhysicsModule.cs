using Leviathan.GameObjects;

namespace Leviathan.Physics
{
	internal class PhysicsModule : ILeviathanModule
	{
		private PhysicsTree? container;

		public void Load()
		{
			if(Application.Window == null)
				return;

			GameObjectManager.onObjectSpawned += OnObjectSpawned;
			container = new PhysicsTree(Application.Window.ScreenBounds);
		}

		public void OnDrawGizmos()
		{
			container?.Visualise();
		}

		public void Unload()
		{
			container = null;
			GameObjectManager.onObjectDestroyed += OnObjectDestroyed;
		}

		private void OnObjectSpawned(GameObject? _gameObject)
		{
			if(_gameObject == null)
				return;
			
			if(_gameObject.TryGetComponent(out Collider? collider) && collider != null)
				collider.data = container?.Insert(new PhysicsTreeData(collider, _gameObject.Bounds));
		}

		private void OnObjectDestroyed(GameObject? _gameObject)
		{
			if(_gameObject == null)
				return;
			
			if(_gameObject.TryGetComponent(out Collider? collider) && collider is { data: { } })
				container?.Remove(collider.data);
		}
	}
}