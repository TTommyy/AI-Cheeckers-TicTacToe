# pragma once

#include "MoveIf.h" 

#include <sstream>
#include <cstdint>
#include <vector>
#include <utility>

class CheckersMove : public MoveIf
{
public:
  using Field = std::pair<int32_t, int32_t>;
  struct Move_t
  {
    Field from;
    Field to;
    std::vector<Field> capctured;
  };
  CheckersMove(Field from, Field to, std::vector<Field> captured) 
      : m_from{from}, m_to{to}, m_captured{captured}{}
  CheckersMove(Field field, int32_t player): m_field{field}, m_player{player}
  {}
  CheckersMove(const CheckersMove&) = default;
  explicit CheckersMove() = default;
  virtual ~CheckersMove() = default;

  Move_t getMove() const
  {
    return {m_from, m_to, m_captured};
  }

  int32_t getNumberOfCaptured() const
  {
    return m_captured.size();
  }

  virtual std::string toString() const override
  {
    std::string ss;
    ss += ("From: (" + std::to_string(m_from.first) +"," + std::to_string(m_from.second) + ")\n");
    ss += ("To: (" + std::to_string(m_to.first) + "," + std::to_string(m_to.second) + ")\n");
    ss += "Captured: ";
    for (auto [y, x]: m_captured)
    {
      ss += ("(" + std::to_string(y) + "," + std::to_string(x) + ")");
    }
    ss += "\n";
    return ss;
  }

  bool operator==(const CheckersMove& other)
  {
    return m_from == other.m_from && m_to == other.m_to && m_captured == other.m_captured;
  } 

  Field m_field;
  int32_t m_player;
private:
    Field m_from;
    Field m_to;
    std::vector<Field> m_captured;
};