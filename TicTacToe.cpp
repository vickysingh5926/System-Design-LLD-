#include <bits/stdc++.h>
using namespace std;

enum class PieceType{X,O};

class PlayingPiece{

    public:
    PieceType pieceType;
    PlayingPiece(PieceType type):pieceType(type){}
    virtual ~PlayingPiece()=default;
};
class PlayingPieceX: public PlayingPiece{
    public:
    PlayingPieceX():PlayingPiece(PieceType::X){}

};
class PlayingPieceO:public PlayingPiece{
    public:
    PlayingPieceO():PlayingPiece(PieceType::O){}
};
class Player{

    public:
    string name;
    shared_ptr<PlayingPiece>playingPiece;

    Player(string n,shared_ptr<PlayingPiece>piece){
        name=move(n);
        playingPiece=move(piece);
    }
};
class Board{
    public:
    int size;
    vector<vector<shared_ptr<PlayingPiece>>>board;

    Board(int s){
        size=s;
        board=vector<vector<shared_ptr<PlayingPiece>>>(size,vector<shared_ptr<PlayingPiece>>(size,nullptr));

    }
    void printBoard(){
        cout<<"Current Board"<<endl;

        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++){

                if(board[i][j]==nullptr)cout<<"-";
                else
                cout<<(board[i][j]->pieceType==PieceType::X?"X":"O");
            }
            cout<<endl;
        }
        cout<<endl;
    }
     vector<pair<int, int>> getFreeCells() {
        vector<pair<int, int>> freeCells;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (board[i][j] == nullptr) freeCells.push_back({i, j});
            }
        }
        return freeCells;
    }

    bool addPiece(int row, int col, shared_ptr<PlayingPiece> piece) {
        if (row < 0 || row >= size || col < 0 || col >= size) return false;
        if (board[row][col] != nullptr) return false;
        board[row][col] = piece;
        return true;
    }

};

class TicTacToe{
    deque<Player>players;
    unique_ptr<Board>gameboard;

    public:

    void initializeGame(){
        players.clear();

        auto crossPiece=make_shared<PlayingPieceX>();
        Player player1("Player1",crossPiece);

        auto noughtPiece=make_shared<PlayingPieceO>();
        Player player2("Player2",noughtPiece);

        players.push_back(player1);
        players.push_back(player2);

        gameboard=make_unique<Board>(3);
    }

    string startGame(){
        bool noWinner=true;

        while(noWinner){

            Player playerTurn=players.front();
            players.pop_front();

            gameboard->printBoard();
            auto freeSpaces=gameboard->getFreeCells();

            if(freeSpaces.empty()){
               noWinner=false;
                continue;
            }
            cout<<"Player:"<<playerTurn.name<<"Enter row,col:";
            string s;
            getline(cin,s);
            if(s.empty())getline(cin,s);

            stringstream ss(s);
            string rowStr,colStr;
            getline(ss,rowStr,',');
            getline(ss,colStr,',');

            int inputRow=stoi(rowStr);
            int inputCol=stoi(colStr);

            bool success=gameboard->addPiece(inputRow,inputCol,playerTurn.playingPiece);
            if(!success){
                cout<<"Incorrect pos ,try again"<<endl;
                players.push_front(playerTurn);
                continue;
            }

            players.push_back(playerTurn);

            bool winner=isThereWinner(inputRow,inputCol,playerTurn.playingPiece->pieceType);
            if(winner){
                gameboard->printBoard();
                return playerTurn.name;
            }
        }
        gameboard->printBoard();
        return "tie";
    }

     bool isThereWinner(int row,int col, PieceType pieceType){

        bool rowMatch=true,colMatch=true,diagMatch=true,antiDiagMatch=true;

        for(int i=0;i<gameboard->size;i++){
            if(gameboard->board[row][i]==nullptr || gameboard->board[row][i]->pieceType!=pieceType)
            rowMatch= false;
        }

        for(int i=0;i<gameboard->size;i++){
             if(gameboard->board[i][col]==nullptr || gameboard->board[i][col]->pieceType!=pieceType)
             colMatch=false;
        }

        for(int i=0,j=0;i<gameboard->size;i++,j++){
            if(gameboard->board[i][j]==nullptr || gameboard->board[i][j]->pieceType!=pieceType)
            diagMatch=false;
        }

        for(int i=0,j=gameboard->size-1;i<gameboard->size;i++,j--){

             if(gameboard->board[i][j]==nullptr || gameboard->board[i][j]->pieceType!=pieceType)
            antiDiagMatch=false;
        }
        return rowMatch || colMatch || diagMatch || antiDiagMatch;
     }
};

int main(){
    TicTacToe game;
    game.initializeGame();
    cout << "Game winner is: " << game.startGame() << endl;
    return 0;
}
