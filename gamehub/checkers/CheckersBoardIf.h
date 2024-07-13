#pragma once
#include "FigureTypeE.h"
#include "PlayerE.h"
#include "CheckersMove.h"

#include <utility>
#include <array>
#include <string>
#include <vector>

constexpr int32_t BOARD_SIZE = 8;
class CheckersBoardIf 
{
public:
  using Board = std::array<std::array<FigureTypeE, BOARD_SIZE>, BOARD_SIZE>;
  virtual ~CheckersBoardIf() = default;
  virtual std::string toString() const = 0;
  virtual std::vector<CheckersMove> getPossibleMoves(const PlayerE&) const = 0;
  virtual void show() = 0;
  virtual Board getBoard() const = 0;
  virtual void setBoard(Board) = 0;
  int32_t gerBoardSize(){ return BOARD_SIZE; }
};