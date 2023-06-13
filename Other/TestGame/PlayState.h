#pragma once

#include <Leviathan/GameStates/IGameState.h>

#include <Leviathan/Utils/GameTimerManager.h>

using Leviathan::IGameState;
using Leviathan::TimerHandle;

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