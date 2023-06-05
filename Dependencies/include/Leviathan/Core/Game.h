#pragma once

#include <Leviathan/Core/Object.h>

class Game : public Object
{
public:
	virtual ~Game() = default;

protected:
	friend class Application;

	virtual void Load() = 0;
	virtual void Unload() {}

	virtual void Tick() {}
	virtual void Render() {}

};