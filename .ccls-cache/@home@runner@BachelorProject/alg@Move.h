

# pragma once

#include "MoveIf.h"

class Move: public MoveIf
{
public:
  Move(std::string description): m_description(description) {}
  std::string getMoveDescription() const override { return m_description; }
private:
  std::string m_description;
};