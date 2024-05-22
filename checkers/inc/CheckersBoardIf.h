#pragma once
#include "FigureTypeE.h"
#include "PlayerE.h"
#include "Move.h"

#include <utility>
#include <array>
#include <string>
#include <vector>

constexpr int8_t BOARD_SIZE = 8;
class CheckersBoardIf 
{
public:
  using Board = std::array<std::array<FigureTypeE, BOARD_SIZE>, BOARD_SIZE>;
  virtual ~CheckersBoardIf() = default;
  virtual std::string toString() const = 0;
  virtual std::vector<Move> getPossibleMoves(const PlayerE&) const = 0;
  virtual void show() const = 0;
  virtual Board getBoard() const = 0;
  virtual void setBoard(Board) = 0;
  int8_t gerBoardSize(){ return BOARD_SIZE; }
};