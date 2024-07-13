#pragma once

#include "Move.h"

#include <array>
#include <cstdint>
#include <memory>
#include <optional>
#include <vector>

template <int32_t NUMBER_OF_PLAYERS> class GameStateIf
{
public:
  virtual ~GameStateIf() = default;
  virtual bool isTerminal() = 0;
  virtual std::array<int32_t, NUMBER_OF_PLAYERS> evaluate() = 0;
  virtual std::vector<Move> getPossibleMoves() = 0;
  virtual std::shared_ptr<GameStateIf<NUMBER_OF_PLAYERS>> applyMove(const Move) = 0;
  virtual std::optional<int32_t> getWinner() = 0;
  virtual void show() = 0;
};