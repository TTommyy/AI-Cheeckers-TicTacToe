#include "CheckersBoard.h"
#include "CheckersGameState.h"
#include "AlphaBetaSearch.h"
#include "MultiMinMax.h"
#include "TicTacToeGameState.h"
#include <iostream>
#include <fstream>

constexpr int32_t DEPTH = 10;
void computerSimulation();
void whiteHumanPlayer();
void blackHumanPlayer();
void humanGamePlay();
void ComputerTicTacToe();

void welcomeUser()
{
  std::cout 
    << "    Welcome to the game hub. Choose your game by entering number:\n"
    << "    1 - Checkers\n"
    << "    2 - TicTacToe\n"
    << "    0 - Quit\n";
}

int exitProgram()
{
  std::cout << "    Goodbye!!!\n";
  return 0;
}

void checkersMenu()
{
  system("clear");
  std::cout 
    << "    Cheeckers. Entrer correct mode\n"
    << "    1 - White Human Player\n"
    << "    2 - Black Human Player\n"
    << "    3 - Both Human Players\n"
    << "    4 - Both Computer Players\n"
    << "    0 - Quit\n";

  int mode;
  std::cin >> mode;
  system("clear");
  switch (mode)
  {
  case 0:
    exitProgram();
    return;
  case 1:
    whiteHumanPlayer();
    break;
  case 2:
    blackHumanPlayer();
    break;
  case 3:
    humanGamePlay();
    break;
  case 4:
    computerSimulation();
    break;
  default:
    std::cout << "Wrong!\n";
    checkersMenu();
    break;
  }
}

int main() 
{
  welcomeUser();
  int mode;
  std::cin >> mode;
  switch (mode)
  {
    case 0:
      return exitProgram();
    case 1:
      checkersMenu();
      break;
    case 2:
      ComputerTicTacToe();
      break;
  }
}

void computerSimulation()
{
  std::shared_ptr<GameStateIf<2>> gs= std::make_shared<CheckersGameState>();
  gs->show();

  bool to_move = true;
  int i = 0;
  while(true)
  {
    auto[move, eval] = alphaBetaSearch(gs, DEPTH, -100, 100, to_move);
    std::cout << "Evaluation after move " << i++ << ": " << eval << "\n";
    if (!move)
    {
      std::cout << "Winner " << to_move + 1;
      return;
    }

    to_move = !to_move;
    std::cout << (*move).toString();
    gs = gs->applyMove(*move);
    gs->show();
  }
}

namespace
{
  constexpr int32_t NUMBER_OF_PLAYERS{4};
  constexpr int32_t FIRST_MOVE_DEPTH{1};
  constexpr int32_t MOVE_DEPTH{10};
  constexpr int32_t TIC_TAC_BOARD_SIZE{7};
}

void ComputerTicTacToe()
{
  std::shared_ptr<GameStateIf<NUMBER_OF_PLAYERS>> gs= std::make_shared<TicTacToeGameState<NUMBER_OF_PLAYERS, TIC_TAC_BOARD_SIZE>>();
  gs->show();

  int d;
  int to_move = 0;
  int i = 0;
  while(!gs->isTerminal())
  {
    d = i < NUMBER_OF_PLAYERS ? FIRST_MOVE_DEPTH : MOVE_DEPTH;
    auto[move, evals] = multiMaxMin(gs, d, to_move);
    gs = gs->applyMove(*move);
    gs->show();
    std::cout << "Future predictions: ";
    for (auto e: evals) std::cout << e << " ";
    std::cout << "\n";
    if (auto winner = gs->getWinner())
    {
      std::cout << "Winner: " << *winner + 1<< "\n";
      return;
    }
    to_move = (to_move+1)%NUMBER_OF_PLAYERS;
    i++;
  }
}


