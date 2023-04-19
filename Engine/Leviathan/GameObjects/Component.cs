namespace Leviathan.GameObjects
{
	public class Component
	{
		protected GameObject? GameObject { get; set; }

		internal void SetGameObject(GameObject _gameObject) => GameObject = _gameObject;

		public virtual void Start(params object[] _data) { }

		public virtual void Tick() { }

		public virtual void PhysicsTick(float _timeStep) { }

		public virtual void Render() { }

		public virtual void OnDestroy() { }

		public virtual void OnRenderGizmos() { }
	}
}