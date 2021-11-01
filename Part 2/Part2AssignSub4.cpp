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
#include <cstring>
using std::istringstream;
using namespace std::chrono;
using namespace std;

void printVector(vector<string> v){

    if(v.size() == 0){
        return;
    }

    if(v.size() == 1){
        cout << v[0] << endl;
    }

    else if(v.size() > 1){

        cout << v[0];

        for(int i = 1; i< v.size() - 1; i++){
            cout << " " << v[i];
        }

        cout << " " << v[v.size()-1] << endl;
    }
}

void vectorToFile(vector<string> v){

    fstream myfile;
    myfile.open("submission4.txt", fstream::app);

    if(v.size() == 1){
        myfile << v[0] << endl;
    }

    if(v.size() == 2){
        myfile << v[0] << " " << v[1] << endl;
    }

    else if(v.size() > 2){

        myfile << v[0];

        for(int i = 1; i < v.size() - 1; i++){
            myfile << " " << v[i];
        }
        
        myfile << " " << v[v.size()-1] << endl;
    }

    myfile.close();
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

vector<string> possiblePawnMoves(vector<vector<char>> board, char e, int row, int col){

    vector<string> column = {"a", "b", "c", "d", "e", "f", "g"};
    vector<int> rank = {7, 6, 5, 4, 3, 2, 1};
    vector<string> possibleMoves;

    string ourColour;
    string opponentColour;

    string boardPosition = column.at(col) + to_string(rank.at(row)); 

    //if we're white
    if( isupper(e) ){
    
        if(row > 0){
            //case1: straight up
            //check if piece is occupied
            if(board[row-1][col] == '0'){
                //not occupied so we can move there
                string up = column[col] + to_string(rank[row-1]);
                string possibleMove = boardPosition + up;
                possibleMoves.push_back(possibleMove);
            }

            //the piece is occupied
            else{
                //we already know that we're upper
                if( islower(board[row-1][col]) ){
                    string up = column[col] + to_string(rank[row-1]);
                    string possibleMove = boardPosition + up;
                    possibleMoves.push_back(possibleMove);
                }
            }

            //case 2: up right:
            if(col < 6){
                
                if(board[row-1][col+1] == '0'){
                    //not occupied so we can move there
                    string upRight = column[col+1] + to_string(rank[row-1]);
                    string possibleMove = boardPosition + upRight;
                    possibleMoves.push_back(possibleMove);
                }

                //the piece is occupied
                else{
                    //we already know that we're upper
                    if( islower(board[row-1][col+1]) ){
                        string upRight = column[col+1] + to_string(rank[row-1]);
                        string possibleMove = boardPosition + upRight;
                        possibleMoves.push_back(possibleMove);
                    }
                }
            }

            //case 3: up left
            if(col > 0){

                if(board[row-1][col-1] == '0'){
                    //not occupied so we can move there
                    string upLeft = column[col-1] + to_string(rank[row-1]);
                    string possibleMove = boardPosition + upLeft;
                    possibleMoves.push_back(possibleMove);
                }

                //the piece is occupied
                else{
                    //we already know that we're upper
                    if( islower(board[row-1][col-1]) ){
                        string upLeft = column[col-1] + to_string(rank[row-1]);
                        string possibleMove = boardPosition + upLeft;
                        possibleMoves.push_back(possibleMove);
                    }
                }
            }

        }

        //moving down or down down
        if(row < 3){
            //down
            //check if piece is occupied
            if(board[row+1][col] == '0'){
                //not occupied so we can move there:
                string down = column[col] + to_string(rank[row+1]);
                string possibleMove = boardPosition + down;
                possibleMoves.push_back(possibleMove);

                //down down
                //check if piece is occupied
                if(board[row+2][col] == '0'){
                    string downDown = column[col] + to_string(rank[row+2]);
                    string possibleMove = boardPosition + downDown;
                    possibleMoves.push_back(possibleMove);
                }
            }
        }
    }
        
    //we're black
    else{

        if(row < 6){
            //case1: straight down
            //check if piece is occupied
            if(board[row+1][col] == '0'){
                //not occupied so we can move there
                string down = column[col] + to_string(rank[row+1]);
                string possibleMove = boardPosition + down;
                possibleMoves.push_back(possibleMove);
            }

            //the piece is occupied
            else{
                //we already know that we're lower
                if( !islower(board[row+1][col]) ){
                    string down = column[col] + to_string(rank[row+1]);
                    string possibleMove = boardPosition + down;
                    possibleMoves.push_back(possibleMove);
                }
            }

            //case 2: down right:
            if(col < 6){
                
                if(board[row+1][col+1] == '0'){
                    //not occupied so we can move there
                    string downRight = column[col+1] + to_string(rank[row+1]);
                    string possibleMove = boardPosition + downRight;
                    possibleMoves.push_back(possibleMove);
                }

                //the piece is occupied
                else{
                    //we already know that we're lower
                    if( !islower(board[row+1][col+1]) ){
                        string downRight = column[col+1] + to_string(rank[row+1]);
                        string possibleMove = boardPosition + downRight;
                        possibleMoves.push_back(possibleMove);
                    }
                }
            }

            //case 3: down left
            if(col > 0){

                if(board[row+1][col-1] == '0'){
                    //not occupied so we can move there
                    string downLeft = column[col-1] + to_string(rank[row+1]);
                    string possibleMove = boardPosition + downLeft;
                    possibleMoves.push_back(possibleMove);
                }

                //the piece is occupied
                else{
                    //we already know that we're lower
                    if( !islower(board[row+1][col-1]) ){
                        string downLeft = column[col-1] + to_string(rank[row+1]);
                        string possibleMove = boardPosition + downLeft;
                        possibleMoves.push_back(possibleMove);
                    }
                }
            }

        }

        //moving down or down down
        if(row > 3){
            //down
            //check if piece is occupied
            if(board[row-1][col] == '0'){
                //not occupied so we can move there:
                string up = column[col] + to_string(rank[row-1]);
                string possibleMove = boardPosition + up;
                possibleMoves.push_back(possibleMove);

                //down down
                //check if piece is occupied
                if(board[row-2][col] == '0'){
                    string upUp = column[col] + to_string(rank[row-2]);
                    string possibleMove = boardPosition + upUp;
                    possibleMoves.push_back(possibleMove);
                }
            }
        }
    }
    
    sort(possibleMoves.begin(), possibleMoves.end());
    return possibleMoves;
}

vector<string> allPossibleMovesVector(vector<vector<char> > board, char piece){

    vector<string> allPossibleMoves;

    for(int row = 0; row < 7; row++){
        for(int col = 0; col < 7; col++){

            if(board[row][col] == piece){
                vector<string> theseMoves = possiblePawnMoves(board, piece, row, col);

                //printVector(theseMoves);
                for(string s : theseMoves){
                    allPossibleMoves.push_back(s);
                }
            }
        }
    }

    sort(allPossibleMoves.begin(), allPossibleMoves.end());
    return allPossibleMoves;

}

void print2DVector(vector<vector<char> > my2DArray, int height, int width){

    vector<int> rank = {7, 6, 5, 4, 3, 2, 1};
    vector<char> column = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};

    for (int h = 0; h < height; h++)
        
      {
            cout << rank[h] << " ";
            for (int w = 0; w < width; w++)
            {  
                char c = (char)my2DArray[h][w];
                cout << c << " ";
            }
            cout << endl;
      }
    
    cout << "  ";
    for(char c : column){
        cout << c << " ";
    }

    cout << endl;
}

