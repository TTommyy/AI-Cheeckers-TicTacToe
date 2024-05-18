//
// Created by tomek on 10.05.2024.
//

#pragma once

#include "GameStateIf.h"
#include "Move.h"

#include <cstdint>
#include <utility>
#include <array>
#include <limits>
#include <memory>
#include <cmath>


std::pair<std::optional<Move>, int32_t> alphaBetaSearch(std::shared_ptr<GameStateIf<2>> gameState_ptr, int32_t depth, int32_t alpha, int32_t beta, bool maxPlayer)
{
  const auto moves = gameState_ptr->getPossibleMoves();
  if (gameState_ptr->isTerminal() || depth == 0 || moves.size() == 0)
  {
    return std::make_pair(std::nullopt, std::get<0>(gameState_ptr->evaluate()));
  }

  auto bestMove = moves.front();

  int32_t val;
  if (maxPlayer)
  {
    val = INT32_MIN;
    for (const auto& move: moves)
    {
      const auto [_, score] = alphaBetaSearch(gameState_ptr->applyMove(move), depth - 1, alpha, beta, false);
      if (score > val)
      {
        bestMove = move;
        val = score;
      }
      alpha = std::max(alpha, val);
      if (val >= beta)
      {
        break;
      }
    }
  }
  else // minPlayer
  {
    val = INT32_MAX;
    for (const auto& move: moves)
    {
      const auto [_, score] = alphaBetaSearch(gameState_ptr->applyMove(move), depth - 1, alpha, beta, true);
      if (score < val)
      {
        bestMove = move;
        val = score;
      }
      beta = std::min(alpha, val);
      if (val <= alpha)
      {
        break;
      }
    }
  }
  return std::make_pair(bestMove, val);
}