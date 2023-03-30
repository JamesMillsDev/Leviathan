#pragma once

class game
{
protected:
	friend class application;

	virtual void load() = 0;
	virtual void unload() {}

	virtual void tick() {}
	virtual void render() {}

};