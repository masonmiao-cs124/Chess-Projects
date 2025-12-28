
#include "bitboard.h"



int main() { 
    Bitboards hello;
    init_starting_position(&hello);
    //print_bitboard(&hello);
    fen_parse_board("4N3/5R2/2kp4/p5pp/8/1PKN4/P6r/8 w - - 0 41",&hello);
    
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("bnqrkrnb/pppppppp/8/8/8/8/PPPPPPPP/BNQRKRNB w KQkq - 0 1");
    printf("\n");
   


    print_bitboard(&hello);

    printf("\n");
    printf("white move? %d", hello.whites_move);
    printf("\n");
    printf("castling rights: White %d   %d", hello.white_castle_king, hello.white_castle_queen); 
    printf("\n");
    printf(" Black: %d    %d", hello.black_castle_king, hello.black_castle_queen, "\n");
    printf("\n");
    printf("en passant! %d", hello.en_passant, "\n");
    printf("\n");
    printf("half move %d", hello.half_move, "\n");
    printf("\n");
    printf("full move %d", hello.full_move, "\n");

    return 0;
}


void init_clear_board(Bitboards* board) { 
    board->white_pawns   = 0x0ULL;
    board->white_rooks   = 0x0ULL;
    board->white_knights = 0x0ULL;
    board->white_bishops = 0x0ULL;
    board->white_queens  = 0x0ULL;
    board->white_king    = 0x0ULL;
    board->black_pawns   = 0x0ULL;
    board->black_rooks   = 0x0ULL;
    board->black_knights = 0x0ULL;
    board->black_bishops = 0x0ULL;
    board->black_queens  = 0x0ULL;
    board->black_king    = 0x0ULL;
    board->empty_squares = 0xFFFFFFFFFFFFFFFFULL;

    // int en_passant; //set -1 to -
    // unsigned int half_move; //50 move draw, 100 means draw
    // unsigned int full_move; //increment every move from black
    
    // bool white_castle_king;
    // bool white_castle_queen;
    // bool black_castle_king;
    // bool black_castle_queen;
    // bool whites_move;
    board->en_passant = -1;
    board->half_move = 0;
    board->full_move = 0;
    board->white_castle_king = false;
    board->white_castle_queen = false;
    board->black_castle_king = false;
    board->black_castle_queen = false;
    board->whites_move = true;



}
void init_starting_position(Bitboards* board) {
    board->white_pawns   = 0x000000000000FF00ULL;
    board->white_rooks   = 0x0000000000000081ULL;
    board->white_knights = 0x0000000000000042ULL;
    board->white_bishops = 0x0000000000000024ULL;
    board->white_queens  = 0x0000000000000010ULL;
    board->white_king    = 0x0000000000000008ULL;
    board->black_pawns   = 0x00FF000000000000ULL;
    board->black_rooks   = 0x8100000000000000ULL;
    board->black_knights = 0x4200000000000000ULL;
    board->black_bishops = 0x2400000000000000ULL;
    board->black_queens  = 0x1000000000000000ULL;
    board->black_king    = 0x0800000000000000ULL;
    board->empty_squares = 0x0000FFFFFFFF0000ULL;

    board->en_passant = -1;
    board->half_move = 0;
    board->full_move = 1;
    board->white_castle_king = true;
    board->white_castle_queen = true;
    board->black_castle_king = true;
    board->black_castle_queen = true;
    board->whites_move = true;
}

