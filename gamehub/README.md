# GameHub - Board Game AI Simulator

A C++ board game framework with AI opponents using Minimax with Alpha-Beta pruning and Multi-player Minimax algorithms.

## Quick Start

```bash
cd gamehub && ./gamehub
```

Or build and run:
```bash
cd gamehub && make && ./gamehub
```

Clean build files:
```bash
cd gamehub && make clean
```

## Architecture Overview

The project follows a modular, template-based architecture with clear separation between game logic, AI algorithms, and UI.

### Directory Structure

```
gamehub/
├── src/                      # Source implementations main.cpp             # Application entry point &
│   ├── menus
│   ├── CheckersBoard.cpp    # Checkers board implementation
│   ├── CheckersGameState.cpp
│   └── TicTacToeGameState.cpp
├── algs/                    # AI search algorithms (headers only)
│   ├── GameStateIf.h        # Game state interface template
│   ├── MoveIf.h             # Move interface (base class)
│   ├── AlphaBetaSearch.h    # 2-player Alpha-Beta pruning
│   └── MultiMinMax.h        # N-player Minimax with parallelization
├── checkers/                # Checkers game components
├── tictactoe/               # Tic-Tac-Toe game components
├── Makefile
└── gamehub                  # Compiled executable
```

## Design Patterns

### 1. Strategy Pattern (Game State Interface)

Template-based interface allows any number of players:

```cpp
template <int32_t NUMBER_OF_PLAYERS>
class GameStateIf {
public:
    virtual ~GameStateIf() = default;
    virtual bool isTerminal() = 0;
    virtual std::array<int32_t, NUMBER_OF_PLAYERS> evaluate() = 0;
    virtual std::vector<std::shared_ptr<MoveIf>> getPossibleMoves() = 0;
    virtual std::shared_ptr<GameStateIf<NUMBER_OF_PLAYERS>> applyMove(const std::shared_ptr<MoveIf>) = 0;
    virtual std::optional<int32_t> getWinner() = 0;
    virtual void show() = 0;
};
```

Benefits:
- Generic AI algorithms work with any game
- Type-safe number of players at compile time
- Easy to add new games

### 2. Move Interface

All moves inherit from `MoveIf`:

```cpp
class MoveIf {
public:
    virtual std::string toString() const = 0;
    virtual ~MoveIf() = default;
};
```

### 3. Board Abstraction (Checkers)

Interface + Implementation pattern:
- `CheckersBoardIf`: Abstract interface
- `CheckersBoard`: Concrete 8x8 board

## AI Algorithms

### Alpha-Beta Search (algs/AlphaBetaSearch.h)

For 2-player zero-sum games (Checkers).

- Depth-limited search (default: 10)
- Alpha-beta pruning for optimization
- Returns: `(best_move, evaluation_score)`

```cpp
auto [move, eval] = alphaBetaSearch(gameState, depth, alpha, beta, maxPlayer);
```

### Multi-Player Minimax (algs/MultiMinMax.h)

For N-player games (Tic-Tac-Toe with 3+ players).

- Parallel move evaluation using `std::async`
- Each move explored in separate thread
- Non-zero-sum: players maximize own score

```cpp
auto [move, scores] = multiMaxMin<NUMBER_OF_PLAYERS>(gameState, depth, currentPlayer);
```

## Game Implementations

### Checkers (2-Player)

- Standard 8x8 board
- Men move forward, Kings move any direction
- Capturing is mandatory, multi-jump supported
- Promotion to King at opposite end

**Game Modes:**
1. White Human vs AI (Black)
2. Black Human vs AI (White)
3. Human vs Human
4. AI vs AI (simulation)

### Tic-Tac-Toe (N-Player)

Template parameters:
```cpp
TicTacToeGameState<NUMBER_OF_PLAYERS, BOARD_SIZE>
```

Default: 3 players, 6x6 board, win condition: 3 in a row.

## Build System

Makefile targets:
- `make` or `make all`: Build executable
- `make clean`: Remove object files and executable

Compiler settings:
```makefile
CXX = clang++
CXXFLAGS = -std=c++20 -Wall
```

Dependencies:
- C++20 compatible compiler (clang++ recommended)
- Standard library only (no external dependencies)

## Extending the Framework

1. Create Move class inheriting from `MoveIf`
2. Create GameState class inheriting from `GameStateIf<N>`
3. Choose AI algorithm:
   - 2 players: Use `alphaBetaSearch()`
   - 3+ players: Use `multiMaxMin<N>()`
4. Add menu option in `main.cpp`

## Performance Notes

- Checkers: Depth 10 provides strong play
- Tic-Tac-Toe: Parallel evaluation using `std::async`
- Board state is immutable for thread safety
