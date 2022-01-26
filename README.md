# TreasureHunter

A simple arduino game for teaching/learning purposes (and for fun!).

This directory includes code for a basic game using as hardware:
  - an Arduino(ish) Uno board;
  - a breadboard and jumpers;
  - two potentiometers (the reason of the naming "potgame");
  - and a couple of LEDs and a buzzer for feedback

Game description:
> The game consists of an imaginary 2D board, mapped by two cartesian coordinates (x,y), a treasure, and a player with an imaginary "metal detector".
> At the beginning of each round, a position (x_T,y_T) for the hidden treasure is randomly chosen by arduino.
> The player moves through the field/board by phisically changing the angle of the potentiometers, which are mapped to 2D player positions by arduino.
> The player receives feedback from its "metal detector", namely a LED and a buzzer which periodically "beep", whose periods correspond to the distance between player and the treasure.
> When player reaches the treasure, the current level is won by the player
> The field is divided into squares, whose quantities depend on the level. Increasing levels corresponds to increasing number of divisions of the field, which increases how difficult it is for the player to land on the precise location (on the same square) of the treasure, making the game more challenging.
That's it for now

There is will to futurely add a GUI with python for a visual representation of the game, too. But it's currently unavailable.
