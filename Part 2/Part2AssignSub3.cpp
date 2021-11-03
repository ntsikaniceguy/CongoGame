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

static std::string removeSpaces(std::string str)
{
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	return str;
}

vector<string> possibleElephantMoves(vector<vector<char>> board, char e, int row, int col){

    vector<string> column = {"a", "b", "c", "d", "e", "f", "g"};
    vector<int> rank = {7, 6, 5, 4, 3, 2, 1};
    vector<string> possibleMoves;

    string ourColour;
    string opponentColour;

    string boardPosition = column.at(col) + to_string(rank.at(row)); 

    //case 1: up or up up:
    if(row > 0){

        //sub case 1: up

        //check if piece is occupied:
        if(board[row-1][col] == '0'){
            //not occupied so we can move there
            string up = column[col] + to_string(rank[row-1]);
            string possibleMove = boardPosition + up;
            removeSpaces(possibleMove);
            possibleMoves.push_back(possibleMove);
        }

        else{
            //check if the piece is opponent:
            char abovePiece = board[row-1][col];

            bool ourColour = isupper(e);
            bool otherColour = isupper(abovePiece);

            if(ourColour ^ otherColour){
                //we can move there
                string up = column[col] + to_string(rank[row-1]);
                string possibleMove = boardPosition + up;
                removeSpaces(possibleMove);
                possibleMoves.push_back(possibleMove);
            }
        }

        //sub case 2: up up:
        if(row > 1){

            //check if piece is occupied:
            if(board[row-2][col] == '0'){
                //not occupied so we can move there
                string upUp = column[col] + to_string(rank[row-2]);
                string possibleMove = boardPosition + upUp;
                removeSpaces(possibleMove);
                possibleMoves.push_back(possibleMove);
            }

            else{
                //check if the piece is opponent:
                char abovePiece = board[row-2][col];

                bool ourColour = isupper(e);
                bool otherColour = isupper(abovePiece);

                if(ourColour ^ otherColour){
                    //we can move there
                    string up = column[col] + to_string(rank[row-2]);
                    string possibleMove = boardPosition + up;
                    removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }
            }
        }
    }

    //case 2: down or down down
    if(row < 6){

         //sub case 1: down

        //check if piece is occupied:
        if(board[row+1][col] == '0'){
            //not occupied so we can move there
            string up = column[col] + to_string(rank[row+1]);
            string possibleMove = boardPosition + up;
            removeSpaces(possibleMove);
            possibleMoves.push_back(possibleMove);
        }

        else{
            //check if the piece is opponent:
            char belowPiece = board[row+1][col];

            bool ourColour = isupper(e);
            bool otherColour = isupper(belowPiece);

            if(ourColour ^ otherColour){
                //we can move there
                string down = column[col] + to_string(rank[row+1]);
                string possibleMove = boardPosition + down;
                removeSpaces(possibleMove);
                possibleMoves.push_back(possibleMove);
            }
        }

        //sub case 2: down down:
        if(row < 5){

            //check if piece is occupied:
            if(board[row+2][col] == '0'){
                //not occupied so we can move there
                string downDown = column[col] + to_string(rank[row+2]);
                string possibleMove = boardPosition + downDown;
                removeSpaces(possibleMove);
                possibleMoves.push_back(possibleMove);
            }

            else{
                //check if the piece is opponent:
                char belowPiece = board[row+2][col];

                bool ourColour = isupper(e);
                bool otherColour = isupper(belowPiece);

                if(ourColour ^ otherColour){
                    //we can move there
                    string downDown = column[col] + to_string(rank[row+2]);
                    string possibleMove = boardPosition + downDown;
                    removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }
            }
        }
    }

    //case 3: right or right right:
    if(col < 6){
        //sub case 1: right

        //check if piece is occupied:
        if(board[row][col+1] == '0'){
            //not occupied so we can move there
            string right = column[col+1] + to_string(rank[row]);
            string possibleMove = boardPosition + right;
            removeSpaces(possibleMove);
            possibleMoves.push_back(possibleMove);
        }

        else{
            //check if the piece is opponent:
            char rightPiece = board[row][col+1];

            bool ourColour = isupper(e);
            bool otherColour = isupper(rightPiece);

            if(ourColour != otherColour){
                //we can move there
                string right = column[col+1] + to_string(rank[row]);
                string possibleMove = boardPosition + right;
                removeSpaces(possibleMove);
                possibleMoves.push_back(possibleMove);
            }
        }

        //sub case 2: up up:
        if(col < 5){

            //check if piece is occupied:
            if(board[row][col+2] == '0'){
                //not occupied so we can move there
                string rightRight = column[col+2] + to_string(rank[row]);
                string possibleMove = boardPosition + rightRight;
                removeSpaces(possibleMove);
                possibleMoves.push_back(possibleMove);
            }

            else{
                //check if the piece is opponent:
                char rightRightPiece = board[row][col+2];

                bool ourColour = isupper(e);
                bool otherColour = isupper(rightRightPiece);

                if(ourColour ^ otherColour){
                    //we can move there
                    string rightRight = column[col+2] + to_string(rank[row]);
                    string possibleMove = boardPosition + rightRight;
                    removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }
            }
        }
    }

    //case 4: left left:
    if(col > 0){

        //sub case 1: left

        //check if piece is occupied:
        if(board[row][col-1] == '0'){
            //not occupied so we can move there
            string left = column[col-1] + to_string(rank[row]);
            string possibleMove = boardPosition + left;
            removeSpaces(possibleMove);
            possibleMoves.push_back(possibleMove);
        }

        else{
            //check if the piece is opponent:
            char leftPiece = board[row][col-1];

            bool ourColour = isupper(e);
            bool otherColour = isupper(leftPiece);

            if(ourColour ^ otherColour){
                //we can move there
                string right = column[col-1] + to_string(rank[row]);
                string possibleMove = boardPosition + right;
                removeSpaces(possibleMove);
                possibleMoves.push_back(possibleMove);
            }
        }
        
        //sub case 2: left left:
        if(col > 1){
            //check if piece is occupied:
            if(board[row][col-2] == '0'){
                //not occupied so we can move there
                string leftLeft = column[col-2] + to_string(rank[row]);
                string possibleMove = boardPosition + leftLeft;
                removeSpaces(possibleMove);
                possibleMoves.push_back(possibleMove);
            }

            else{
                //check if the piece is opponent:
                char leftLeftPiece = board[row][col-2];

                bool ourColour = isupper(e);
                bool otherColour = isupper(leftLeftPiece);

                if(ourColour ^ otherColour){
                    //we can move there
                    string leftLeft = column[col-2] + to_string(rank[row]);
                    string possibleMove = boardPosition + leftLeft;
                    removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }
            }
        }
    }
    
    //sort(possibleMoves.begin(), possibleMoves.end());
    return possibleMoves;
}

