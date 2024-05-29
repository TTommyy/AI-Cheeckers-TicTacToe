#pragma once
#include "GameStateIf.h"
#include "Move.h"
#include "CheckersBoardIf.h"

class CheckersGameState : public GameStateIf<2>
{
public:
  CheckersGameState();
  CheckersGameState(std::shared_ptr<CheckersBoardIf>, PlayerE);
  bool isTerminal() override;
  std::array<int32_t, 2> evaluate() override;
  std::vector<Move> getPossibleMoves() override;
  std::shared_ptr<GameStateIf<2>> applyMove(const Move) override;
  std::optional<int32_t> getWinner() override;
  void show() const override;

private:
  bool isMan(const FigureTypeE&, const PlayerE&) const;
  FigureTypeE figureChange(const FigureTypeE&, const PlayerE&, uint8_t) const;
  std::shared_ptr<CheckersBoardIf> m_board_ptr;
  PlayerE m_playerToMove;
  std::optional<std::vector<Move>> m_possibleMoves;
};