void whiteHumanPlayer()
{
  std::shared_ptr<GameStateIf<2>> gs= std::make_shared<CheckersGameState>();
  gs->show();

  int i = 1;
  while(true)
  {
    const auto moves = gs->getPossibleMoves();
    if (moves.size() == 0)
    {
      std::cout << "Winner Black\n";
      return;
    }

    std::cout << "Valid moves:\n";
    int j = 0;
    for (const auto& m: moves)
    {
      std::cout << "Move number: " << j++ << "\n";
      std::cout << m.toString();
    }

    bool valid_move = false;
    int user_move;
    while(!valid_move)
    {
      std::cout << "Valid moves range: 0-" << moves.size() - 1 << "\n";
      std::cout << "Enter your move: ";
      std::cin >> user_move;
      if (user_move < 0 || user_move > moves.size() - 1)
      {
        std::cout << "Invalid move\n";
      }
      else valid_move = true;
    }
    system("clear");
    std::cout << "Applied move: " << moves[user_move].toString();
    gs = gs->applyMove(moves[user_move]);
    gs->show();

    std::cout << "Waiting for computer move...\n";
    auto[move, eval] = alphaBetaSearch(gs, DEPTH, -100, 100, false);
    std::cout << "Evaluation after move " << i++ << ": " << eval << "\n";
    if (!move)
    {
      std::cout << "Winner White\n";
      return;
    }

    std::cout << (*move).toString();
    gs = gs->applyMove(*move);
    gs->show();
  }
}

void blackHumanPlayer()
{
  std::shared_ptr<GameStateIf<2>> gs= std::make_shared<CheckersGameState>();
  gs->show();

  int i = 1;
  while(true)
  {
    std::cout << "Waiting for computer move...\n";
    auto[move, eval] = alphaBetaSearch(gs, DEPTH, -100, 100, true);
    std::cout << "Evaluation after move " << i++ << ": " << eval << "\n";
    if (!move)
    {
      std::cout << "Winner Black\n";
      return;
    }

    std::cout << (*move).toString();
    gs = gs->applyMove(*move);
    gs->show();

    const auto moves = gs->getPossibleMoves();
    if (moves.size() == 0)
    {
      std::cout << "Winner White\n";
      return;
    }

    std::cout << "Valid moves:\n";
    int j = 0;
    for (const auto& m: moves)
    {
      std::cout << "Move number: " << j++ << "\n";
      std::cout << m.toString();
    }

    bool valid_move = false;
    int user_move;
    while(!valid_move)
    {
      std::cout << "Valid moves range: 0-" << moves.size() - 1 << "\n";
      std::cout << "Enter your move: ";
      std::cin >> user_move;
      if (user_move < 0 || user_move > moves.size() - 1)
      {
        std::cout << "Invalid move\n";
      }
      else valid_move = true;
    }
    system("clear");
    std::cout << "Applied move: " << moves[user_move].toString();
    gs = gs->applyMove(moves[user_move]);
    gs->show();
  }
}

void humanGamePlay()
{
  std::shared_ptr<GameStateIf<2>> gs= std::make_shared<CheckersGameState>();
  gs->show();

  while(true)
  {

    const auto white_moves = gs->getPossibleMoves();
    if (white_moves.size() == 0)
    {
      std::cout << "Winner Black\n";
      return;
    }

    std::cout << "Valid moves:\n";
    int j = 0;
    for (const auto& m: white_moves)
    {
      std::cout << "Move number: " << j++ << "\n";
      std::cout << m.toString();
    }

    bool valid_move = false;
    int user_move = -1;
    while(!valid_move)
    {
      std::cout << "Valid moves range: 0-" << white_moves.size() - 1 << "\n";
      std::cout << "Enter your move: ";
      std::cin >> user_move;
      if (user_move < 0 || user_move > white_moves.size() - 1)
      {
        std::cout << "Invalid move\n";
      }
      else valid_move = true;
    }
    system("clear");
    std::cout << "Applied move: " << white_moves[user_move].toString();
    gs = gs->applyMove(white_moves[user_move]);
    gs->show();

    const auto black_moves = gs->getPossibleMoves();
    if (black_moves.size() == 0)
    {
      std::cout << "Winner White\n";
      return;
    }

    std::cout << "Valid moves:\n";
    j = 0;
    for (const auto& m: black_moves)
    {
      std::cout << "Move number: " << j++ << "\n";
      std::cout << m.toString();
    }

    valid_move = false;
    user_move = -1;
    while(!valid_move)
    {
      std::cout << "Valid moves range: 0-" << black_moves.size() - 1 << "\n";
      std::cout << "Enter your move: ";
      std::cin >> user_move;
      if (user_move < 0 || user_move > black_moves.size() - 1)
      {
        std::cout << "Invalid move\n";
      }
      else valid_move = true;
    }
    system("clear");
    std::cout << "Applied move: " << black_moves[user_move].toString();
    gs = gs->applyMove(black_moves[user_move]);
    gs->show();
  }
}