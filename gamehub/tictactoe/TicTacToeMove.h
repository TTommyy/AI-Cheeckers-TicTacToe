#pragma once

#include "MoveIf.h"
#include <sstream>


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
    std::stringstream ss;
    ss << "Field: [" << std::to_string(m_field.first) << "," << std::to_string(m_field.second) << "], Player: " + std::to_string(m_player) + "\n";
    return ss.str();
  }
};

