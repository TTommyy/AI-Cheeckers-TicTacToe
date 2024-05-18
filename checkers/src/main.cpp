#include "../inc/CheckersBoard.h"
#include "../inc/CheckersGameState.h"
#include "../inc/AlphaBetaSearch.h"
#include <iostream>

int main() 
{
  std::shared_ptr<GameStateIf<2>> gs= std::make_shared<CheckersGameState>();
  gs->show();

  bool to_move = true;
  for(int i = 0; i < 100; i++)
  {
    auto[move, eval] = alphaBetaSearch(gs, 10, -100, 100, to_move);
    std::cout << "Evaluation after move " << i << ": " << eval << "\n";
    if (!move)
    {
      std::cout << "Winner " << to_move;
      return 0;
    }

    to_move = !to_move;
    std::cout << (*move).toString();
    gs = gs->applyMove(*move);
    gs->show();
  }
}