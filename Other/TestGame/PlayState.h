#pragma once

#include <Leviathan/GameStates/IGameState.h>

class PlayState final : public IGameState
{
public:
    PlayState();
    virtual ~PlayState();

    void Load() override;
    void Tick() override;

    void Unload() override;

};