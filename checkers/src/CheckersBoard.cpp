#include "../inc/CheckersBoard.h"
#include <sstream>
#include <algorithm>
#include <iostream>
#include "../inc/Move.h"

namespace
{
  using DirectionVector = std::vector<std::pair<int32_t, int32_t>>;
  const auto ALL_DIRECTIONS = DirectionVector
  {
    {1, -1},  // upper left
    {1, 1},   // upper right
    {-1, 1},  // lower right
    {-1, -1}  // lower left
  };

  const auto AHEAD_DIRECTIONS = DirectionVector
  {
    {1, -1},
    {1, 1}
  };

  const auto BACKWARDS_DIRECTIONS = DirectionVector
  {
    {-1, -1},
    {-1, 1}
  };
}


CheckersBoard::CheckersBoard()
{
  intializeBoard();
}

std::string CheckersBoard::toString() const
{
  std::stringstream ss;
  for (const auto& row: m_board)
  {
    for (const auto& cell : row)
    {
      ss << static_cast<int>(cell) << ",";
    }
    ss << "\n";
  }
  return ss.str();
}

void CheckersBoard::show()
{
  std::stringstream ss;

  auto row = static_cast<int32_t>(BOARD_SIZE - 1);
  for (auto it = m_board.rbegin(); it < m_board.rend(); ++it)
  {
    ss << row-- << "| "; 
    for (const auto& cell : *it)
    {
      auto p = static_cast<int>(cell); 
      if (p == -1) ss << "8,";
      else if (p == -3) ss << "9,";
      else if (p == 1) ss << "1,";
      else if (p == 3) ss << "2,";
      else ss << static_cast<int>(cell) << ",";
    }
    ss << "\n";
  }

  ss << "  ";
  for (auto col = 0; col < BOARD_SIZE ; col++)
  {
    ss << "--";
  }
  ss << "\n   ";
  for (auto col = 0; col < BOARD_SIZE; col++)
  {
    ss << col << " ";
  }
  ss << "\n";

  std::cout << ss.str();
}

std::vector<Move> CheckersBoard::getPossibleMoves(const PlayerE& player) const
{
  std::vector<Move> moves;
  int32_t mostCaptured = 0;

  // check man can kill
  for (int32_t y = 0; y < BOARD_SIZE; ++y)
  {
    for (int32_t x = 0; x < BOARD_SIZE; ++x)
    {
      const auto& figure = m_board[y][x];
      // check man kill
      if ((figure == FigureTypeE::WhiteMan && player == PlayerE::White) ||
          (figure == FigureTypeE::BlackMan && player == PlayerE::Black))
      {
        // [end_field, captures_by_the_way]
        auto cap_vec = checkIfManCanKill(y, x, player, std::vector<Move::Field>(), m_board);

        for(const auto &pair: cap_vec)
        {
          moves.emplace_back(std::make_pair(y, x), pair.first, pair.second);
        }
      }
      // check king kill
      if ((figure == FigureTypeE::WhiteKing && player == PlayerE::White) ||
          (figure == FigureTypeE::BlackKing && player == PlayerE::Black))
      {
        // [end_field, captures_by_the_way]
        auto cap_vec = checkIfKingCanKill(y,x, player, std::vector<Move::Field>(), m_board);

        for(const auto &pair: cap_vec)
        {
          moves.emplace_back(std::make_pair(y, x), pair.first, pair.second);
        }
      }
    }
  }

  for(const auto& move: moves)
  {
    mostCaptured = std::max(move.getNumberOfCaptured(), mostCaptured);
  }

  moves.erase(std::remove_if(moves.begin(), moves.end(), 
    [mostCaptured](const auto& move)
    {
      return move.getNumberOfCaptured() < mostCaptured;
    }), moves.end());

  if (mostCaptured != 0)
  {
    return moves;
  }

  // check man move
  for(int32_t y = 0; y < BOARD_SIZE; ++y)
  {
    for(int32_t x = 0; x < BOARD_SIZE; ++x)
    {
      // check man move
      const auto& figure = m_board[y][x];
      if ((figure == FigureTypeE::WhiteMan && player == PlayerE::White) ||
          (figure == FigureTypeE::BlackMan && player == PlayerE::Black))
      {
        if ((figure == FigureTypeE::WhiteMan && y + 1 >= BOARD_SIZE) ||
            (figure == FigureTypeE::BlackMan && y - 1 < 0))
        {
          continue;
        }
        const auto manMoves = checkIfManCanMove(y, x, player);
        moves.insert(moves.end(), manMoves.begin(), manMoves.end());
      }
      // check king move
      else if ((figure == FigureTypeE::WhiteKing && player == PlayerE::White) ||
               (figure == FigureTypeE::BlackKing && player == PlayerE::Black))
      {
        const auto kingMoves = checkIfKingCanMove(y, x);
        moves.insert(moves.end(), kingMoves.begin(), kingMoves.end());
      }
    }
  }

  return moves;
}

CheckersBoardIf::Board CheckersBoard::getBoard() const
{
  return m_board;
}

void CheckersBoard::setBoard(CheckersBoardIf::Board board)
{
  m_board = board;
}

