#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>



typedef struct Bitboards {
    unsigned long long white_pawns;
    unsigned long long white_rooks;
    unsigned long long white_knights;
    unsigned long long white_bishops;
    unsigned long long white_queens;
    unsigned long long white_king;
    unsigned long long black_pawns;
    unsigned long long black_rooks;
    unsigned long long black_knights;
    unsigned long long black_bishops;
    unsigned long long black_queens;
    unsigned long long black_king;
    unsigned long long empty_squares;

    int en_passant; //set -1 to -
    unsigned int half_move; //50 move draw, 100 means draw
    unsigned int full_move; //increment every move from black
    
    bool white_castle_king;
    bool white_castle_queen;
    bool black_castle_king;
    bool black_castle_queen;
    bool whites_move;

} Bitboards;

void init_starting_position(Bitboards* board);
void print_bitboard(Bitboards* board);
void init_clear_board(Bitboards* board);
void fen_parse_board(char* fen, Bitboards* board);

