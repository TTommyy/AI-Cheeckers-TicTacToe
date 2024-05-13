//
// Created by tomek on 10.05.2024.
//

#pragma once

#include "MoveIf.h"

#include <array>
#include <cstdint>
#include <memory>
#include <optional>
#include <vector>

template <int32_t NUMBER_OF_PLAYERS> class GameStateIf {
public:
  virtual ~GameStateIf() = default;
  virtual bool isTerminal() const = 0;
  virtual std::array<int32_t, NUMBER_OF_PLAYERS> evaluate() const = 0;
  virtual std::vector<std::shared_ptr<MoveIf>> getPossibleMoves() const = 0;
  virtual std::unique_ptr<GameStateIf<NUMBER_OF_PLAYERS>> applyMove(const std::shared_ptr<MoveIf>) const = 0;
  virtual std::optional<int32_t> getWinner() const = 0;
};