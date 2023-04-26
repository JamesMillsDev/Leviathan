#pragma once

#include <Leviathan/Game.h>

class TestGame : public Game
{
protected:
	virtual void Load() override;
	virtual void Render() override;

};

