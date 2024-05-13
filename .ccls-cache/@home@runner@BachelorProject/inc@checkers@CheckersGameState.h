//
// Created by tomek on 10.05.2024.
//

# pragma once
# include "GameStateIf.h"
# include "Move.h"


# include <string>


class CheckersGameState: public GameStateIf
{

private:
  std::array<std::array<int32_t, 8>, 8> m_board;
};
