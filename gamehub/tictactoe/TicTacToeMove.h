#pragma once
#include "MoveIf.h"


class TicTacToeMove : public MoveIf
{
public:
  using Field = std::pair<int32_t, int32_t>;
  TicTacToeMove(Field field, int32_t player): m_field{field}, m_player{player}
  {}
  Field m_field;
  int32_t m_player;
  std::string toString() const
  {
    return "To do\n";
  }
};