void printVector(vector<string> v){

    if(v.size() == 0){
        return;
    }

    if(v.size() == 1){
        cout << v[0] << endl;
    }

    if(v.size() == 2){
        cout << v[0] << " " << v[1] << endl;
    }

    else if(v.size() > 2){

        cout << v[0];

        for(int i = 1; i < v.size() - 1; i++){
            cout << " " << v[i];
        }

        cout << " " << v[v.size()-1] << endl;
    }
}

void vectorToFile(vector<string> v){

    fstream myfile;
    myfile.open("Part2Sub3.txt", fstream::app);

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

vector<string> allPossibleMovesVector(vector<vector<char> > board, char piece){

    vector<string> allPossibleMoves;

    for(int row = 0; row < 7; row++){
        for(int col = 0; col < 7; col++){

            if(board[row][col] == piece){
                vector<string> theseMoves = possibleElephantMoves(board, piece, row, col);

               // printVector(theseMoves);
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

    for (int h = 0; h < height; h++)
      {
            for (int w = 0; w < width; w++)
            {  
                char c = (char)my2DArray[h][w];
                cout << c << " ";
            }
            cout << endl;
      }
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
       // print2DVector(thisBoard, 7, 7);
       // cout << endl;

        //this gets the colour's turn
        char l = fenString.at(1).at(0);
       // cout << l << endl;

        if(l == 'b'){
            vector<string> theseMoves = allPossibleMovesVector(thisBoard, 'e');
            allPossibleMoves.push_back(theseMoves);
        }

        if(l == 'w'){
           vector<string> theseMoves = allPossibleMovesVector(thisBoard, 'E');
            allPossibleMoves.push_back(theseMoves);
        }
    }

    //output all the possible moves for each input
    for(vector<string> v : allPossibleMoves){
        vectorToFile(v);
        printVector(v);
    }

    
}
