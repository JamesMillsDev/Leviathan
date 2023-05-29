#pragma once

#include <Leviathan/GameStates/IGameState.h>

#include <Leviathan/Utils/GameTimerManager.h>

class PlayState final : public IGameState
{
public:
    PlayState();
    virtual ~PlayState();

    void Load() override;
    void Tick() override;

    void Unload() override;

    void DelayTest();

    TimerHandle m_timerHandle;

};