# Chess-Projects

End Goal: Chess Engine


## Part 1: BitBoard FEN Parser
A FEN (Forsyth-Edwards Notation) parser implemented in C. This project is designed to help in the process for the chess engine, in order to initialize game states directly into bitboards. 

### Architecture of Bitboard

Instead of using an 8 x 8 array this parser maps each piece type and color to a 64-bit integer. Each bit represents a square on the board, where a 1 indicates a piece is present and a 0 indicates it is empty.

Using a Bitboard allows for friendly bitwise operators, increasing speed.
Uses Little Endian Formatting (A8 = bit 63, H8 = bit 0). 

Drop bitboard.h and bitboard.c into your project's source directory.
```bash
gcc -Ofast bitboard.c -o bitboard.exe
./bitboard.exe
```
This project also calculates castling, en passant, 50 move rule.

