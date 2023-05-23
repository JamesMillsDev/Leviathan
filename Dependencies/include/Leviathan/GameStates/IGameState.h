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
	class GameManagers* m_gameManagers;

protected:
	IGameState(class GameManagers* _gameManagers, const char* _id)
		: m_name(_id), m_gameManagers(_gameManagers) {}

private:
	friend class GameStateManager;

	const char* m_name;

};