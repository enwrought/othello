This was a one-person project.  There are a few things that make
the enwrought AI competitive.

[Adaptive depth alpha-beta pruning]
The AI does a alpha-beta pruned minimax to choose the best move.  The
depth of the tree depends on how much remaining time is available
(out of the assumed 16 minutes).  If there is not enough time, the 
ply is reduced.

In practice, what happens is that there are fewer moves in the beginning
and the end, which end up getting higher ply.  In the beginning, this
is helpful to prevent from losing the game from the opening.  In the 
endgame, it is necessary to compute multiple steps in advance.  To do this
I use 8-ply (8 moves, each person makes one move) when there is enough
time, 7-ply if it is not at least 50% ahead of the end of the game, and
6-ply if it is slower than the end of the game.  Finally, if it is within 
12 moves from the end of the game, we force 10-ply.

For Othello, this manual tuning seems to be sufficient.  The difference
between 6-ply and 8-ply can be seconds versus minutes, and towards the 
end 10-ply is still relatively fast.


[Time and position based Heuristic]
The heuristic much more heavily values corners and edges of the board, 
but varies the weight depending on the number of moves in the game.  The 
corners and edges are highly valuable since they are harder or impossible
to flip sides and help to control the corners.  However, the time-based
component is important because at the endgame, each piece is worth the
same.  The heuristic accounts for this by taking a weighted average of the
position value and 1, where weights favor 1 as the game continues.

Corners are worth 35 and other edges are worth 8, while other squares are
just worth 1.  If the weight is w and we have played x out of the 64 pieces,
the heuristic is

alpha := (x-4) / (64-4)
return alpha * w + (1-alpha) * 1

The x-4 and 64-4 terms are used since we actually start with 4 pieces.


[Other considerations]
I chose not to use a transposition table since the AI can already go to
6 to 8-ply without having too much time, and the table will need to 
remove the most recent elements anyways each time.  Further, implementing
the transposition table means that the AI would go to higher ply, which
would affect the heuristic.

I looked for opening books, but Othello programs do not really have good
documentation and unfortunately could not find one with an understandable
format.

I used the -O2 optimization, which should improve performance.
