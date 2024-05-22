#include "../inc/CheckersGameState.h"
#include "../inc/CheckersBoard.h"
#include <iostream>
  
  
CheckersGameState::CheckersGameState(): m_board_ptr{std::make_shared<CheckersBoard>()}, m_to_move{PlayerE::White}
{}

CheckersGameState::CheckersGameState(std::shared_ptr<CheckersBoardIf> board, PlayerE player): m_board_ptr{std::move(board)}, m_to_move{player}
{}

bool CheckersGameState::isTerminal() const
{
  return getPossibleMoves().size() == 0;
}

std::array<int32_t, 2> CheckersGameState::evaluate() const
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

std::vector<Move> CheckersGameState::getPossibleMoves() const
{
  return m_board_ptr->getPossibleMoves(m_to_move);
}
std::shared_ptr<GameStateIf<2>> CheckersGameState::applyMove(const Move move) const
{
  auto bar_board = m_board_ptr->getBoard();
  auto move_desctription = move.getMove();

  auto &[old_y, old_x] = move_desctription.from;
  auto &[new_y, new_x] = move_desctription.to;

  auto to_move = bar_board[old_y][old_x];
  bar_board[old_y][old_x] = FigureTypeE::Empty;
  bar_board[new_y][new_x] = to_move;
  for (const auto& [y, x]: move_desctription.capctured)
  {
    bar_board[y] [x] = FigureTypeE::Empty;
  }

  PlayerE new_to_move = PlayerE::Black;
  if (m_to_move == PlayerE::Black)
  {
    new_to_move = PlayerE::White;
  }

  CheckersBoard new_board;
  new_board.setBoard(bar_board);
  return std::make_shared<CheckersGameState>(std::make_shared<CheckersBoard>(CheckersBoard(new_board)), new_to_move);
}

std::optional<int32_t> CheckersGameState::getWinner() const
{
  if (m_to_move == PlayerE::Black) return 100;
  return -100;
}

void CheckersGameState::show() const
{
  m_board_ptr->show();
}