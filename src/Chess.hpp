#pragma once
#include <array>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

class Chess {
protected:
    static const int BOARD_SIZE = 8;
    std::array<std::array<char,8>,8> board;
    int moveCount;
    std::vector<std::string> moveHistory;
    bool canWhiteCastleQueenside;
    bool canWhiteCastleKingside;
    bool canBlackCastleQueenside;
    bool canBlackCastleKingside;

public:
    Chess() : moveCount(0) {
        canWhiteCastleQueenside = canWhiteCastleKingside = canBlackCastleQueenside = canBlackCastleKingside = true;
        
        initializeBoard();
    }
    virtual void play() {
        std::string move;
        printBoard();
        int gameResult = 0; // 1 is white won, 2 is black won, 3 is a draw
        while (gameResult == 0) {
            std::cout << "Enter move (" << (moveCount % 2 == 0 ? "White" : "Black") << "): ";
            std::getline(std::cin, move);
            if (move == "exit") {
                break;
            }
            if (!makeMove(move)) {
                std::cout << "Invalid move. Please try again." << std::endl;
                continue;
            }
            moveHistory.push_back(move);
            gameResult = checkGameResult();
            moveCount++;
            printBoard();
        }
        if(gameResult == 1) std::cout << "White Won\n";
        if(gameResult == 2) std::cout << "Black Won\n";
        if(gameResult == 3) std::cout << "Draw\n";
    }

protected:
    void initializeBoard() {
        // Set pawns
        for(int x = 0; x < BOARD_SIZE; x++){
            for(int y = 0; y < BOARD_SIZE; y++){
                board[x][y] = ' ';
            }
        }
        
        for (int i = 0; i < BOARD_SIZE; i++) {
            board[6][i] = 'P'; // White pawns
            board[1][i] = 'p'; // Black pawns
        }

        // Set the rest of the pieces
        const std::string pieces = "RNBQKBNR";
        for (int i = 0; i < BOARD_SIZE; i++) {
            board[7][i] = pieces[i]; // White pieces
            board[0][i] = tolower(pieces[i]); // Black pieces
        }
    }
    virtual void printBoard() {
        if (moveCount % 2 == 0) {  // print for white move
            std::cout << "  a b c d e f g h\n";
            for (int i = 0; i < BOARD_SIZE; ++i) {
                std::cout << 8 - i << " ";
                for (int j = 0; j < BOARD_SIZE; ++j) {
                    std::cout << board[i][j] << ' ';
                }
                std::cout << 8 - i << "\n";
            }
            std::cout << "  a b c d e f g h\n";
        } else {  // print for black move
            std::cout << "  h g f e d c b a\n";
            for (int i = BOARD_SIZE - 1; i >= 0; --i) {
                std::cout << 8 - i << " ";
                for (int j = BOARD_SIZE - 1; j >= 0; --j) {
                    std::cout << board[i][j] << ' ';
                }
                std::cout << 8 - i << "\n";
            }
            std::cout << "  h g f e d c b a\n";
        }   
    }
    bool makeMove(const std::string& move) {
        int startX, startY, endX, endY;
        if (!convertNotation(move, startX, startY, endX, endY)) {
            return false;
        }
        char piece = board[startX][startY];
        if(moveCount%2==0 && islower(piece)){return false;} //white player is moving black's pieces
        if(moveCount%2==1 && isupper(piece)){return false;} //black player is moving white's pieces
        if (tolower(piece) == 'p' && !legalPawnMove(startX, startY, endX, endY, piece, move[2])) {
            return false;
        }
        else if (tolower(piece) == 'n' && !legalKnightMove(startX, startY, endX, endY)) {
            return false;
        }
        else if (tolower(piece) == 'b' && !legalBishopMove(startX, startY, endX, endY)) {
            return false;
        }
        else if (tolower(piece) == 'r' && !legalRookMove(startX, startY, endX, endY)) {
            return false;
        }
        else if (tolower(piece) == 'q') {
            // For a queen, check if the move is either a straight line (like a rook) or diagonal (like a bishop)
            if (startX == endX || startY == endY) {
                if (!legalRookMove(startX, startY, endX, endY)) {
                    return false;
                }
            } else {
                if (!legalBishopMove(startX, startY, endX, endY)) {
                    return false;
                }
            }
        }
        else if (tolower(piece) == 'k' && !legalKingMove(startX, startY, endX, endY)) {
            return false;
        }
        if (tolower(piece) == 'r') {
            if (startX == 7 && startY == 0) canWhiteCastleQueenside = false;
            if (startX == 7 && startY == 7) canWhiteCastleKingside = false;
            if (startX == 0 && startY == 0) canBlackCastleQueenside = false;
            if (startX == 0 && startY == 7) canBlackCastleKingside = false;
        }else if (tolower(piece) == 'k') {
            if (startX == 7) { 
                canWhiteCastleQueenside = canWhiteCastleKingside = false;
            } else {
                canBlackCastleQueenside = canBlackCastleKingside = false;
            }
        }
        
        // make move
        board[endX][endY] = board[startX][startY];
        board[startX][startY] = ' ';

        // promote pawn
        if (tolower(piece) == 'p') {
            if ((moveCount % 2 == 0 && endX == 0) || (moveCount % 2 == 1 && endX == 7)) {
                promotePawn(endX, endY); 
            }
        }

        return true;
    }
    bool convertNotation(const std::string& move, int& startX, int& startY, int& endX, int& endY) {
        if (move.size() < 4) {
            return false;
        }

        startY = tolower(move[0]) - 'a';
        startX = '8' - move[1];
        endY = tolower(move[2]) - 'a';
        endX = '8' - move[3];

        std::cout << startY << startX << endY << endX << "\n";

        return startX >= 0 && startX < BOARD_SIZE && startY >= 0 && startY < BOARD_SIZE &&
               endX >= 0 && endX < BOARD_SIZE && endY >= 0 && endY < BOARD_SIZE;
    }
    int checkGameResult(){
        bool whiteKingAlive;
        bool blackKingAlive;
        for(int x = 0; x < BOARD_SIZE; x++){
            for(int y = 0; y < BOARD_SIZE; y++){
                if(board[x][y] == 'K') whiteKingAlive = true;
                if(board[x][y] == 'k') blackKingAlive = true;
            }
        }
        if(whiteKingAlive && blackKingAlive) return 0;
        if(whiteKingAlive && !blackKingAlive) return 1;
        if(!whiteKingAlive && blackKingAlive) return 2;
        return 3; // both kings are gone, the game is a draw
    }
    bool legalPawnMove(int startX, int startY, int endX, int endY, char pawn, char lastColumn) {
        if(endX < 8 && endX >= 0 && endY < 8 && endY >= 0){
            if (pawn == 'P') {
                // Standard move
                if (startY == endY && board[endX][endY] == ' ' && ((startX - endX) == 1)) {
                    return true;
                }
                // Initial double move
                else if (startY == endY && board[endX][endY] == ' ' && (startX == 6) && ((startX - endX) == 2) && board[startX - 1][startY] == ' ') {
                    return true;
                }
                // Diagonal capture
                else if (abs(startY - endY) == 1 && (startX - endX) == 1 && islower(board[endX][endY])) {
                    return true;
                }
                // check for en passant
                if (startX == 3 && abs(startY - endY) == 1 && endX == 2) {
                    std::string lastMove = moveHistory.back();
                    int lastMoveEndCol = tolower(lastMove[2]) - 'a'; // Correct: converts 'd' to 3
                    int lastMoveEndRow = '8' - lastMove[3]; // Correct: converts '5' to 3
                    char lastPieceMoved = board[lastMoveEndCol][lastMoveEndRow];
                    
                    if (lastMove[1] == '7' && lastMove[3] == '5' && lastPieceMoved == 'p' && lastMove[2] == lastColumn) { 
                        board[3][endY] = ' '; 
                        return true;
                    }
                }
                return false;
            }
            else if (pawn == 'p') {
                // Standard move
                if (startY == endY && board[endX][endY] == ' ' && ((endX - startX) == 1)) {
                    return true;
                }
                // Initial double move
                else if (startY == endY && board[endX][endY] == ' ' && (startX == 1) && ((endX - startX) == 2) && board[startX + 1][startY] == ' ') {
                    return true;
                }
                // Diagonal capture
                else if (abs(startY - endY) == 1 && (endX - startX) == 1 && isupper(board[endX][endY])) {
                    return true;
                }
                // check for en passant
                if (startX == 4 && abs(startY - endY) == 1 && endX == 5) {
                    std::string lastMove = moveHistory.back();
                    int lastMoveEndCol = tolower(lastMove[2]) - 'a'; // Correct: converts 'd' to 3
                    int lastMoveEndRow = '8' - lastMove[3]; // Correct: converts '5' to 3
                    char lastPieceMoved = board[lastMoveEndCol][lastMoveEndRow];
                    
                    if (lastMove[1] == '2' && lastMove[3] == '4' && lastPieceMoved == 'P' && lastMove[2] == lastColumn) { 
                        board[5][endY] = ' '; 
                        return true;
                    }
                }
                return false;
            }
        }
        return false;
    }
    bool legalKnightMove(int startX, int startY, int endX, int endY) {
        if (((abs(startX - endX) == 2 && abs(startY - endY) == 1) || (abs(startX - endX) == 1 && abs(startY - endY) == 2)) &&
        endX < 8 && endX >= 0 && endY < 8 && endY >= 0) {

            if (moveCount % 2 == 0) {
                return board[endX][endY] == ' ' || islower(board[endX][endY]);
            }
            else {
                return board[endX][endY] == ' ' || isupper(board[endX][endY]);
            }
        }

        
        return false;
    }
    bool legalBishopMove(int startX, int startY, int endX, int endY) {
        // Check if the move is diagonal by comparing the absolute difference of the coordinates
        if (abs(startX - endX) != abs(startY - endY)) {
            return false; // Not a diagonal move
        }

        // Check if the path is clear
        int pathX = (endX - startX > 0) ? 1 : -1;
        int pathY = (endY - startY > 0) ? 1 : -1;

        int currentX = startX + pathX;
        int currentY = startY + pathY;
        while (currentX != endX && currentY != endY) {
            if (board[currentX][currentY] != ' ') {
                return false; // Path is not clear
            }
            currentX += pathX;
            currentY += pathY;
        }

        // Check for capture
        if (moveCount % 2 == 0 && islower(board[endX][endY])) {
            return true; // White move, black piece can be captured
        } else if (moveCount % 2 != 0 && isupper(board[endX][endY])) {
            return true; // Black move, white piece can be captured
        }

        // Move is legal if the end position is empty
        return board[endX][endY] == ' ';
    }
    bool legalRookMove(int startX, int startY, int endX, int endY) {
        // Rooks move either horizontally or vertically, so one coordinate must be the same
        if (startX != endX && startY != endY) {
            return false; // Not a horizontal or vertical move
        }

        // Check if the path is clear
        int pathX = (startX == endX) ? 0 : ((endX - startX > 0) ? 1 : -1);
        int pathY = (startY == endY) ? 0 : ((endY - startY > 0) ? 1 : -1);

        int currentX = startX + pathX;
        int currentY = startY + pathY;
        while ((pathX != 0 && currentX != endX) || (pathY != 0 && currentY != endY)) {
            if (board[currentX][currentY] != ' ') {
                return false; // Path is not clear
            }
            currentX += pathX;
            currentY += pathY;
        }

        // Check for capture
        if (moveCount % 2 == 0) { // White's move
            return board[endX][endY] == ' ' || islower(board[endX][endY]);
        } else { // Black's move
            return board[endX][endY] == ' ' || isupper(board[endX][endY]);
        }
    }
    bool legalKingMove(int startX, int startY, int endX, int endY) {
        int dx = abs(startX - endX);
        int dy = abs(startY - endY);

        // regular move
        if ((dx == 1 && dy == 1) || 
            (dx == 1 && dy == 0) || 
            (dx == 0 && dy == 1)) { 
            // Check for capture
            if (moveCount % 2 == 0) { 
                return board[endX][endY] == ' ' || islower(board[endX][endY]);
            } else {
                return board[endX][endY] == ' ' || isupper(board[endX][endY]);
            }
        }

        // Castling
        if (dx == 0 && dy == 2) {
            // Check for the conditions for castling
            if (canCastle(startX, startY, endX, endY)) {
                executeCastling(startX, startY, endX, endY);
                return true;
            }
        }

        return false; // If none of the valid moves are made, return false
    }
    bool canCastle(int startX, int startY, int endX, int endY) {
        bool isWhite = (startX == 7);
        bool castleLeft = (endY < startY);
        bool canCastle = (isWhite && castleLeft) ? canWhiteCastleQueenside : (isWhite) ? canWhiteCastleKingside : (castleLeft) ? canBlackCastleQueenside : canBlackCastleKingside;

        if (!canCastle) {
            return false;
        }

        // Check if the path between the king and the rook is clear
        int yDirection = (endY < startY) ? -1 : 1;
        int currentY = startY + yDirection;
        while (currentY != endY) {
            if (board[startX][currentY] != ' ') {
                return false;
            }
            currentY += yDirection;
        }

        return true; // All conditions are met
    }
    void executeCastling(int startX, int startY, int endX, int endY) {

        if(endY > startY){
            int rookStartY = 7;
            int rookEndY = 5;

            board[startX][rookEndY] = board[startX][rookStartY];
            board[startX][rookStartY] = ' ';
        }
        else{
            int rookStartY = 0;
            int rookEndY = 3;

            board[startX][rookEndY] = board[startX][rookStartY];
            board[startX][rookStartY] = ' ';
        }

        // Update castling rights
        if (startX == 7) { // White
            canWhiteCastleQueenside = canWhiteCastleKingside = false;
        } else { // Black
            canBlackCastleQueenside = canBlackCastleKingside = false;
        }
    }
    void promotePawn(int x, int y) {
        char newPiece;
        std::cout << "Pawn promotion! Enter new piece (q, r, b, n): ";
        std::cin >> newPiece;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (tolower(newPiece) != 'q' && tolower(newPiece) != 'r' && tolower(newPiece) != 'b' && tolower(newPiece) != 'n') {
            std::cout << "Invalid piece for promotion. Promotion to queen." << std::endl;
            newPiece = 'q';
        }
        board[x][y] = (isupper(board[x][y])) ? toupper(newPiece) : tolower(newPiece);
    }
};