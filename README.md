# Backgammon Board Game Implementation in C++

This is a C++ implementation of the classic board game Backgammon. The project aims to provide a playable version of Backgammon using C++ programming language.

## Preview

![bckgss](https://github.com/JanBancerewicz/Backgammon-board-game/assets/79080628/23cb5efe-8d77-41e6-a631-cfe8bba699cd)


## Getting Started
### Prerequisites
Make sure you have a C++ compiler installed. The code provided here is compatible with C++11 or later.

## Installation

Clone this repository:

```bash
  git clone https://github.com/JanBancerewicz/Backgammon-board-game.git
```

Compile the code using your C++ compiler:

```bash
g++ -o backgammon game.cpp functions.cpp -std=c++11
```
Run the executable:
```bash
./backgammon
```

## How to play

Backgammon is a two-player game where each player has 15 pieces that move between 24 triangles (points) according to the roll of two dice.

The game will prompt players for their moves. Enter the point number from which you want to move your pieces and the point number to which you want to move them. Follow the on-screen instructions to play the game.

## Features Preview

- **Interactive Gameplay:** Engage in classic backgammon gameplay against another player.

- **Graphical User Interface (GUI):** Enjoy a visually appealing interface designed for smooth interaction.

- **Doubling Cube:** Implementation of the doubling cube feature adds an extra layer of strategy to the game.

- **Ingame hints for possible moves:** This feature makes the game much more consistent and enjoyable.

- **Save/Load Game:** Save your progress and resume games later.


### Replay mode

- **Keep track of your completed games:** A replay mode allows to inspect every single move and quickly navigate through the save. 

![replay](https://github.com/JanBancerewicz/Backgammon-board-game/assets/79080628/17e0503f-cb8b-4584-811f-4efa103c925a)
 
### Leaderboard

- **Track player scores in a convinient way:** The leaderboard stores all users and the sum of their points. 

![leaderboard](https://github.com/JanBancerewicz/Backgammon-board-game/assets/79080628/3b43452c-2f70-4200-96fc-9d4d68985356)


## License
This project is licensed under the MIT [License](LICENSE).

## Acknowledgments
This implementation is inspired by the classic Backgammon board game.
Special thanks to prof. Tytus Pikies for their guidance and support.



