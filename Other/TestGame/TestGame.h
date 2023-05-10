#pragma once

#include <Leviathan/Game.h>

class TestGame : public Game
{
protected:
	virtual void Load() override;
	virtual void Unload() override;

	virtual void Tick() override;
	virtual void Render() override;

};