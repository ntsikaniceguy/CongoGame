#include <iostream>
#include<fstream>
#include <vector>
#include<queue>
#include <random>
#include <list>
#include<tuple>
#include <chrono>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include<string.h>
#include<ctype.h>
#include <algorithm>
using std::istringstream;
using namespace std::chrono;
using namespace std;

void printVector(vector<string> v){

    for(string s : v){
        cout << s << " ";
    }
    cout << endl;
}

vector<string> tokenize(string s, string del = "/"){

    vector<string> row;

    int start = 0;
    int end = s.find(del);

    while(end != -1){
        row.push_back(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
    }

    row.push_back(s.substr(start, end - start));

    return row;

}

vector<string> readline(int lineSize){
    vector<string> vec;

    for(int i = 0; i < lineSize; i++){
        string n;
        cin >> n;
        vec.push_back(n);
    }

    return vec;
}

bool isStringNumber(char c){

    if(c <'0' || c >'9'){
        return false;
    }
    
    return true; 
}

vector<vector<char>> makeBoard(vector<string> boardSetup){

    //we're gonna start from the top and work down
    int row = 6;

    //just believe in Allah!
    vector<vector<char> > board;

    while(row >= 0){

        int column = 0;

        //initialise empty row
        vector<char> temp = {'0', '0', '0', '0', '0', '0', '0'};

        string s = boardSetup.at(6 - row);

        //empty row
        if(s == "7"){
            board.push_back(temp);
        }

        //populate row
        else{

            for(char c : s){

                //these are empty spaces
                if(isStringNumber(c)){
                    int n = c - '0';
                    column += n;
                }

                else{
                    temp.at(column) = (char)c;
                    column = column + 1;
                }
            }

            board.push_back(temp);
        }

        row = row - 1;
    }

    return board;

}

pair<int, int> getPosition(vector<vector<char> > board, char piece){

    for(int row = 0; row < 7; row++){
        for(int col = 0; col < 7; col++){
            if(board.at(row).at(col) == piece){
                return make_pair(row, col); //return the coordinates wrt how we access arrays in c++
            }
        }
    }

}

vector<string> possibleLionMoves(vector<vector<char>> board, char piece){

    vector<string> column = {"a", "b", "c", "d", "e", "f,", "g"};
    vector<int> rank = {7, 6, 5, 4, 3, 2, 1};
    vector<string> possibleMoves;

    pair<int, int> position = getPosition(board, piece);

    int row = position.first;
    int col = position.second;
    string ourColour;
    string opponentColour;

    string boardPosition = column.at(col) + to_string(rank.at(row)); //this holds the position wrt how we will display it

    //cout << "Position: " + boardPosition << endl;
    //cout << "row: " << row << "\t col:" << col << endl;
    //can we move up:
    //we can only (potentially) move up if we're not on the top row already
    if(row > 0){

        //either straight up
        //then we need to check if there's a piece above us:
        if(board.at(row-1).at(col) == '0'){
           // cout << "nope! no piece here. straight above " << endl;
            //if the answer is no, we can make this move
            string up = column.at(col) + to_string(rank.at(row-1));
            string possibleMove = boardPosition + up;
            possibleMoves.push_back(possibleMove);
        }

        //else there is a piece above us
        else{
            //cout << "oops! looks like someone's already here. straight above" << endl;
            //check if the piece is the same colour or opposite colour:
            char above = board.at(row-1).at(col);
          //  cout << above << " is here: " << row-1 << " " << col << endl;

            if( (isupper(piece) && islower(above)) || (isupper(piece) && islower(above)) ){
               // cout << "this is an opp!" << endl;
                string up = column.at(col) + to_string(rank.at(row-1));
                string possibleMove = boardPosition + up;
                possibleMoves.push_back(possibleMove);
            }
        }

        //left diagonally up
        //can we even move left?
        if(col > 2){
             //check if there's a piece there:
            if(board.at(row-1).at(col-1) == '0'){
                //cout << "nope! no piece here. left diagonally up" << endl;
                //if the answer is no, we can make this move
                string upLeft = column.at(col-1) + to_string(rank.at(row-1));
                string possibleMove = boardPosition + upLeft;
                possibleMoves.push_back(possibleMove);
            }

            //there's a piece there
            else{
                //check if the piece is the same colour or opposite colour:
               // cout << "oops! looks like someone's already here. left diagonally up " << endl;
                char above = board.at(row-1).at(col-1);
               // cout << above << " is here." << row+1 << " " << col-1 << endl;

                if( (isupper(piece) && islower(above)) || (isupper(piece) && islower(above)) ){
                    //cout << "this is an opp!" << endl;
                    string upLeft = column.at(col-1) + to_string(rank.at(row-1));
                    string possibleMove = boardPosition + upLeft;
                    possibleMoves.push_back(possibleMove);
                }
            }
        }

        //right diagonally up
        //can we even move right?
        if(col < 4){
             //check if there's a piece there:
            if(board.at(row-1).at(col+1) == '0'){
                //if the answer is no, we can make this move
                //cout << "nope! no piece here. right diagonally up" << endl;
                string upRight = column.at(col+1) + to_string(rank.at(row-1));

                string possibleMove = boardPosition + upRight;
                possibleMoves.push_back(possibleMove);
            }

            //there's a piece there
            else{
                //cout << "oops! some piece already right. left diagonally up" << endl;
                //check if the piece is the same colour or opposite colour:
                char above = board.at(row-1).at(col+1);
               // cout << above << " is here." << row-1 << " " << col+1 << endl;

                if( (isupper(piece) && islower(above)) || (isupper(above) && islower(piece))){
                   // cout << "this is an opp!" << endl;
                    string upRight = column.at(col+1) + to_string(rank.at((row-1)));
                    string possibleMove = boardPosition + upRight;
                    possibleMoves.push_back(possibleMove);
                }
            }
        }
    }

    //can we move down:
    if(row < 6){

        //either straight down
        //then we need to check if there's a piece below us:
        if(board.at(row+1).at(col) == '0'){

            //cout << "nope! no piece here. straight down" << endl;
            //if the answer is no, we can make this move
            string down = column.at(col) + to_string(rank.at(row+1));
            string possibleMove = boardPosition + down;
            possibleMoves.push_back(possibleMove);
        }

        //else there is a piece below us
        else{
            //cout << "oops! some piece already here here. straight down" << endl;
            //check if the piece is the same colour or opposite colour:
            char below = board.at(row+1).at(col);

            if( (isupper(piece) && islower(below)) ||  (isupper(below) && islower(piece))){
                string down = column.at(col) + to_string(rank.at(row+1));
                string possibleMove = boardPosition + down;
                possibleMoves.push_back(possibleMove);
            }
        }

        //left diagonally down
        //can we even move left?
        if(col > 2){
             //check if there's a piece there:
            if(board.at(row+1).at(col-1) == '0'){
               // cout << "nope! no piece here. left diagonally down" << endl;
                //if the answer is no, we can make this move
                string downLeft = column.at(col-1) + to_string(rank.at((row+1)));
                string possibleMove = boardPosition + downLeft;
                possibleMoves.push_back(possibleMove);
            }

            //there's a piece there
            else{
               // cout << "oops! some piece already here. left diagonally down" << endl;
                //check if the piece is the same colour or opposite colour:
                char above = board.at(row+1).at(col-1);

                if(isupper(piece) && islower(above) || (isupper(above) && islower(piece)) ){
                    string downLeft = column.at(col-1) + to_string(rank.at(row+1));
                    string possibleMove = boardPosition + downLeft;
                    possibleMoves.push_back(possibleMove);
                }
            }
        }

        //right diagonally down
        //can we even move right?
        if(col < 4){
             //check if there's a piece there:
            if(board.at(row+1).at(col+1) == '0'){
              //  cout << "nope! no piece here. right diagonally down" << endl;
                //if the answer is no, we can make this move
                string downRight = column.at(col+1) + to_string(rank.at(row+1));
                string possibleMove = boardPosition + downRight;
                possibleMoves.push_back(possibleMove);
            }

            //there's a piece there
            else{
               // cout << "oops! piece here. right diagonally down" << endl;
                //check if the piece is the same colour or opposite colour:
                char below = board.at(row+1).at(col+1);

                if( ( isupper(piece) && islower(below) ) || (islower(piece) && isupper(below))){
                    string downRight = column.at(col+1) + to_string(rank.at(row+1));
                    string possibleMove = boardPosition + downRight;
                    possibleMoves.push_back(possibleMove);
                }
            }
        }
    }

    //can we move horizontally left?
    if(col > 2){
        //check if there's a piece there:
        if(board.at(row).at(col-1) == '0'){
            //cout << "nope! no piece here. left horizontally" << endl;
            //if the answer is no, we can move w there no problem
            
            string left = column.at(col-1) + to_string(rank.at(row));
            string possibleMove = boardPosition + left;
            possibleMoves.push_back(possibleMove);
        }

        //the position is occupied
        else{
            //cout << "oops! piece here. left horizontally" << endl;
            //check if the piece is the same colour as our piece:
            char left = board.at(row).at(col-1);
            
            if( (isupper(piece) && islower(left)) || (isupper(left) && islower(piece)) ){
                string left = column.at(col-1) + to_string(rank.at(row));
                string possibleMove = boardPosition + left;
                possibleMoves.push_back(possibleMove);
            }
        }
    }

    //can we move horizontally right?
    if(col < 4){
        //check if there's a piece there:
        if(board.at(row).at(col+1) == '0'){
            //cout << "nope! no piece here. horizontally right" << endl;
            //if the answer is no, we can move w there no problem
            string right = column.at(col+1) + to_string(rank.at(row));
            string possibleMove = boardPosition + right;
            possibleMoves.push_back(possibleMove);
        }

        //the position is occupied
        else{
            //cout << "oops! piece here. right horizontally" << endl;
            //check if the piece is the same colour as our piece:
            char right = board.at(row).at(col+1);
            
            if( (isupper(piece) && islower(right)) || (isupper(right) && islower(piece)) ){
                string right = column.at(col+1) + to_string(rank.at(row));
                string possibleMove = boardPosition + right;
                possibleMoves.push_back(possibleMove);
            }
        }
    }


    //lion to lion:
    pair<int, int> otherLionPosition;

    if(islower(piece)){
        otherLionPosition = getPosition(board, 'L');
        // cout << "other lion colour: white" << endl;
    }
    else{
        otherLionPosition = getPosition(board, 'l');
        // cout << "other lion colour: black" << endl;
    }

    int otherLionRow = otherLionPosition.first;
    int otherLionCol = otherLionPosition.second;

    string stringOtherLionPosition = column.at(col) + to_string(rank.at(otherLionRow));
    
   // if we are in the same column
    if(otherLionCol == col){

        bool canAttack = true;
        //if it's above us
        if(otherLionRow < row){
            for(int i = row-1; i > otherLionRow; i--){
                if(board.at(i).at(col) != '0'){

                 //   cout << "something's in the way above: " << board.at(i).at(col) << "at row" << i << endl; 
                    canAttack = false;
                }
            }
        }

        //if it's below us
        else{
            for(int i = row+1; i < otherLionRow; i++){
                if(board.at(i).at(col) != '0'){
                    canAttack = false;
                }
            }
        }

        if(canAttack){
            string possibleMove = boardPosition +  stringOtherLionPosition;
            possibleMoves.push_back(possibleMove);
        }

    }


   // if it's a diagonal ting going on:
   // let's say it's diagonal up 
    if(otherLionRow = row-2){
        //to the right
        if(otherLionCol + 2 == col){
            //check if anything is in the way
            if(board.at(row-1).at(col+1) == '0'){
                string possibleMove = boardPosition + stringOtherLionPosition;
                possibleMoves.push_back(possibleMove);
            }
        }

        //to the left
        if(otherLionCol - 2 == col){
            //check if anything is in the way
            if(board.at(row-1).at(col-1) == '0'){
                string possibleMove = boardPosition + stringOtherLionPosition;
                possibleMoves.push_back(possibleMove);
            }
        }
    }

   // let's say it's diagonal down 
    if(otherLionRow = row+2){
        //to the right
        if(otherLionCol + 2 == col){
            //check if anything is in the way
            if(board.at(row+1).at(col+1) == '0'){
                string possibleMove = boardPosition + stringOtherLionPosition;
                possibleMoves.push_back(possibleMove);
            }
        }

        //to the left
        if(otherLionCol - 2 == col){
            //check if anything is in the way
            if(board.at(row+1).at(col-1) == '0'){
                string possibleMove = boardPosition + stringOtherLionPosition;
                possibleMoves.push_back(possibleMove);
            }
        }
    }


    sort(possibleMoves.begin(), possibleMoves.end());

    return possibleMoves;

}

vector<string> getPossibleMoves(vector<vector<char> > board, char piece){

    if(piece == 'l' || piece == 'L'){
        return possibleLionMoves(board, piece);
    }
}

void print2DVector(vector<vector<char> > my2DArray, int height, int width){

    for (int h = 0; h < height; h++)
      {
            for (int w = 0; w < width; w++)
            {
                printf("%i ", char(my2DArray[h][w]));
            }
            printf("\n");
      }
}


int main(){

    int nLines;

    cin >> nLines;

    vector<vector<string> > allPossibleMoves;
    for(int i = 0; i < nLines; i++){
    
        //fenString vector will look something like this:
        //{2ele1z/ppppppp/7/7/7/PPP1PPP/2ELE1Z, w, 4}
        vector<string> fenString = readline(3);

        //the board is setup occording to fenstring[0] of course
        vector<string> boardSetup = tokenize(fenString.at(0), "/");

        //this creates the 2D char vector of the board
        vector<vector<char> > thisBoard = makeBoard(boardSetup);

        //this gets the colour's turn
        char l = fenString.at(1).at(0);

        if(l == 'b'){
            allPossibleMoves.push_back( possibleLionMoves(thisBoard, 'l') );
        }

        if(l == 'w'){
            allPossibleMoves.push_back( possibleLionMoves(thisBoard, 'L') );
        }
    }

    //output all the possible moves for each input
    for(vector<string> v : allPossibleMoves){
        printVector(v);
    }
}