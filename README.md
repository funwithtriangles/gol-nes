# Conway's Game of Life for the NES

<img width="546" alt="Screenshot 2024-04-30 at 11 32 48" src="https://github.com/funwithtriangles/gol-nes/assets/1876324/39992c23-7355-4ba3-a9c0-2d535ad42377">

Simple little thing I made for the NES. It involves two Game of Life boards: one shows green bugs, the other shows white flowers. When the two boards overlap, red flowers are shown in that cell. The bugs follow different rules than original GOL.

Board state is stored in 256 bytes. Each cell is a byte, with both boards represented in that byte. The first bit is dead/alive for board A, the second bit is dead/aive for board B. This implementation could potentially run 8 simultaneous boards. 

2*256 bytes is needed (Board0 and Board1). While the game is reading off one board, it is writing to the other.

*Note: This is my first NES project, don't use this as an example of best practice!*
