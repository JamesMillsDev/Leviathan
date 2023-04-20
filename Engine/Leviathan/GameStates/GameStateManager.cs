using Leviathan.Debugging;

namespace Leviathan.GameStates
{
	public class GameStateManager : Singleton<GameStateManager>
	{
		private static readonly Logger logger = new("GameStateManager");

		private static readonly List<Action> updateStatesActions = new();

		public static void Add(IGameState _state)
		{
			if(Instance == null)
			{
				logger.LogException(new NullReferenceException("Not yet initialised!"));

				return;
			}

			if(!Instance.states.ContainsKey(_state.ID))
				Instance.states.Add(_state.ID, _state);
		}

		public static void Enter(string _state)
		{
			if(Instance == null)
			{
				logger.LogException(new NullReferenceException("Not yet initialised!"));

				return;
			}

			if(Instance.states.ContainsKey(_state))
			{
				updateStatesActions.Add(() =>
				{
					Instance.states[_state].Enter();
					Instance.active.Add(Instance.states[_state]);
				});
			}
		}

		public static void Exit(string _state)
		{
			if(Instance == null)
			{
				logger.LogException(new NullReferenceException("Not yet initialised!"));

				return;
			}

			if(Instance.states.ContainsKey(_state) && Instance.active.Contains(Instance.states[_state]))
			{
				updateStatesActions.Add(() =>
				{
					Instance.states[_state].Exit();
					Instance.active.Remove(Instance.states[_state]);
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

			Instance.active.ForEach(_state => _state.Render());
		}

		internal static void Tick()
		{
			if(Instance == null)
			{
				logger.LogException(new NullReferenceException("Not yet initialised!"));

				return;
			}

			foreach(Action action in updateStatesActions)
				action();

			updateStatesActions.Clear();
			
			Instance.active.ForEach(_state => _state.Tick());
		}

		internal static void OnRenderGizmos()
		{
			if(Instance == null)
			{
				logger.LogException(new NullReferenceException("Not yet initialised!"));

				return;
			}

			Instance.active.ForEach(_state => _state.OnRenderGizmos());
		}

		private readonly Dictionary<string, IGameState> states = new();
		private readonly List<IGameState> active = new();
	}
}