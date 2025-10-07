#include <bits/stdc++.h>
using namespace std;

class Jump{
    public:
    int start;
    int end;
    Jump():start(0),end(0){}
};

class Cell{
    public:
    Jump* jump;

    Cell(){
        jump=nullptr;
    }
};

class Board{
    public:
    vector<vector<Cell>>cells;
    Board(int boardSize,int numberOfSnakes,int numberOfLadders){
        initializeCells(boardSize);
        addSnakesLadders(numberOfSnakes,numberOfLadders);
    }

    void initializeCells(int boardSize){
        cells.resize(boardSize,vector<Cell>(boardSize));
    }

    void addSnakesLadders(int numberOfSnakes,int numberOfLadders){

        int size=cells.size();

        while(numberOfSnakes>0){
            int snakeHead=randInt(1,size*size-2);
            int snakeTail=randInt(1,size*size-2);

            if(snakeTail>=snakeHead)continue;

            Jump* snakeObj=new Jump();
            snakeObj->start=snakeHead;
            snakeObj->end=snakeTail;

            Cell &cell=getCell(snakeHead);
            cell.jump=snakeObj;

            numberOfSnakes--;
        }

        while(numberOfLadders>0){

            int ladderHead=randInt(1,size*size-2);
            int ladderEnd=randInt(1,size*size-2);

            if(ladderHead>=ladderEnd)continue;

            Jump* ladderObj=new Jump();
            ladderObj->start=ladderHead;
            ladderObj->end=ladderEnd;

             Cell& cell=getCell(ladderHead);
             cell.jump=ladderObj;
             numberOfLadders--;
        }

    }
     Cell & getCell(int playerPosition){

            int size=cells.size();
            int row=playerPosition/size;
            int col=playerPosition%size;
            return  cells[row][col];
        }
    private:
        int randInt(int low,int high){
            return low+rand()%(high-low+1);
        }
};

class Dice{

    public:
    int diceCount;
    int minValue;
    int maxValue;

    Dice(int diceCount){
        this->diceCount=diceCount;
        minValue=1;
        maxValue=6;
    }

    int rollDice(){
        int totalSum=0;
        for(int i=0;i<diceCount;i++){
            totalSum+=randInt(minValue,maxValue);

        }
        return totalSum;
    }

    private:
    int randInt(int low,int high){
        return  low+rand()%(high-low+1);
    }

};

class Player{
    public:
    string id;
    int currentPosition;

    Player(string id,int pos){
        this->id=id;
        this->currentPosition=pos;
    }

};

class Game{

    public:

    Board* board;
    Dice* dice;
    deque<Player*>playerList;
    Player* winner;

    Game(){
        initialize();
    }
    
    void startGame(){

        while(winner==nullptr){

            Player* playerTurn=findPlayerTurn();
            cout<<"Player Turn:"<<playerTurn->id<<"| Current Position:"<<playerTurn->currentPosition<<endl;

            int diceNumbers=dice->rollDice();
            int newPos=playerTurn->currentPosition+diceNumbers;
            newPos=jumpCheck(newPos);

            playerTurn->currentPosition=newPos;
            cout<<"Player"<<playerTurn->id<<"Move to:"<<newPos<<endl;
            
            if(newPos>=board->cells.size()*board->cells.size()-1){
                winner=playerTurn;
            }
         }

            cout<<"Winner Is:"<<winner->id<<endl;
    }

    private:

    void initialize(){
        board=new Board(10,5,6);
        dice=new Dice(1);
        winner=nullptr;
        addPlayers();
    }

    void addPlayers(){
        Player* p1=new Player("p1",0);
        Player* p2=new Player("p2",0);
        playerList.push_back(p1);
        playerList.push_back(p2);
    }

    Player* findPlayerTurn(){
         
        Player* playerTurn=playerList.front();
        playerList.pop_front();
        playerList.push_back(playerTurn);
        return playerTurn;
    }

    int jumpCheck(int playerNewPosition){

        int size=board->cells.size();
        if(playerNewPosition>size*size-1)return playerNewPosition;
        
        Cell& cell=board->getCell(playerNewPosition);

        if(cell.jump!=nullptr && cell.jump->start==playerNewPosition){

            string jumpBy=(cell.jump->start<cell.jump->end)?"LADDER":"SNAKE";
            cout<<"Jumped by:"<<jumpBy<<endl;
            return cell.jump->end;
        }

        return playerNewPosition;
    }

};

int main(){

    srand(time(0));

    Game obj;
    obj.startGame();

    return 0;

}
