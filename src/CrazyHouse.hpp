#pragma once
#include <cstdint>
#include "Chess.hpp"

class CrazyHouse : public Chess{
    struct pieceInventory{
        std::uint8_t pawns = 0;
        std::uint8_t knights = 0;
        std::uint8_t bishops = 0;
        std::uint8_t rooks = 0;
        std::uint8_t queens = 0;
    };
    pieceInventory whitePlayerInventory;
    pieceInventory blackPlayerInventory;


    public:
        CrazyHouse() : Chess() {}

        void play() override{
            std::string move, placePiece, piecePlacement;
            printBoard();
            int gameResult = 0; // 1 is white won, 2 is black won, 3 is a draw
            bool isPlacingPiece;
            char piece;
            while (gameResult == 0) {
                std::cout << "Do you want to place a piece (type yes or anything else for no)?";
                std::getline(std::cin, placePiece);

                isPlacingPiece = (placePiece == "yes" || placePiece == "Yes");
                if(isPlacingPiece){
                    std::cout << "Type the piece and then the index (e.g., nd4, rc7): ";
                    std::getline(std::cin, piecePlacement);
                    addPieceToBoard(piecePlacement);
                }

                std::cout << "Enter move (" << (moveCount % 2 == 0 ? "White" : "Black") << "): ";
                std::getline(std::cin, move);
                
                if (move == "exit") {
                    break;
                }
                piece = board['8' - move[3]][tolower(move[2]) - 'a'];
                if (!makeMove(move)) {
                    std::cout << "Invalid move. Please try again." << std::endl;
                    continue;
                }
                if(piece != ' '){
                    addPieceToInventory(piece);
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

        void addPieceToInventory(char piece){
            if(moveCount%2==0){
                switch(piece){
                case 'p':
                    whitePlayerInventory.pawns++;
                    break;
                case 'n':
                    whitePlayerInventory.knights++;
                    break;
                case 'b':
                    whitePlayerInventory.bishops++;
                    break;
                case 'r':
                    whitePlayerInventory.rooks++;
                    break;
                case 'q':
                    whitePlayerInventory.queens++;
                    break;
                }
            }
            else{
                switch(tolower(piece)){
                case 'p':
                    blackPlayerInventory.pawns++;
                    break;
                case 'n':
                    blackPlayerInventory.knights++;
                    break;
                case 'b':
                    blackPlayerInventory.bishops++;
                    break;
                case 'r':
                    blackPlayerInventory.rooks++;
                    break;
                case 'q':
                    blackPlayerInventory.queens++;
                    break;
                }
            }
        }
        void addPieceToBoard(std::string piecePlacement){
            if(moveCount%2==0 && board['8' - piecePlacement[2]][tolower(piecePlacement[1]) - 'a'] == ' '){
                switch(tolower(piecePlacement[0])){
                    case 'p':
                        if(whitePlayerInventory.pawns > 0){
                            board['8' - piecePlacement[2]][tolower(piecePlacement[1]) - 'a'] = 'P';
                            whitePlayerInventory.pawns--;
                        }
                        break;
                    case 'n':
                        if(whitePlayerInventory.knights > 0){
                            board['8' - piecePlacement[2]][tolower(piecePlacement[1]) - 'a'] = 'N';
                            whitePlayerInventory.knights--;
                        }
                        break;
                    case 'b':
                        if(whitePlayerInventory.bishops > 0){
                            board['8' - piecePlacement[2]][tolower(piecePlacement[1]) - 'a'] = 'B';
                            whitePlayerInventory.bishops--;
                        }
                        break;
                    case 'r':
                        if(whitePlayerInventory.rooks > 0){
                            board['8' - piecePlacement[2]][tolower(piecePlacement[1]) - 'a'] = 'R';
                            whitePlayerInventory.rooks--;
                        }
                        break;
                    case 'q':
                        if(whitePlayerInventory.queens > 0){
                            board['8' - piecePlacement[2]][tolower(piecePlacement[1]) - 'a'] = 'Q';
                            whitePlayerInventory.queens--;
                        }
                        break;
                }
            }
            else if(moveCount%2==1 && board['8' - piecePlacement[2]][tolower(piecePlacement[1]) - 'a']){
                switch(tolower(piecePlacement[0])){
                    case 'p':
                        if(blackPlayerInventory.pawns > 0){
                            board['8' - piecePlacement[2]][tolower(piecePlacement[1]) - 'a'] = 'p';
                            blackPlayerInventory.pawns--;
                        }
                        break;
                    case 'n':
                        if(blackPlayerInventory.knights > 0){
                            board['8' - piecePlacement[2]][tolower(piecePlacement[1]) - 'a'] = 'n';
                            blackPlayerInventory.knights--;
                        }
                        break;
                    case 'b':
                        if(blackPlayerInventory.bishops > 0){
                            board['8' - piecePlacement[2]][tolower(piecePlacement[1]) - 'a'] = 'b';
                            blackPlayerInventory.bishops--;
                        }
                        break;
                    case 'r':
                        if(blackPlayerInventory.rooks > 0){
                            board['8' - piecePlacement[2]][tolower(piecePlacement[1]) - 'a'] = 'r';
                            blackPlayerInventory.rooks--;
                        }
                        break;
                    case 'q':
                        if(blackPlayerInventory.queens > 0){
                            board['8' - piecePlacement[2]][tolower(piecePlacement[1]) - 'a'] = 'q';
                            blackPlayerInventory.queens--;
                        }
                        break;
                }
            }
        }
};