void CheckersBoard::intializeBoard()
{
  for(auto& row: m_board)
  {
    std::fill(row.begin(), row.end(), FigureTypeE::Empty);
  }

  // Initialize white pieces
  for (int x = 0; x < BOARD_SIZE; x += 2)
  {
    m_board[0][x] = FigureTypeE::WhiteMan;
    m_board[2][x] = FigureTypeE::WhiteMan;
  }
  for (int x = 1; x < BOARD_SIZE; x += 2)
  {
    m_board[1][x] = FigureTypeE::WhiteMan;
  }

  // Initialize black pieces
  for(int x = 1; x < BOARD_SIZE; x += 2)
  { 
    m_board[BOARD_SIZE - 3][x] = FigureTypeE::BlackMan;
    m_board[BOARD_SIZE - 1][x] = FigureTypeE::BlackMan;
  }
  for(int x = 0; x < BOARD_SIZE; x += 2)
  { 
    m_board[BOARD_SIZE - 2][x] = FigureTypeE::BlackMan;
  }
}

CheckersBoard::CapcturesVector CheckersBoard::checkIfManCanKill(int32_t y, int32_t x, const PlayerE& player, std::vector<Move::Field> cap, Board board) const
{
  CapcturesVector res;
  const PlayerE enemy = player == PlayerE::White? PlayerE::Black : PlayerE::White;
  for (const auto& [dy, dx]: ALL_DIRECTIONS)
  {
    if (checkIfOnField(y+dy, x+dx, enemy, board) && checkIfEmpty(y+2*dy, x+2*dx, board))
    {
      const auto capturedY = y+dy;
      const auto capturedX = x+dx;
      const auto newY = y + 2*dy;
      const auto newX = x + 2*dx;
      auto new_cap = cap;
      new_cap.push_back({capturedY, capturedX});
      res.push_back(std::make_pair(std::make_pair(newY, newX), new_cap));

      auto new_board = board;
      new_board[capturedY][capturedX] = FigureTypeE::Empty;
      new_board[y][x] = FigureTypeE::Empty;
      new_board[newY][newX] = FigureTypeE::WhiteMan;

      auto recur = checkIfManCanKill(newY, newX, player, new_cap, new_board);
      res.insert(res.end(), recur.begin(), recur.end());
    }
  }

  return res;
}

// KingsLogic
CheckersBoard::CapcturesVector CheckersBoard::checkIfKingCanKill(int32_t y, int32_t x, const PlayerE& player, std::vector<Move::Field> cap, Board board) const
{
  CapcturesVector res;
  const PlayerE enemy = player == PlayerE::White ? PlayerE::Black : PlayerE::White;

  for (const auto& [dy, dx] : ALL_DIRECTIONS)
  {
    int32_t newY = y;
    int32_t newX = x;
    bool foundCapture = false;

    while (validField(newY + dy, newX + dx))
    {
      newY += dy;
      newX += dx;

      if (checkIfOnField(newY, newX, player, board))
      {
        break;
      }

      if (checkIfOnField(newY, newX, enemy, board))
      {
        foundCapture = true;
        break;
      }
    }

    if (foundCapture) 
    {
      int32_t captureY = newY;
      int32_t captureX = newX;
      newY += dy;
      newX += dx;
      while (checkIfEmpty(newY, newX, board))
      {
        auto new_cap = cap;
        new_cap.push_back({captureY, captureX});
        res.push_back(std::make_pair(std::make_pair(newY, newX), new_cap));

        auto new_board = board;
        new_board[captureY][captureX] = FigureTypeE::Empty;
        new_board[y][x] = FigureTypeE::Empty;
        new_board[newY][newX] = FigureTypeE::WhiteKing;

        auto recur = checkIfKingCanKill(newY, newX, player, new_cap, new_board);
        res.insert(res.end(), recur.begin(), recur.end());

        newY += dy;
        newX += dx;
      }
    }
  }

  return res;
}

std::vector<Move> CheckersBoard::checkIfManCanMove(int32_t y, int32_t x, const PlayerE& player) const
{
  std::vector<Move> res;
  DirectionVector dv = player == PlayerE::White? AHEAD_DIRECTIONS : BACKWARDS_DIRECTIONS;
  for (const auto& [dy, dx] : dv)
  {
    auto newY = y;
    auto newX = x;
    if (checkIfEmpty(newY + dy, newX + dx, m_board))
    {
      newY += dy;
      newX += dx;
      Move m = Move({y, x}, {newY, newX}, {});
      res.push_back(m);
    }
  }

  return res;
}

std::vector<Move> CheckersBoard::checkIfKingCanMove(int32_t y, int32_t x) const
{
  std::vector<Move> res;

  for (const auto& [dy, dx] : ALL_DIRECTIONS)
  {
    auto newY = y;
    auto newX = x;
    while (checkIfEmpty(newY + dy, newX + dx, m_board))
    {
      newY += dy;
      newX += dx;
      Move m = Move({y, x}, {newY, newX}, {});
      res.push_back(m);
    }
  }

  return res;
}

bool CheckersBoard::validField(int32_t y,  int32_t x) const
{
  return 0 <= y && y < BOARD_SIZE && 0 <= x && x < BOARD_SIZE;
}

bool CheckersBoard::checkIfOnField(int32_t y, int32_t x, PlayerE player, const Board& board) const
{
  if (!validField(y,x)) return false;

  const auto field = board[y][x];
  return player == PlayerE::White ? 
     field == FigureTypeE::WhiteMan || field == FigureTypeE::WhiteKing :
     field == FigureTypeE::BlackMan || field == FigureTypeE::BlackKing;
}

bool CheckersBoard::checkIfEmpty(int32_t y, int32_t x, const Board& board) const
{
  return validField(y, x) && board[y][x] == FigureTypeE::Empty;
}