#pragma once
#include "Chess.hpp"

class SpellChess : public Chess {
private:
    int whiteAbilities[2] = {3,5};
    int blackAbilities[2] = {3,5};
    struct JumpSpell{
        char piece;
        int x;
        int y;

        JumpSpell(){
            piece = ' ';
            x = -1;
            y = -1;
        }
    };
    struct FreezeSpell{
        char piece;
        int x;
        int y;

        FreezeSpell(){
            piece = ' ';
            x = -1;
            y = -1;
        }
    };
    JumpSpell jumpSpell;
    FreezeSpell whiteFreezeSpell;
    FreezeSpell blackFreezeSpell;

public:

    SpellChess() : Chess() {}


    // Override the play function to include abilities usage
    void play() override {
        std::string move, spell, input;
        printBoard();
        int gameResult = 0; 
        bool usingSpell = false;
        while (gameResult == 0) {
            std::cout << "Use Spell (yes or anything else for no)? ";
            std::cin >> input;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // Convert the input to a boolean
            usingSpell = (input == "yes");
            if(usingSpell){
                std::cout << "Enter f for freeze or j for jump then enter the index (e.g., fd4 or jh6): ";
                std::getline(std::cin, spell);
                if(spell[0] == 'f' && spell.length() == 3 && applyFreeze(spell)) {
                    std::cout << "Applied Freeze\n"; }
                else if(spell[0] == 'j' && spell.length() == 3 && applyJump(spell)){
                    std::cout << "Applied Jump\n"; }
                else if(spell == "exit" || spell == "Exit"){
                    std::cout << "Exit\n";
                    break; }
                else{
                    std::cout << "Not Used Correctly. Try again\n";
                    continue; }
            }
            printBoard();
            std::cout << "Enter move (" << (moveCount % 2 == 0 ? "White" : "Black") << "): ";
            std::getline(std::cin, move);
            if (move == "exit" || move == "Exit") {
                break;
            }
            std::cout << "1\n";
            
            if(frozePiece(move)){
                std::cout << "Piece is Frozen.  Please try again\n";
                continue;
            }
            if (!makeMove(move)) {
                std::cout << "Invalid move. Please try again.\n";
                continue;
            }
            std::cout << "2\n";
            undoSpells();
            std::cout << "3\n";
            moveHistory.push_back(move);
            gameResult = checkGameResult();
            moveCount++;
            usingSpell = false;
            printBoard();
        }
        if(gameResult == 1) std::cout << "White Won\n";
        if(gameResult == 2) std::cout << "Black Won\n";
        if(gameResult == 3) std::cout << "Draw\n";
    }

protected:
    bool frozePiece(std::string move){
        int pieceY = tolower(move[0]) - 'a';
        int pieceX = '8' - move[1];
        
        if(moveCount%2==0){
            if(blackFreezeSpell.x != -1){
                if(blackFreezeSpell.x == pieceX && blackFreezeSpell.y == pieceY){
                    std::cout << "Frozen Piece\n";
                    return true;
                }
            }
        }
        else{
            if(whiteFreezeSpell.x != -1){
                if(whiteFreezeSpell.x == pieceX && whiteFreezeSpell.y == pieceY){
                    std::cout << "Frozen Piece\n";
                    return true;
                }
            }
        }
        return false;
    }
    bool applyFreeze(std::string spell){
        if(moveCount%2==0 && whiteAbilities[1] > 0){
            whiteFreezeSpell.y = tolower(spell[1]) - 'a';
            whiteFreezeSpell.x = '8' - spell[2];
            if(!(whiteFreezeSpell.x<8) && !(whiteFreezeSpell.x>-1) && !(whiteFreezeSpell.y<8) && !(whiteFreezeSpell.y>-1))
                return false;
            whiteFreezeSpell.piece = board[whiteFreezeSpell.x][whiteFreezeSpell.y];
            board[whiteFreezeSpell.x][whiteFreezeSpell.y] = 'f';
            whiteAbilities[1]--;
        }
        else if(moveCount%2 && blackAbilities[1] > 0){
            blackFreezeSpell.y = tolower(spell[1]) - 'a';
            blackFreezeSpell.x = '8' - spell[2];
            if(!(blackFreezeSpell.x<8) && !(blackFreezeSpell.x>-1) && !(blackFreezeSpell.y<8) && !(blackFreezeSpell.y>-1))
                return false;
            blackFreezeSpell.piece = board[blackFreezeSpell.x][blackFreezeSpell.y];
            board[whiteFreezeSpell.x][whiteFreezeSpell.y] = 'f';
            blackAbilities[1]--;
        }
        return true;
    }
    bool applyJump(std::string spell){
        if(moveCount%2==0 && whiteAbilities[0] < 1){
            return false;
        }
        if(moveCount%2==1 && blackAbilities[0] < 1){
            return false;
        }
        if(moveCount%2 == 0){
            whiteAbilities[0]--;
        }
        if(moveCount%2 == 1){
            blackAbilities[0]--;
        }

        jumpSpell.y = tolower(spell[1]) - 'a';
        jumpSpell.x = '8' - spell[2];

        if(!(jumpSpell.x < 8) || !(jumpSpell.x > -1) || !(jumpSpell.y < 8) || !(jumpSpell.y > -1)) {
            std::cout << "wrong index \n";
            return false;
        }
        jumpSpell.piece = board[jumpSpell.x][jumpSpell.y];
        board[jumpSpell.x][jumpSpell.y] = ' ';
        return true;
    }
    void undoSpells(){
        if(jumpSpell.x != -1){
            board[jumpSpell.x][jumpSpell.y] = jumpSpell.piece;
            jumpSpell.x = -1;
        }
        if(moveCount%2==0 && blackFreezeSpell.x != -1){
            board[blackFreezeSpell.x][blackFreezeSpell.y] = blackFreezeSpell.piece;
            blackFreezeSpell.x = -1;
        }
        if(moveCount%2==1 && whiteFreezeSpell.x != -1){
            board[whiteFreezeSpell.x][whiteFreezeSpell.y] = whiteFreezeSpell.piece;
            whiteFreezeSpell.x = -1;
        }
    }
};
