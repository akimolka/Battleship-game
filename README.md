# Battleship

### Description
This project implemets the well-known [Battleship game](https://en.wikipedia.org/wiki/Battleship_(game)).

**Already supported features:**
- [X] classic shipset 
- [X] adequate Artificial Intelligence player
- [X] arranging ships on the board
- [X] generation of grids for lazy ones
- [X] games vs AI and other human players
**To be implemented:**
- [ ] extraordinary shipsets and opportunity to choose a shipset for a game
- [ ] AI player that calculates the possibility of box to be occupied
- [ ] beautiful output
- [ ] graphical interface(?)

### How to run the game
Simply execute run.sh file

### Patterns used
***Factory method*** is used in creation of players, means of input and output. It provides an interface for usage of objects in a superclass, but allows subclasses to alter the behavior.

***Builder*** is used in filling the board. As a number of rules should be followed during ship arrangement, client does not have a straight access to the construction of the board and uses fill_board() method instead, which guides him through this intricate process

***Flyweight*** idea is applied in creation of class StandartShips. Real objects are created only this class, elsewhere pointers are used. Но сделано криво, нужно будет переделать



