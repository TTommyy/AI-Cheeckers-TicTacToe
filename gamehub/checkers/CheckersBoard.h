#pragma once

#include "CheckersBoardIf.h"

class CheckersBoard : public CheckersBoardIf
{
public:
using CapcturesVector = std::vector<std::pair<CheckersMove::Field ,std::vector<CheckersMove::Field>>>;
  CheckersBoard();
  std::string toString() const override;
  std::vector<CheckersMove> getPossibleMoves(const PlayerE&) const override;
  void show() override;
  Board getBoard() const override;
  void setBoard(Board) override;

private:
  void intializeBoard();
  CapcturesVector checkIfManCanKill(int32_t, int32_t, const PlayerE&, std::vector<CheckersMove::Field>, Board) const;
  CapcturesVector checkIfKingCanKill(int32_t, int32_t, const PlayerE&, std::vector<CheckersMove::Field>, Board) const;
  std::vector<CheckersMove> checkIfManCanMove(int32_t, int32_t, const PlayerE&) const;
  std::vector<CheckersMove> checkIfKingCanMove(int32_t, int32_t) const;
  bool validField(int32_t, int32_t) const;
  bool checkIfOnField(int32_t, int32_t, const PlayerE, const Board&) const;
  bool checkIfEmpty(int32_t, int32_t, const Board&) const;
  Board m_board;
};