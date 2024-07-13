#pragma once

#include "GameStateIf.h"

#include <cstdint>
#include <utility>
#include <array>
#include <limits>
#include <iostream>
#include <memory>
#include <numeric>
#include <future>

class MoveIf;

template <int32_t NUMBER_OF_PLAYERS>
int32_t getNextPlayer(int32_t currentPlayer)
{
  return (currentPlayer + 1) % NUMBER_OF_PLAYERS;
}

template<int32_t NUMBER_OF_PLAYERS>
std::pair<std::shared_ptr<MoveIf>, std::array<int32_t, NUMBER_OF_PLAYERS>> multiMaxMin(std::shared_ptr<GameStateIf<NUMBER_OF_PLAYERS>> gameState_ptr, int32_t depth, int32_t currentPlayer)
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

  std::vector<std::future<std::pair<std::shared_ptr<MoveIf>, std::array<int32_t, NUMBER_OF_PLAYERS>>>> futures;
  for (const auto& move : moves)
  {
    futures.push_back( std::async(std::launch::async, [=, &gameState_ptr]() {
      const auto newState = gameState_ptr->applyMove(move);
      return multiMaxMin<NUMBER_OF_PLAYERS>(newState, depth - 1, nextPlayer);
    }));
  }

  for (size_t i = 0; i < moves.size(); ++i)
  {
    const auto [_, score] = futures[i].get();
    const auto newSum = std::accumulate(score.begin(), score.end(), 0);
    if (score[currentPlayer] > bestScore[currentPlayer] || (score[currentPlayer] == bestScore[currentPlayer] && newSum < bestSum))
    {
      bestMove = moves[i];
      bestScore = score;
      bestSum = newSum;
    }
  }

  return {bestMove, bestScore};
}