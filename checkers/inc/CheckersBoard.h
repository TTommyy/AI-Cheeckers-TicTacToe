#pragma once

#include "CheckersBoardIf.h"

class CheckersBorad : public CheckersBoardIf
{
public:
  CheckersBorad();
  Board getBoard() const override;
  std::string toString() const override;
  std::vector<MoveIf> getPossibleMoves(const PlayerE&) override;

private:
  Board m_board;
};