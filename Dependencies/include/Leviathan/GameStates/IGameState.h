#pragma once

class IGameState
{
public:
	virtual void Load() = 0;
	virtual void Tick() {}
	virtual void Render() {}
	virtual void Unload() {}

protected:
	IGameState(char* _id) : m_name(_id) {}

private:
	friend class GameStateManager;

	char* m_name;

};