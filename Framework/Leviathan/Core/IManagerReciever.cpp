#include <Leviathan/Core/IManagerReciever.h>

#include <Leviathan/Core/GameManagers.h>

GameStateManager* IManagerReciever::GetStateManager()
{
    return GameManagers::m_stateManager;
}

GameObjectManager* IManagerReciever::GetObjectManager()
{
    return GameManagers::m_objectManager;
}

GameTimerManager* IManagerReciever::GetTimerManager()
{
    return GameManagers::m_timerManager;
}