int main(){

    int nLines;

    cin >> nLines;

    vector<vector<string> > allPossibleMoves;

    for(int i = 0; i < nLines; i++){
    
        //fenString vector will look something like this:
        
        vector<string> fenString = readline(3); ////{2ele1z/ppppppp/7/7/7/PPP1PPP/2ELE1Z, w, 4}
        //printVector(fenString);
        //cout << endl;

        //the board is setup occording to fenstring[0] of course
        vector<string> boardSetup = tokenize(fenString.at(0), "/"); //{23le1z, ppppppp, 7, 7, 7, PPP1PPP, 2ELE1z}
       // printVector(boardSetup);
        //cout << endl;

        //this creates the 2D char vector of the board
        vector<vector<char> > thisBoard = makeBoard(boardSetup);
        print2DVector(thisBoard, 7, 7);
        // cout << endl;

        //this gets the colour's turn
        char l = fenString.at(1).at(0);
       // cout << l << endl;

        if(l == 'b'){
            vector<string> theseMoves = allPossibleMovesVector(thisBoard, 'p');
            allPossibleMoves.push_back(theseMoves);
        }

        if(l == 'w'){
           vector<string> theseMoves = allPossibleMovesVector(thisBoard, 'P');
            allPossibleMoves.push_back(theseMoves);
        }
    }
 
    //output all the possible moves for each input
    for(vector<string> v : allPossibleMoves){
        vectorToFile(v);
        printVector(v);
    }

     
}