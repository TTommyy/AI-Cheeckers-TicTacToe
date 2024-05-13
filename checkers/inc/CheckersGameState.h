//
// Created by tomek on 10.05.2024.
//

#pragma once
#include "../../alg/GameStateIf.h"
#include "../../alg/Move.h"
#include "CheckersBoardIf.h"

#include <string>

class CheckersGameState : public GameStateIf<2>
{
public:
  CheckersGameState();
  bool isTerminal() const override;
  std::array<int32_t, 2> evaluate() const override;
  std::vector<std::shared_ptr<MoveIf>> getPossibleMoves() const overide;
  std::unique_ptr<GameStateIf<2>> applyMove(const std::shared_ptr<MoveIf>) const override;
  std::optional<int32_t> getWinner() const override;

private:
  std::unique_ptr<CheckersBoardIf> m_board_ptr;
};
