#pragma once

#include <Leviathan/Core/Leviathan.h>

class IManagerReciever
{
protected:
	DLL class GameStateManager* GetStateManager();
	DLL class GameObjectManager* GetObjectManager();
	DLL class GameTimerManager* GetTimerManager();

};

