using Leviathan.Debugging;

using Raylib_cs;

namespace Leviathan.UI
{
	// ReSharper disable once InconsistentNaming
	public class UIManager : Singleton<UIManager>
	{
		private static readonly Logger logger = new("UIManager");

		public static void Add(Widget _widget)
		{
			if(Instance == null)
			{
				logger.LogException(new NullReferenceException("Not yet initialised!"));

				return;
			}
			
			if(!Instance.widgets.Contains(_widget))
				Instance.widgets.Add(_widget);
		}

		public static void Remove(Widget _widget)
		{
			if(Instance == null)
			{
				logger.LogException(new NullReferenceException("Not yet initialised!"));

				return;
			}
			
			if(Instance.widgets.Contains(_widget))
				Instance.widgets.Remove(_widget);
		}

		internal static void Render()
		{
			if(Instance == null)
			{
				logger.LogException(new NullReferenceException("Not yet initialised!"));

				return;
			}
			
			Instance.widgets.ForEach(_widget => _widget.Render());
		}

		internal static void Tick()
		{
			if(Instance == null)
			{
				logger.LogException(new NullReferenceException("Not yet initialised!"));

				return;
			}
			
			Instance.widgets.Sort();
			Instance.widgets.ForEach(_widget => _widget.Tick(Raylib.GetMousePosition()));
		}

		private readonly List<Widget> widgets = new();
	}
}