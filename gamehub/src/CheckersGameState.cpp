#include "CheckersGameState.h"
#include "CheckersBoard.h"
#include <iostream>
#include <algorithm>
#include <random>
  
CheckersGameState::CheckersGameState(): m_board_ptr{std::make_shared<CheckersBoard>()}, m_playerToMove{PlayerE::White}
{}

CheckersGameState::CheckersGameState(std::shared_ptr<CheckersBoardIf> board, PlayerE player): m_board_ptr{std::move(board)}, m_playerToMove{player}
{}

bool CheckersGameState::isTerminal()
{
  return getPossibleMoves().size() == 0;
}

std::array<int32_t, 2> CheckersGameState::evaluate()
{
  if (isTerminal())
  {
    auto score = *getWinner();
    return {score, - score};
  }

  const auto& bar_board = m_board_ptr->getBoard();
  int32_t score = 0;

  for (const auto& row: bar_board)
  {
    for (const auto field: row)
    {
      score += static_cast<int32_t>(field);
    }
  }

  return {score, -score};
}

std::vector<Move> CheckersGameState::getPossibleMoves()
{
  if (m_possibleMoves) return m_possibleMoves.value();
  m_possibleMoves = m_board_ptr->getPossibleMoves(m_playerToMove);
  // std::reverse(m_possibleMoves.value().begin(), m_possibleMoves.value().end());
  return m_possibleMoves.value();
  // std::random_device rd;
  // std::mt19937 g(rd());
  // std::shuffle(m_possibleMoves.value().begin(), m_possibleMoves.value().end(), g);
  // return m_possibleMoves.value();
}
std::shared_ptr<GameStateIf<2>> CheckersGameState::applyMove(const Move move)
{
  auto bar_board = m_board_ptr->getBoard();
  auto move_desctription = move.getMove();

  auto &[old_y, old_x] = move_desctription.from;
  auto &[new_y, new_x] = move_desctription.to;

  auto figure_to_move = bar_board[old_y][old_x];
  bar_board[old_y][old_x] = FigureTypeE::Empty;
  bar_board[new_y][new_x] = figureChange(figure_to_move, m_playerToMove, new_y);
  for (const auto& [y, x]: move_desctription.capctured)
  {
    bar_board[y] [x] = FigureTypeE::Empty;
  }

  PlayerE newPlayerToMove = PlayerE::Black;
  if (m_playerToMove == PlayerE::Black)
  {
    newPlayerToMove = PlayerE::White;
  }

  CheckersBoard new_board;
  new_board.setBoard(bar_board);
  return std::make_shared<CheckersGameState>(std::make_shared<CheckersBoard>(CheckersBoard(new_board)), newPlayerToMove);
}

std::optional<int32_t> CheckersGameState::getWinner()
{
  if (m_playerToMove == PlayerE::Black) return 100;
  return -100;
}

void CheckersGameState::show()
{
  m_board_ptr->show();
}

bool CheckersGameState::isMan(const FigureTypeE& figure, const PlayerE& player) const
{
  if (player == PlayerE::White) return figure == FigureTypeE::WhiteMan;
  else return figure == FigureTypeE::BlackMan;
}

FigureTypeE CheckersGameState::figureChange(const FigureTypeE& figure, const PlayerE& player, int32_t new_y) const
{
  if (!isMan(figure, player)) return figure;
  if (player == PlayerE::White && new_y + 1 == m_board_ptr->gerBoardSize()) return FigureTypeE::WhiteKing;
  else if (player == PlayerE::Black && new_y == 0) return FigureTypeE::BlackKing;

  return figure;
}