# Game-Playing-AI-bot
1 Goal
The goal of this assignment is to implement the adversarial search algorithms, such as
minimax and alpha-beta pruning, in a real-game setting.
2 The Game of Rollerball
2.1 Starting Position
![1](https://github.com/Fireborn25/Game-Playing-AI-bot/assets/97736756/c0c0c616-6633-4c48-b7ef-880409b15d25)

Rollerball features a 7x7 board with a 3x3 section in the middle cut out. There are six pieces per side:
two pawns, two rooks, one bishop and one king. The pieces move similarily to chess, with two changes:
• The pieces can move n steps in the clockwise direction and one or zero steps in the anticlockwise
direction
• The pieces may reflect off the four corners (for rooks) or off the edges (for bishops) atmost once
The game proceeds similar to chess, with the objective being to checkmate the opponent king. Further
details are described below.
2.2 Movement Rules
Due to four-fold symmetry of the board, we shall only describe the rules over these 10 squares of the
chessboard. All other moves can be obtained similarly. The pieces moves clockwise most of the time.
The squares on the board form two rings - the outer ring and the inner ring. Details for each piece
movements are given below.
![2](https://github.com/Fireborn25/Game-Playing-AI-bot/assets/97736756/24f80d0c-4756-446b-a967-3440d76bf349)

2.2.1 King
The king moves and can capture one step in any direction. Similar to traditional chess, the king can not
occupy any square where it can be captured. There is no castling in rollerball.
![3](https://github.com/Fireborn25/Game-Playing-AI-bot/assets/97736756/7d79dae4-8b9a-4352-992c-267e81aa3642)

2.2.2 Rook
Rook moves any number of steps horizontally or vertically along the clockwise direction. It also moves
one step in the anti-clockwise direction on its current ring. In rollerball, the rook reflects from the four
corners of the board. Only one reflection is allowed in a single move
![4](https://github.com/Fireborn25/Game-Playing-AI-bot/assets/97736756/ff80f0fe-2589-4189-85cd-20aed3e7127b)

2.2.3 Bishop
The bishop moves any number of steps diagonally in the clockwise direction. It moves only one step
diagonally in the anti-clockwise direction. In rollerball, the bishop reflects from the eight sides of the
board (four outer sides and four inner sides). Only one reflection is allowed in a single move.
![5](https://github.com/Fireborn25/Game-Playing-AI-bot/assets/97736756/11879a9d-6339-4563-898a-066d8f4b357a)

2.2.4 Pawn
The pawn moves one step straight or diagonally in the clockwise direction. It does not move in the
anti-clockwise direction. The pawn can be promoted to a rook or a bishop upon reaching the starting
squares of the opponent’s pawns.
![6](https://github.com/Fireborn25/Game-Playing-AI-bot/assets/97736756/caedc334-a6bb-41f7-9728-135ea543245a)

2.3 Objective
The objective of the game is to capture the opponent’s king while keeping the your king safe. Similar to
traditional chess, the player who checkmates the opponent is declared the winner.

3 C++ API
The core datatypes used in the code are positions and moves. A position is an 8-bit unsigned integer,
of which only the lower 6 bits are used, where bits 0-2 are used for the x-coordinate and 3-5 for the
y-coordinate.
![image](https://github.com/Fireborn25/Game-Playing-AI-bot/assets/97736756/fff14da8-afd5-41f4-854e-959afb256688)

A move is a 16-bit unsigned integer which consists of two positions concatenated with each other. Bits
0-5 are for the final position, bits 8-13 are for the initial position and bits 6 and 7 represent promotions
for pawns.
![image](https://github.com/Fireborn25/Game-Playing-AI-bot/assets/97736756/8d79e214-b7db-4338-ac06-a4e26cff2677)

Macros have been provided to construct and manipulate these types. Other than these two types, board
state is represented using BoardData, which contains positions of the twelve pieces on the board and
four rotated representations of the board, due to it’s four-fold symmetry. Each board is made up of 64
bytes, of which only 40 are used to represent state. Each of these bytes is a combination of PlayerColor
and PieceType. See the Board constructor and the two enums for details on how pieces are represented.
The Board class exposes four public methods:
1. get legal moves: This function computes and returns a set of legal moves for the current player
based on the current board state. Legal moves are moves that do not leave the player’s king in
check. If there are no legal moves, an empty set is returned.
2. in check: This function returns true if the current player is under check from the opponent
3. copy: Returns a pointer to a copy of the board. The pointer must be deleted after use.
4. do move(U16 move): performs a move on the board. Note that this alters the board state accordingly.



