#include "../inc/TicTacToeGameState.h"
#include "../inc/Move.h"

#include <array>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <random>
#include <iostream>
#include <algorithm>

constexpr int32_t REMOVED_FIELD{-1};
constexpr auto REMOVED_FIELD_FACTOR{0.15f};
constexpr int32_t WINNING_LENGTH{4};
using DirectionVector = std::vector<std::pair<int8_t, int8_t>>;
const DirectionVector UP_DOWN = {{1, 0}, {-1, 0}};
const DirectionVector LEFT_RIGHT = {{0, -1}, {0, 1}};
const DirectionVector LEFT_DOWN_RIGTH_UP = {{-1, -1}, {1, 1}};
const DirectionVector LEFT_UP_RIGHT_DOWN = {{1, -1}, {-1, 1}};
const std::vector<DirectionVector> ALL_DIRECTION =
  {
   UP_DOWN,
   LEFT_RIGHT,
   LEFT_DOWN_RIGTH_UP,
   LEFT_UP_RIGHT_DOWN
  };

template <int32_t NUMBER_OF_PLAYERS>
int32_t getNextPlayer(int32_t currentPlayer)
{
  return (currentPlayer + 1) % NUMBER_OF_PLAYERS;
}


template<int32_t NUMBER_OF_PLAYERS, uint8_t BOARD_SIZE>
TicTacToeGameState<NUMBER_OF_PLAYERS, BOARD_SIZE>::TicTacToeGameState()
{
  initBoard();
  m_playerToMove = 0;
  m_moveCounter = 0;
}

template<int32_t NUMBER_OF_PLAYERS, uint8_t BOARD_SIZE>
TicTacToeGameState<NUMBER_OF_PLAYERS, BOARD_SIZE>::TicTacToeGameState(const Board& board, int32_t player, int32_t count, std::array<std::vector<Field>, NUMBER_OF_PLAYERS>& placedMoves): m_board{board}
{
  m_playerToMove = player;
  m_moveCounter = count;
  m_placedMoves = placedMoves;
}
  
template<int32_t NUMBER_OF_PLAYERS, uint8_t BOARD_SIZE>
bool TicTacToeGameState<NUMBER_OF_PLAYERS, BOARD_SIZE>::isTerminal()
{
  if (getWinner()) return true;

  for (const auto& row: m_board)
  {
    for (const auto& col: row)
    {
      if (col == 0)
      {
        return false;
      }
    }
  }
  return true;
}

template<int32_t NUMBER_OF_PLAYERS, uint8_t BOARD_SIZE>
int32_t TicTacToeGameState<NUMBER_OF_PLAYERS, BOARD_SIZE>::checkWinningCondition(int32_t player, int32_t y, int32_t x)
{
  int32_t highest{0};
  for (const auto& line: ALL_DIRECTION)
  {
    int count = 1;
    for (const auto& [dy, dx]: line)
    {
      auto newY = y + dy;
      auto newX = x + dx;
      while (validField(newY, newX) && m_board[newY][newX] == player + 1)
      {
        count++;
        newY += dy;
        newX += dx;
      }
    }

    highest = std::max(highest, count);
  }

  return highest;
}

template<int32_t NUMBER_OF_PLAYERS, uint8_t BOARD_SIZE>
std::array<int32_t, NUMBER_OF_PLAYERS> TicTacToeGameState<NUMBER_OF_PLAYERS, BOARD_SIZE>::evaluate() 
{
  if (m_scores_opt) return m_scores_opt.value();

  std::array<int32_t, NUMBER_OF_PLAYERS> scores;
  for (int32_t player = 0; player < NUMBER_OF_PLAYERS; ++player)
  {
    auto moves = getPossibleMoves(player);
    if (moves.size() == 1 && moves[0].m_player == -1) // one move pass
    {
      scores[player] = -100;
      std::cout << "no moves\n";
      continue;
    }

    int32_t maxForPlayer = 0;
    for (const auto& field : m_placedMoves[player])
    {
      int32_t row = field.first;
      int32_t col = field.second;
      maxForPlayer = std::max(checkWinningCondition(player, row, col), maxForPlayer);
    }

    if (maxForPlayer == WINNING_LENGTH)
    {
      scores.fill(-100);
      scores[player] = 100;
      return scores;
    }
    scores[player] = maxForPlayer;
  }

  m_scores_opt = scores;
  return scores;
}

template<int32_t NUMBER_OF_PLAYERS, uint8_t BOARD_SIZE>
std::vector<Move> TicTacToeGameState<NUMBER_OF_PLAYERS, BOARD_SIZE>::getPossibleMoves()
{
  auto moves = getPossibleMoves(m_playerToMove);
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(moves.begin(), moves.end(), g);
  return moves;
}

