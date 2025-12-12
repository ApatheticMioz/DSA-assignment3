# AVL Game Player Manager

A C++ implementation of a Game and Player management system using self-balancing AVL trees for efficient data operations.

## Description

This project implements a dual AVL tree system for managing:
- **Players**: User profiles with personal information and gaming history
- **Games**: Game metadata including developer, publisher, and download statistics
- **Games Played**: A nested AVL tree tracking each player's gaming activity

All operations (insert, search, update, delete) achieve **O(log n)** time complexity through AVL tree self-balancing.

## Project Structure

```
.
├── main.cpp          # Main source file with all implementations
├── LICENSE           # MIT License
├── README.md         # This file
├── CONTRIBUTING.md   # Contribution guidelines
├── CHANGELOG.md      # Version history
├── .editorconfig     # Editor configuration
└── .gitignore        # Git ignore rules
```

## Features

- **Insertion**: Add players and games with duplicate key detection
- **Search & Retrieval**: Find entries by primary key in O(log n)
- **Deletion**: Remove entries with automatic tree rebalancing
- **Data Persistence**: Save/load from CSV files
- **Tree Visualization**: Display N layers of the tree
- **Path Finding**: Show traversal path to any node
- **Edit Entries**: Modify player/game data with key repositioning
- **Game History**: Check if a player has played a specific game

## Installation

### Prerequisites

- C++ compiler with C++11 support (g++, clang++, or MSVC)

### Build

```bash
g++ -o main main.cpp
```

## Usage

### Running the Application

```bash
./main
```

### Input Data Files

The application expects two input files in the working directory:
- `Players.txt` - Player data in CSV format
- `Games.txt` - Game data in CSV format

### Player Data Format
```
playerID,name,phoneNumber,email,password,gameID,hoursPlayed,achievements,...
```

### Game Data Format
```
gameID,name,developer,publisher,fileSizeGBs,downloads
```

### Output Files

The application generates:
- `Players.csv` - Exported player data
- `Games.csv` - Exported game data

## Time Complexities

| Operation | Complexity |
|-----------|------------|
| Insert | O(log n) |
| Search | O(log n) |
| Delete | O(log n) |
| Edit | O(log n) |
| Has Played | O(2 log n) |
| Save/Load | O(n) |

## Status

**Archived / Refactored**

This is an archived academic project demonstrating AVL tree implementation in C++.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
