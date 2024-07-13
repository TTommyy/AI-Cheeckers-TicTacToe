#pragma once

#include "CheckersBoardIf.h"

class CheckersBoard : public CheckersBoardIf
{
public:
using CapcturesVector = std::vector<std::pair<Move::Field ,std::vector<Move::Field>>>;
  CheckersBoard();
  std::string toString() const override;
  std::vector<Move> getPossibleMoves(const PlayerE&) const override;
  void show() override;
  Board getBoard() const override;
  void setBoard(Board) override;

private:
  void intializeBoard();
  CapcturesVector checkIfManCanKill(int32_t, int32_t, const PlayerE&, std::vector<Move::Field>, Board) const;
  CapcturesVector checkIfKingCanKill(int32_t, int32_t, const PlayerE&, std::vector<Move::Field>, Board) const;
  std::vector<Move> checkIfManCanMove(int32_t, int32_t, const PlayerE&) const;
  std::vector<Move> checkIfKingCanMove(int32_t, int32_t) const;
  bool validField(int32_t, int32_t) const;
  bool checkIfOnField(int32_t, int32_t, const PlayerE, const Board&) const;
  bool checkIfEmpty(int32_t, int32_t, const Board&) const;
  Board m_board;
};