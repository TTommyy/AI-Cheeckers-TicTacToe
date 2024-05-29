#pragma once
#include "../inc/Move.h"


class TicTacToeMove : public Move
{
public:
  TicTacToeMove(Field field, int32_t player): m_field{field}, m_player{player}
  {}
  Field m_field;
  int32_t m_player;
  std::string toString() const
  {
    return "To do\n";
  }
};