template<int32_t NUMBER_OF_PLAYERS, uint8_t BOARD_SIZE>
std::shared_ptr<GameStateIf<NUMBER_OF_PLAYERS>> TicTacToeGameState<NUMBER_OF_PLAYERS, BOARD_SIZE>::applyMove(const Move move)
{
  const auto [row, col] = move.m_field;
  const auto player = move.m_player;


  Board board = m_board;
  if (player != -1) // pass
  {
    board[row][col] = player + 1;// 0 is empty
  }
  m_placedMoves[player].push_back(move.m_field);
  return std::make_shared<TicTacToeGameState<NUMBER_OF_PLAYERS, BOARD_SIZE>>(board, getNextPlayer<NUMBER_OF_PLAYERS>(m_playerToMove), m_moveCounter+1, m_placedMoves);
}

template<int32_t NUMBER_OF_PLAYERS, uint8_t BOARD_SIZE>
std::optional<int32_t> TicTacToeGameState<NUMBER_OF_PLAYERS, BOARD_SIZE>:: getWinner()
{
  auto evals = evaluate();
  for (auto i = 0; i < NUMBER_OF_PLAYERS; i++)
  {
    if (evals[i] == 100) return i;
  }

  return std::nullopt;
}

template<int32_t NUMBER_OF_PLAYERS, uint8_t BOARD_SIZE>
void TicTacToeGameState<NUMBER_OF_PLAYERS, BOARD_SIZE>::show() const
{
  std::stringstream ss;

  auto row = static_cast<int32_t>(BOARD_SIZE - 1);
  for (auto it = m_board.rbegin(); it < m_board.rend(); ++it)
  {
    ss << row-- << "| "; 
    for (const auto& cell : *it)
    {
      auto p = static_cast<int>(cell); 
      if (p == -1) ss << "X,";
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


template<int32_t NUMBER_OF_PLAYERS, uint8_t BOARD_SIZE>
std::vector<Move> TicTacToeGameState<NUMBER_OF_PLAYERS, BOARD_SIZE>::getPossibleMoves(int32_t player)
{
  if (m_possibleMoves.contains(player)) 
  {
    std::cout <<"er\n";
    return m_possibleMoves[player];
  }

  std::vector<Move> res;
  if (m_moveCounter < NUMBER_OF_PLAYERS)
  {
    for (auto y = 0; y < BOARD_SIZE; y++)
    {
      for (auto x = 0; x < BOARD_SIZE; x++)
      {
        if (m_board[y][x] == 0)
        {
          // std::cout << "pus1\n";
          res.push_back(Move(std::make_pair(y, x), player));
        }
      }
    }
  }
  else
  {
    for (const auto& field: m_placedMoves[player])
    {
      std::cout << "fuck yeah\n";
      for (const auto& line: ALL_DIRECTION)
      {
        for (const auto& [dy, dx]: line)
        {
          auto newY = field.first + dy;
          auto newX = field.second + dx;
          std::cout << "pushing " << newY << "\n";
          if (validField(newY, newX) && m_board[newY][newX] == 0)
          {
            res.push_back(Move(std::make_pair(newY, newX), player));
          }
        }
      }
    }
  }

  if (res.empty()) res.push_back(Move(std::make_pair(0, 0), -1)); // pass move
  m_possibleMoves.insert({player, res});
  return res;
}

template<int32_t NUMBER_OF_PLAYERS, uint8_t BOARD_SIZE>
void TicTacToeGameState<NUMBER_OF_PLAYERS, BOARD_SIZE>::initBoard() 
{
    Board board;

    for (auto& row : board) 
    {
        row.fill(0);
    }

    std::srand(std::time(nullptr));

    int32_t totalFields = BOARD_SIZE * BOARD_SIZE;
    int32_t fieldsToRemove = static_cast<int32_t>(totalFields * REMOVED_FIELD_FACTOR);

    std::vector<std::pair<int32_t, int32_t>> allPositions;
    for (int32_t i = 0; i < BOARD_SIZE; ++i)
    {
        for (int32_t j = 0; j < BOARD_SIZE; ++j)
        {
            allPositions.emplace_back(i, j);
        }
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(allPositions.begin(), allPositions.end(), g);
    for (int32_t i = 0; i < fieldsToRemove; ++i) 
    {
        int32_t row = allPositions[i].first;
        int32_t col = allPositions[i].second;
        board[row][col] = REMOVED_FIELD;
    }

    m_board = board;
}

template<int32_t NUMBER_OF_PLAYERS, uint8_t BOARD_SIZE>
bool TicTacToeGameState<NUMBER_OF_PLAYERS, BOARD_SIZE>::validField(uint8_t y, uint8_t x)
{
  return 0 <= y < BOARD_SIZE && 0 <= x < BOARD_SIZE && m_board[y][x] != REMOVED_FIELD;
}

template class TicTacToeGameState<5, 8>;