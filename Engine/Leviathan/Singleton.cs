namespace Leviathan
{
	/// <summary>A base class for singletons that handles references of it.</summary>
	/// <typeparam name="T">The type the singleton is. This is what is returned when you access the <see cref="Instance"/>.</typeparam>
	public abstract class Singleton<T> where T : Singleton<T>, new()
	{
		/// <summary>The Singleton Instance. Can be accessed anywhere.</summary>
		// ReSharper disable once MemberCanBeProtected.Global
		public static T? Instance { get; private set; }

		/// <summary>Sets the instance to null and calls <see cref="OnDestroy"/>.</summary>
		public static void CreateInstance()
		{
			Instance = new T();
			Instance.OnCreate();
		}

		/// <summary>Sets the instance to null and calls <see cref="OnDestroy"/>.</summary>
		public static void DestroyInstance()
		{
			Instance?.OnDestroy();
			Instance = null;
		}

		/// <summary>Used to setup any initial values on the singleton.</summary>
		protected virtual void OnCreate() { }

		/// <summary>Used to clean up any values on the singleton.</summary>
		protected virtual void OnDestroy() { }
	}
}