void print_bitboard(Bitboards* board) {
    int diag = 0;
    for (int x = 7; x >= 0; x--) {
        for (int y = 7; y >= 0; y--) {
            if (x%2 == 1) diag = 0;
            else diag = 1;
            int square = x * 8 + y;
            unsigned long long mask = 1ULL << square;
            if (board->empty_squares & mask) { //IF THIS IS NOT 0
                if ((square+diag)%2) { 
                    printf("  ");
                } else { 
                    printf("# ");
                }
                continue;
            }
            bool check = board->white_pawns & mask;
            bool check1 = board->white_rooks & mask;
            bool check2 = board->white_knights & mask;
            bool check3 = board->white_bishops & mask;
            bool check4 = board->white_queens & mask;
            bool check5 = board->white_king & mask;

            bool check6 = board->black_pawns & mask;
            bool check7 = board->black_rooks & mask;
            bool check8 = board->black_knights & mask;
            bool check9 = board->black_bishops & mask;
            bool check10 = board->black_queens & mask;
            bool check11 = board->black_king & mask;

            if (check || check6) {
                if (check) printf("P ");
                else printf("p ");
            }
            else if (check1 || check7) {
                if (check1) printf("R ");
                else printf("r ");
            }
            else if (check2 || check8) {
                if (check2) printf("N ");
                else printf("n ");
            }
            else if (check3 || check9) {
                if (check3) printf("B ");
                else printf("b ");
            }
            else if (check4 || check10) {
                if (check4) printf("Q ");
                else printf("q ");
            }
            else if (check5 || check11) {
                if (check5) printf("K ");
                else printf("k ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void fen_parse_board(char* fen, Bitboards* board) { 
    init_clear_board(board);
    int place = 63;
    int i = 0;
    bool board_finished = false;
    bool castle_finished = false;
    bool move_finished = false;
    bool en_passant_finished = false;
    bool half_move_finished = false;
    //for (size_t i = 0; i < len; i++) { 
    while (true) {
        char temp = fen[i];
        i++;
        if (!temp) { 
            break;
        }
        if (!board_finished) { 
            if (isdigit(temp)) { 
                place -=  temp - '0'; //ascii!
            }
            else if (temp == ' ') { 
                board_finished = true;
                continue;
            }
            else if (temp == '/') { 
                continue;
            }
            unsigned long long mask = 1ULL << place;
            if (islower(temp) || isupper(temp)) { 
                if (isupper(temp)) { //BLACK
                    board->empty_squares &= ~mask; // sets to 0 for emptysquare
                    if (temp == 'R') board->white_rooks |= mask;
                    else if (temp == 'N') board->white_knights |= mask;
                    else if (temp == 'B') board->white_bishops |= mask;
                    else if (temp == 'Q') board->white_queens |= mask;
                    else if (temp == 'K') board->white_king |= mask;
                    else if (temp == 'P') board->white_pawns |= mask;
                    place--;
                }
                else { //WHITE
                    board->empty_squares &= ~mask; // sets to 0 for emptysquare
                    if (temp == 'r') board->black_rooks |= mask;
                    else if (temp == 'n') board->black_knights |= mask;
                    else if (temp == 'b') board->black_bishops |= mask;
                    else if (temp == 'q') board->black_queens |= mask;
                    else if (temp == 'k') board->black_king |= mask;
                    else if (temp == 'p') board->black_pawns |= mask;
                    place--;
                }
            }
        }
        else { // enpassant, castling, 50 move rule
            if (temp == ' ') continue;
            if (!move_finished) { 
                if (temp == 'w') {
                    board->whites_move = true; 
                    move_finished = true;
                }
                else if (temp == 'b') {
                    board->whites_move = false; 
                    move_finished = true;
                }
            } 
            else if (!castle_finished) { 
                if (temp == 'q') board->black_castle_queen = true;
                else if (temp == 'k') board->black_castle_king = true;
                else if (temp == 'Q') board->white_castle_queen = true;
                else if (temp == 'K') board->white_castle_king = true;
                else if (temp == '-') {castle_finished = true; continue;}
                if (fen[i] == ' ') {castle_finished = true;} //checks next character if space
            } 
            else if (move_finished && !en_passant_finished) { 
                if (temp == '-') { 
                    board->en_passant = -1;
                    en_passant_finished = true;
                }
                
                else if (islower(temp)) { 
                    board->en_passant = 7 - (temp - 'a');
                }
                else if (isdigit(temp)) { 
                    board->en_passant += 8*(temp - '1');
                    en_passant_finished = true;
                }
            }
            else if (en_passant_finished && !half_move_finished) { 
                if (isdigit(temp)) { 
                    board->half_move = board->half_move*10;
                    board->half_move += temp - '0';
                    if (fen[i] == ' ') half_move_finished = true;
                }
            }
            else if (half_move_finished) { 
                if (temp == ' ') { 
                    continue;
                }
                if (isdigit(temp)) { 
                    board->full_move = board->full_move * 10;
                    board->full_move += temp - '0';
                    if (fen[i] == ' ') { 
                        break;
                    }
                }
            }
        }
    }
}

