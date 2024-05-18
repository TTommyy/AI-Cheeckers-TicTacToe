#pragma once

#include <cstdint>

enum class FigureTypeE : int8_t 
{
  Empty = 0,
  WhiteMan = 1,
  WhiteKing = 3,
  BlackMan = -1,
  BlackKing = -3
};