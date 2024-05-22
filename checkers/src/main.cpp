#include "../inc/CheckersBoard.h"
#include "../inc/CheckersGameState.h"
#include "../inc/AlphaBetaSearch.h"
#include <iostream>
#include <fstream>

constexpr int32_t DEPTH = 6;
void computerSimulation();
void humanPlayer();
void whiteHumanPlayer();
void blackHumanPlayer();
void humanGamePlay();
void generateTimesCvs();

int main() 
{
 std::cout << "Enter\n0 if Computer Simulation\n1 if HumanPlayer\n";

 int mode;
 std::cin >> mode;
 if (mode == 0)
 {
  computerSimulation();
 }
  else if(mode == 1)
  {
    humanPlayer();
  }
}

void humanPlayer()
{
  int mode;
  std::cout << "Enter\n0 if you play with white\n1 if you play with black\n2 if both players are human\n3 if cvs generation\n";
  std:: cin >> mode;
  if (mode == 0)
  {
    whiteHumanPlayer();
  }
  else if (mode == 1)
  {
    blackHumanPlayer();
  }
  else if (mode == 2)
  {
    humanGamePlay();
  }
  else if (mode == 3)
  {
    generateTimesCvs();
  }
  else 
  {
    std::cout << "Wrong mode. Ending program\n";
    return;
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

    std::cout << "Applied move: " << black_moves[user_move].toString();
    gs = gs->applyMove(black_moves[user_move]);
    gs->show();
  }
}

void timedAlphaBetaSearch(std::shared_ptr<GameStateIf<2>> gameState_ptr, int32_t depth, int32_t alpha, int32_t beta, bool maxPlayer)
{
    auto start = std::chrono::high_resolution_clock::now();

    auto [move, eval] = alphaBetaSearch(gameState_ptr, depth, alpha, beta, maxPlayer);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // Write depth and elapsed time to CSV file
    std::ofstream csvFile("timing_results.csv", std::ios::app); // Open in append mode
    if (csvFile.is_open())
    {
        csvFile << depth << "," << elapsed.count() << "\n";
        csvFile.close();
    }
    else
    {
        std::cerr << "Unable to open the CSV file for writing." << std::endl;
    }
}

void generateTimesCvs()
{
  for(auto i = 1; i < 15; i++)
  {
    std::shared_ptr<GameStateIf<2>> gs = std::make_shared<CheckersGameState>();
    timedAlphaBetaSearch(gs, i, -101, 101, true);
  }
}