# pragma once

#include <sstream>
#include <cstdint>
#include <vector>
#include <utility>

class Move
{
public:
  using Field = std::pair<uint8_t, uint8_t>;
  struct Move_t
  {
    Field from;
    Field to;
    std::vector<Field> capctured;
  };
  Move(Field from, Field to, std::vector<Field> captured) 
      : m_from{from}, m_to{to}, m_captured{captured}{}
  Move(const Move&) = default;
  explicit Move() = default;

  Move_t getMove() const
  {
    return {m_from, m_to, m_captured};
  }

  uint8_t getNumberOfCaptured() const
  {
    return m_captured.size();
  }

  std::string toString() const
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

  bool operator==(const Move& other)
  {
    return m_from == other.m_from && m_to == other.m_to && m_captured == other.m_captured;
  } 
private:
    Field m_from;
    Field m_to;
    std::vector<Field> m_captured;
};