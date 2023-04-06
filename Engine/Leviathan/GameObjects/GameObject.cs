using Raylib_cs;

using Transform = Leviathan.GameObjects.Components.Transform;

namespace Leviathan.GameObjects
{
	public class GameObject
	{
		public bool IsActive { get; set; }

		// ReSharper disable once UnusedAutoPropertyAccessor.Global
		// ReSharper disable once AutoPropertyCanBeMadeGetOnly.Global
		public string? Name { get; set; }

		public Transform? Transform { get; }

		public Rectangle Bounds => Transform == null ? default : new Rectangle(Transform.Position.x, Transform.Position.y, Transform.Scale.x, Transform.Scale.y);

		internal readonly List<Component> components = new();

		public GameObject(string? _name)
		{
			Name = _name;

			// This will be the only component that CANNOT be added / removed from the components list
			Transform = new Transform();
		}

		public COMPONENT? AddComponent<COMPONENT>(params object[] _data) where COMPONENT : Component, new()
		{
			if(typeof(COMPONENT) == typeof(Transform))
				return default;

			COMPONENT component = new();
			component.SetGameObject(this);
			component.Start(_data);
			components.Add(component);

			return component;
		}

		public void RemoveComponent<COMPONENT>(COMPONENT? _component) where COMPONENT : Component
		{
			// Prevent the removal of transform components
			if(typeof(COMPONENT) == typeof(Transform))
				return;

			if(_component != null && components.Contains(_component))
			{
				components.Remove(_component);
				_component.OnDestroy();
			}
		}

		public COMPONENT? GetComponent<COMPONENT>() where COMPONENT : Component
		{
			return (COMPONENT?) components.FirstOrDefault(_component => _component is COMPONENT);
		}

		public COMPONENT?[] GetComponents<COMPONENT>() where COMPONENT : Component
		{
			return components.Where(_component => _component is COMPONENT).Cast<COMPONENT>().ToArray();
		}

		public bool TryGetComponent<COMPONENT>(out COMPONENT? _component) where COMPONENT : Component
		{
			_component = GetComponent<COMPONENT>();

			return _component != null;
		}
	}
}