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
	IGameState(const char* _id) : m_name(_id) {}

private:
	friend class GameStateManager;

	const char* m_name;

};