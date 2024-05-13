#pragma once

#include "FieldTypeE.h"
#include "FigureTypeE.h"
#include "PlayerE.h"
#include "../../alg/MoveIf.h"

#include <utility>
#include <array>
#include <string>
#include <vector>

constexpr int8_t BOARD_SIZE = 8;

using Field = std::pair<FieldTypeE, FigureTypeE>;
using Board = std::array<std::array<Field, BOARD_SIZE>, BOARD_SIZE>;
class CheckersBoardIf 
{
public:
  virtual ~CheckersBoardIf() = default;
  virtual Board getBoard() const = 0;
  virtual std::string toString() const = 0;
  virtual std::vector<MoveIf> getPossibleMoves(const PlayerE&) = 0;
};