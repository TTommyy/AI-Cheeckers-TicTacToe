#pragma once

#include "GameStateIf.h"
#include "Tic.h"

#include <cstdint>
#include <utility>
#include <array>
#include <limits>
#include <iostream>
#include <memory>
#include <numeric>

template <int32_t NUMBER_OF_PLAYERS>
int32_t getNextPlayer(int32_t currentPlayer)
{
  return (currentPlayer + 1) % NUMBER_OF_PLAYERS;
}

template<int32_t NUMBER_OF_PLAYERS>
std::pair<std::shared_ptr<Move>, std::array<int32_t, NUMBER_OF_PLAYERS>> multiMaxMin(std::shared_ptr<GameStateIf<NUMBER_OF_PLAYERS>> gameState_ptr, int32_t depth, int32_t currentPlayer)
{
  const auto moves = gameState_ptr->getPossibleMoves();
  if (gameState_ptr->isTerminal() or depth == 0 || moves.size() == 0)
  {
    return std::make_pair(nullptr, gameState_ptr->evaluate());
  }

  const auto nextPlayer = getNextPlayer<NUMBER_OF_PLAYERS>(currentPlayer);
  auto bestMove = moves.front();

  std::array<int32_t, NUMBER_OF_PLAYERS> bestScore;
  bestScore.fill(INT32_MIN);
  auto bestSum = std::accumulate(bestScore.begin(), bestScore.end(), 0);
  for (const auto& move : moves)
  {
    auto newState = gameState_ptr->applyMove(move);
    const auto [_, score] = multiMaxMin<NUMBER_OF_PLAYERS>(newState, depth - 1, nextPlayer);
    const auto newSum = std::accumulate(score.begin(), score.end(), 0);
    if (score[currentPlayer] > bestScore[currentPlayer] || (score[currentPlayer] == bestScore[currentPlayer] && newSum < bestSum))
    {
      bestMove = move;
      bestScore = score;
      bestSum = newSum;
    }
  }
  return {std::make_shared<Move>(bestMove), bestScore};
}