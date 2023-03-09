namespace Leviathan.Resources
{
	/// <summary>The base resource class that contains the bulk of the functionality for handling game resources.</summary>
	/// <typeparam name="T">The type of resource that is being managed.</typeparam>
	public abstract class Resource<T> : IDisposable
	{
		/// <summary>The delegate for Raylib's Loading functions so that one variable can be used as a mask for all implementations.</summary>
		protected delegate T LoadDelegate(string _path);
		
		/// <summary>The delegate for Raylib's Unloading functions so that one variable can be used as a mask for all implementations.</summary>
		protected delegate void UnloadDelegate(T _asset);

		/// <summary>The pointer to the actual resource that is being handled by the system. The type is dependant on the resource that is implementing this class.</summary>
		public T? Value
		{
			get
			{
				// If the resource hasn't been loaded yet, attempt to load it.
				if(!IsLoaded)
				{
					Application.raylibLogger?.LogDebug($"Loading resource {typeof(T).Name} at path {path.Substring(path.IndexOf("assets", StringComparison.Ordinal))}.");
					resource = load(path);
				}

				return resource;
			}
		}

		/// <summary>The abstract boolean for determining if the resource has actually been requested/loaded yet.</summary>
		protected abstract bool IsLoaded { get; }

		/// <summary>The actual internal resource handle for the managed asset.</summary>
		protected T? resource;

		/// <summary>The delegate for the function that gets called when a load is requested.</summary>
		private readonly LoadDelegate load;
		/// <summary>The delegate for the function that gets called when the resource needs to be released.</summary>
		private readonly UnloadDelegate unload;

		/// <summary>The path to the physical resource on the file system.</summary>
		private readonly string path;

		/// <param name="_load">The delegate used to load the resource.</param>
		/// <param name="_unload">The delegate used to unload the resource.</param>
		/// <param name="_path">The absolute path to the resource.</param>
		protected Resource(LoadDelegate _load, UnloadDelegate _unload, string _path)
		{
			load = _load;
			unload = _unload;
			path = _path;
		}

		/// <summary>Gets called when the memory for the resource needs to be cleared.</summary>
		public void Dispose()
		{
			if(IsLoaded && resource != null)
				unload(resource);
			
			GC.SuppressFinalize(this);
		}

		/// <summary>A quick implicit casting to allow all resource types to function as their respective Raylib counterparts</summary>
		/// <param name="_resource">The base resource type that is being casted from.</param>
		/// <returns>The Raylib resource associated with the type.</returns>
		public static implicit operator T?(Resource<T> _resource) => _resource.resource;
	}
}