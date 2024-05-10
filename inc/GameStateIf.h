//
// Created by tomek on 10.05.2024.
//

#pragma once

#include "MoveIf.h"

#include <cstdint>
#include <array>
#include <vector>
#include <optional>
#include <memory>

template<int32_t NUMBER_OF_PLAYERS>
class GameStateIf
{
public:
    virtual bool isTerminal() = 0;
    virtual std::array<int32_t, NUMBER_OF_PLAYERS> evaluate() = 0;
    virtual std::vector<std::shared_ptr<MoveIf>> getPossibleMoves() = 0;
    virtual std::unique_ptr<GameStateIf<NUMBER_OF_PLAYERS>> applyMove(const std::shared_ptr<MoveIf>) = 0;
    virtual std::optional<int32_t> getWinner() = 0;
};
