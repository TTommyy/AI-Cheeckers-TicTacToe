#pragma once

#include "GameStateIf.h"
#include "Move.h"
#include <unordered_map>

template<int32_t NUMBER_OF_PLAYERS, uint8_t BOARD_SIZE>
class TicTacToeGameState : public GameStateIf<NUMBER_OF_PLAYERS>
{
public:
using Board = std::array<std::array<int32_t, BOARD_SIZE>, BOARD_SIZE>;
using Field = std::pair<int32_t, int32_t>;
  TicTacToeGameState();
  TicTacToeGameState(const Board &, int32_t, int32_t, std::array<std::vector<Field>, NUMBER_OF_PLAYERS>&);
  bool isTerminal() override;
  std::array<int32_t, NUMBER_OF_PLAYERS> evaluate() override;
  std::vector<Move> getPossibleMoves() override;
  std::shared_ptr<GameStateIf<NUMBER_OF_PLAYERS>> applyMove(const Move) override;
  std::optional<int32_t> getWinner() override;
  void show() const override;

private:
  void initBoard();
  bool validField(uint8_t, uint8_t);
  int32_t checkWinningCondition(int32_t, int32_t, int32_t);
  std::vector<Move> getPossibleMoves(int32_t);

  int32_t m_playerToMove;
  int32_t m_moveCounter;
  std::unordered_map<int32_t, std::vector<Move>> m_possibleMoves;
  Board m_board;
  std::array<std::vector<Field>, NUMBER_OF_PLAYERS> m_placedMoves;
  std::optional<std::array<int32_t, NUMBER_OF_PLAYERS>> m_scores_opt;
};
