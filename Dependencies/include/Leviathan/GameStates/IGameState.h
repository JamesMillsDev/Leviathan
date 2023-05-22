#pragma once

class IGameState
{
public:
	virtual ~IGameState() = default;
	virtual void Load() = 0;
	virtual void Tick() {}
	virtual void Render() {}
	virtual void Unload() {}

protected:
	class GameStateManager* m_stateManager;
	class GameObjectManager* m_goManager;

protected:
	IGameState(class GameStateManager* _stateManager, class GameObjectManager* _goManager, const char* _id)
		: m_name(_id), m_stateManager(_stateManager), m_goManager(_goManager) {}

private:
	friend class GameStateManager;

	const char* m_name;

};