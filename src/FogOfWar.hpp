#pragma once
#include "Chess.hpp"

class FogOfWar : public Chess{
    using Chess::Chess;
    std::array<std::array<char, 8>,8> maskedBoard;
    
public:

private:
    
    void printBoard() override {
        maskBoard();
        if (moveCount % 2 == 0) {  // print for white move
            std::cout << "  a b c d e f g h\n";
            for (int i = 0; i < BOARD_SIZE; ++i) {
                std::cout << 8 - i << " ";
                for (int j = 0; j < BOARD_SIZE; ++j) {
                    std::cout << maskedBoard[i][j] << ' ';
                }
                std::cout << 8 - i << "\n";
            }
            std::cout << "  a b c d e f g h\n";
        } else {  // print for black move
            std::cout << "  h g f e d c b a\n";
            for (int i = BOARD_SIZE - 1; i >= 0; --i) {
                std::cout << 8 - i << " ";
                for (int j = BOARD_SIZE - 1; j >= 0; --j) {
                    std::cout << maskedBoard[i][j] << ' ';
                }
                std::cout << 8 - i << "\n";
            }
            std::cout << "  h g f e d c b a\n";
        }   
    }
    void maskBoard() {
        for(int x = 0; x < 8; x++){
            for(int y = 0; y < 8; y++){
                maskedBoard[x][y] = '-';
            }
        }
        if(moveCount%2==0 && canWhiteCastleQueenside) maskedBoard[7][2] = board[7][2];
        if(moveCount%2==1 && canBlackCastleQueenside) maskedBoard[0][2] = board[0][2];
        for(int x = 0; x < 8; x++){
            for(int y = 0; y < 8; y++){
                if(maskedBoard[x][y] != ' '){
                    char piece = toupper(board[x][y]);
                    switch (piece){
                        case 'P':
                            showPossiblePawnMoves(x,y);
                            break;
                        case 'N':
                            showPossibleKnightMoves(x,y);
                            break;
                        case 'B':
                            showPossibleBishopMoves(x,y);
                            break;
                        case 'R':
                            showPossibleRookMoves(x,y);
                            break;
                        case 'Q':
                            showPossibleQueenMoves(x,y);
                            break;
                        case 'K':
                            showPossibleKingMoves(x,y);
                            break;
                    }
                }
            }
        }
    }
    void showPossiblePawnMoves(int currentX, int currentY){
        if(moveCount%2==0 && isupper(board[currentX][currentY])){
            maskedBoard[currentX][currentY] = board[currentX][currentY];
            if(currentX != 0){
                if(board[currentX-1][currentY] == ' '){
                    maskedBoard[currentX-1][currentY] = board[currentX-1][currentY];
                    if(currentX == 6 && board[currentX-2][currentY] == ' '){
                        maskedBoard[currentX-2][currentY] = board[currentX-2][currentY];
                    }
                }
                if(currentY > 0){
                    if(islower(board[currentX-1][currentY-1]))
                        maskedBoard[currentX-1][currentY-1] = board[currentX-1][currentY-1];
                }
                if(currentY < 7){
                    if(islower(board[currentX-1][currentY+1]))
                        maskedBoard[currentX-1][currentY+1] = board[currentX-1][currentY+1];
                }
                
            }
        }
        if(moveCount%2==1 && islower(board[currentX][currentY])){
            maskedBoard[currentX][currentY] = board[currentX][currentY];
            if(currentX != 7){
                if(board[currentX+1][currentY] == ' '){
                    maskedBoard[currentX+1][currentY] = board[currentX+1][currentY];
                    if(currentX == 1 && board[currentX+2][currentY] == ' '){
                        maskedBoard[currentX+2][currentY] = board[currentX+2][currentY];
                    }
                }
                if(currentY > 0){
                    if(islower(board[currentX+1][currentY-1]))
                        maskedBoard[currentX+1][currentY-1] = board[currentX+1][currentY-1];
                }
                if(currentY < 7){
                    if(islower(board[currentX+1][currentY+1]))
                        maskedBoard[currentX+1][currentY+1] = board[currentX+1][currentY+1];
                }
                
            }
        }
    }
    void showPossibleKnightMoves(int currentX, int currentY){
        if(moveCount%2==0 && isupper(board[currentX][currentY])){
            maskedBoard[currentX][currentY] = board[currentX][currentY];
            if(currentX+2 < 8){
                if(currentY+1 < 8)
                    maskedBoard[currentX+2][currentY+1] = board[currentX+2][currentY+1];
                if(currentY-1 >= 0)
                    maskedBoard[currentX+2][currentY-1] = board[currentX+2][currentY-1];
            }
            if(currentX-2 > 0){
                if(currentY+1 < 8)
                    maskedBoard[currentX-2][currentY+1] = board[currentX-2][currentY+1];
                if(currentY-1 >= 0)
                    maskedBoard[currentX-2][currentY-1] = board[currentX-2][currentY-1];
            }
            if(currentY+2 < 8){
                if(currentX+1 < 8)
                    maskedBoard[currentX+1][currentY+2] = board[currentX+1][currentY+2];
                if(currentX-1 >= 0)
                    maskedBoard[currentX-1][currentY+2] = board[currentX-1][currentY+2];
            }
            if(currentY-2 > 0){
                if(currentX+1 < 8)
                    maskedBoard[currentX+1][currentY-2] = board[currentX+1][currentY-2];
                if(currentX-1 >= 0)
                    maskedBoard[currentX-1][currentY-2] = board[currentX-1][currentY-2];
            }
        }
        if(moveCount%2==1 && islower(board[currentX][currentY])){
            maskedBoard[currentX][currentY] = board[currentX][currentY];
            if(currentX+2 < 8){
                if(currentY+1 < 8)
                    maskedBoard[currentX+2][currentY+1] = board[currentX+2][currentY+1];
                if(currentY-1 >= 0)
                    maskedBoard[currentX+2][currentY-1] = board[currentX+2][currentY-1];
            }
            if(currentX-2 > 0){
                if(currentY+1 < 8)
                    maskedBoard[currentX-2][currentY+1] = board[currentX-2][currentY+1];
                if(currentY-1 >= 0)
                    maskedBoard[currentX-2][currentY-1] = board[currentX-2][currentY-1];
            }
            if(currentY+2 < 8){
                if(currentX+1 < 8)
                    maskedBoard[currentX+1][currentY+2] = board[currentX+1][currentY+2];
                if(currentX-1 >= 0)
                    maskedBoard[currentX-1][currentY+2] = board[currentX-1][currentY+2];
            }
            if(currentY-2 > 0){
                if(currentX+1 < 8)
                    maskedBoard[currentX+1][currentY-2] = board[currentX+1][currentY-2];
                if(currentX-1 >= 0)
                    maskedBoard[currentX-1][currentY-2] = board[currentX-1][currentY-2];
            }
        }
    }
    void showPossibleBishopMoves(int currentX, int currentY){
        int directions[4][2] = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
        if(moveCount % 2 == 0 && isupper(board[currentX][currentY])) {
            maskedBoard[currentX][currentY] = board[currentX][currentY];
            for (auto& dir : directions) {
                int possibleX = currentX + dir[0];
                int possibleY = currentY + dir[1];

                // Continue in the direction until we hit the end of the board or another piece
                while (possibleX >= 0 && possibleX < BOARD_SIZE && possibleY >= 0 && possibleY < BOARD_SIZE) {
                    maskedBoard[possibleX][possibleY] = board[possibleX][possibleY];
                    // If we hit another piece, stop in this direction
                    if (board[possibleX][possibleY] != ' ') {
                        break;
                    }
                    possibleX += dir[0];
                    possibleY += dir[1];
            }
        }
        }
        if(moveCount % 2 == 1 && islower(board[currentX][currentY])) {
            maskedBoard[currentX][currentY] = board[currentX][currentY];
            for (auto& dir : directions) {
                int possibleX = currentX + dir[0];
                int possibleY = currentY + dir[1];

                // Continue in the direction until we hit the end of the board or another piece
                while (possibleX >= 0 && possibleX < BOARD_SIZE && possibleY >= 0 && possibleY < BOARD_SIZE) {
                    maskedBoard[possibleX][possibleY] = board[possibleX][possibleY];
                    // If we hit another piece, stop in this direction
                    if (board[possibleX][possibleY] != ' ') {
                        break;
                    }
                    possibleX += dir[0];
                    possibleY += dir[1];
                }
            }
        }
    }
    void showPossibleRookMoves(int currentX, int currentY){
        int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        if(moveCount % 2 == 0 && isupper(board[currentX][currentY])) {
            maskedBoard[currentX][currentY] = board[currentX][currentY];
            for (auto& dir : directions) {
                int possibleX = currentX + dir[0];
                int possibleY = currentY + dir[1];

                // Continue in the direction until we hit the end of the board or another piece
                while (possibleX >= 0 && possibleX < BOARD_SIZE && possibleY >= 0 && possibleY < BOARD_SIZE) {
                    maskedBoard[possibleX][possibleY] = board[possibleX][possibleY];
                    // If we hit another piece, stop in this direction
                    if (board[possibleX][possibleY] != ' ') {
                        break;
                    }
                    possibleX += dir[0];
                    possibleY += dir[1];
            }
        }
        }
        if(moveCount % 2 == 1 && islower(board[currentX][currentY])) {
            maskedBoard[currentX][currentY] = board[currentX][currentY];
            for (auto& dir : directions) {
                int possibleX = currentX + dir[0];
                int possibleY = currentY + dir[1];

                // Continue in the direction until we hit the end of the board or another piece
                while (possibleX >= 0 && possibleX < BOARD_SIZE && possibleY >= 0 && possibleY < BOARD_SIZE) {
                    maskedBoard[possibleX][possibleY] = board[possibleX][possibleY];
                    // If we hit another piece, stop in this direction
                    if (board[possibleX][possibleY] != ' ') {
                        break;
                    }
                    possibleX += dir[0];
                    possibleY += dir[1];
                }
            }
        }
    }
    void showPossibleQueenMoves(int currentX, int currentY){
        if(moveCount%2==0 && isupper(board[currentX][currentY])){
            maskedBoard[currentX][currentY] = board[currentX][currentY];
            showPossibleBishopMoves(currentX, currentY);
            showPossibleRookMoves(currentX, currentY);
        }
        if(moveCount%2==1 && islower(board[currentX][currentY])){
            maskedBoard[currentX][currentY] = board[currentX][currentY];
            showPossibleBishopMoves(currentX, currentY);
            showPossibleRookMoves(currentX, currentY);
        }
    }
    void showPossibleKingMoves(int currentX, int currentY){
        int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        { 0, -1},          { 0, 1},
        { 1, -1}, { 1, 0}, { 1, 1}
        };
        if(moveCount%2==0 && isupper(board[currentX][currentY])){
            maskedBoard[currentX][currentY] = 'K';
            for (auto& dir : directions) {
                int possibleX = currentX + dir[0];
                int possibleY = currentY + dir[1];

                if (possibleX >= 0 && possibleX < BOARD_SIZE && possibleY >= 0 && possibleY < BOARD_SIZE) {
                    maskedBoard[possibleX][possibleY] = board[possibleX][possibleY];
                }
            }
        }
        if(moveCount%2==1 && islower(board[currentX][currentY])){
            maskedBoard[currentX][currentY] = 'k';
            for (auto& dir : directions) {
                int possibleX = currentX + dir[0];
                int possibleY = currentY + dir[1];

                if (possibleX >= 0 && possibleX < BOARD_SIZE && possibleY >= 0 && possibleY < BOARD_SIZE) {
                    maskedBoard[possibleX][possibleY] = board[possibleX][possibleY];
                }
            }

        }
    }

};