//
// Created by tomek on 10.05.2024.
//

#pragma once
#include "GameStateIf.h"
#include "Move.h"
#include "CheckersBoardIf.h"

#include <string>

class CheckersGameState : public GameStateIf<2>
{
public:
  CheckersGameState();
  CheckersGameState(std::shared_ptr<CheckersBoardIf>, PlayerE);
  bool isTerminal() const override;
  std::array<int32_t, 2> evaluate() const override;
  std::vector<Move> getPossibleMoves() const override;
  std::shared_ptr<GameStateIf<2>> applyMove(const Move) const override;
  std::optional<int32_t> getWinner() const override;
  void show() const override;

private:
  std::shared_ptr<CheckersBoardIf> m_board_ptr;
  PlayerE m_to_move;
};
