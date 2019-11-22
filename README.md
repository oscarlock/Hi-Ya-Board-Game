# Hi-Ya-Board-Game
Board game that uses minimax and alpha-beta pruning in order to compete at a high level amongst players.


/*
~~~~~~~ RULES ~~~~~~~

This AI board game is a game that I created that has the objective of confronting the king to win.
Included in the engine are four pieces that can be moved to try to and defeat the built in AI.

"J" -  The Ninja can move in diagonals. At any moment in time in can move forward in a diagonal movement, but only backwards diagonally to confront a piece.

"j" -  The mini ninja follows the same rules except that it can only move one square per turn.  It contains the same rules that it can move backward in order to confront a piece.

"S" -  The Samurai can move forward at any point and time.  The Samurai can move perpindicular if it is to confront a piece. The Samurai cannot move backwards.

"s" -  The mini samurai has all the same movements as the Samurai except that it can only move one space whether it be forward or perpindicular.

When Samurais or Ninjas are confronted they are demoted to a mini samurai or mini ninja.

When mini samurais or mini ninjas are confronted they are removed from the board.

Rather than landing on the same board placement as the opponents piece to attack/confront the piece you must land in front of the oppoosing piece in the Y axis.

ex   | J | If the Samurai lands in front of the Ninja it will demote to a mini Ninja.  | j |
     | S |  																		   | S |

The Objective is to confront the king.

ex   | K |  This position would give the player with the Samurai a win.
     | S |

*/


/*

~~~~~~ To BEGIN ~~~~~~

1. In order to play and compile the file save this file onto your desktop as "HiYaLock.cpp".

2. Next open your terminal/command prompt and enter into the Desktop directory using the command "cd Desktop"

3. If the file is in your desktop drive enter the command "g++ HiYaLock.cpp -O3" in order to compile the file.

4. Finally enter the command "./a.out"
*/
