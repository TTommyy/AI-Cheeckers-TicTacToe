//
// Created by tomek on 10.05.2024.
//

#pragma once

#include "GameStateIf.h"
#include "MoveIf.h"

#include <cstdint>
#include <utility>
#include <array>
#include <limits>
#include <iostream>
#include <memory>

template <int32_t NUMBER_OF_PLAYERS>
int32_t getNextPlayer(int32_t currentPlayer)
{
  return (currentPlayer + 1) % NUMBER_OF_PLAYERS
}

template<int32_t NUMBER_OF_PLAYERS>
std::pair<std::shared_ptr<MoveIf>, std::array<int32_t, NUMBER_OF_PLAYERS>> multiMaxMin(std::unique_ptr<GameStateIf<NUMBER_OF_PLAYERS>> gameState_ptr, int32_t depth, int32_t currentPlayer)
{
  if (gameState_ptr->isTerminal() or depth == 0)
  {
    return std::make_pair(nullptr, gameState_ptr->evaluate());
  }

  const auto moves = gameState_ptr->getPossibleMoves();
  const auto nextPlayer = getNextPlayer<NUMBER_OF_PLAYERS>(currentPlayer);

  if (moves.size() < 1)
  {
    // To do: Logs
    std::cout << "No moves for player: " << currentPlayer << "\n";
    return multiMaxMin(gameState_ptr, depth - 1, nextPlayer)
  }

  auto bestMove = moves.front();

  int32_t val = INT32_MIN;
  for (const auto& move: moves)
  {
    const auto [_, score] = multiMaxMin(gameState_ptr->applyMove(move), depth - 1, nextPlayer);
    if (score[currentPlayer] > val)
    {
      bestMove = move;
      val = score[currentPlayer];
    }
  }

  return std::make_pair(bestMove, val)
}