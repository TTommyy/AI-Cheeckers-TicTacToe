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
  virtual ~GameStateIf() = default;
  virtual bool isTerminal() const = 0;
  virtual std::array<int32_t, NUMBER_OF_PLAYERS> const evaluate() = 0;
  virtual std::vector<std::shared_ptr<MoveIf>> const getPossibleMoves() = 0;
  virtual std::unique_ptr<GameStateIf<NUMBER_OF_PLAYERS>> const applyMove(const std::shared_ptr<MoveIf>) = 0;
  virtual std::optional<int32_t> const getWinner() = 0;
};
