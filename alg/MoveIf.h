//
// Created by tomek on 10.05.2024.
//

#pragma once

#include <string>

class MoveIf
{
public:
  virtual ~MoveIf() = default;
  virtual std::string getMoveDescription() const = 0;
};
