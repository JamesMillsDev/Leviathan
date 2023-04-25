#pragma once

class Game
{
protected:
	friend class Application;

	virtual void Load() = 0;
	virtual void Unload() {}

	virtual void Tick() {}
	virtual void Render() {}

};