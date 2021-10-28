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

vector<int> getPosition(vector<vector<char> > board, char piece){

    vector<int> coOrdinates;
    for(int row = 0; row < 7; row++){
        for(int col = 0; col < 7; col++){
          //  cout << "row: " << row << "\t col:" << col << "\t piece: " << board[row][col] << endl;

            if(board[row][col] == piece){
                coOrdinates.push_back(row);
                coOrdinates.push_back(col);
                return coOrdinates;
            }
        }
    }

    return coOrdinates;

}

vector<string> possibleElephantMoves(vector<vector<char>> board, char z){

    vector<string> column = {"a", "b", "c", "d", "e", "f", "g"};
    vector<int> rank = {7, 6, 5, 4, 3, 2, 1};
    vector<string> possibleMoves;

    vector<int> position = getPosition(board, z);
    
    if(position.size() == 0){
        return possibleMoves;
    }


    int row = position.at(0);
    int col = position.at(1);


    string ourColour;
    string opponentColour;

    string boardPosition = column.at(col) + to_string(rank.at(row)); 

    
    

    sort(possibleMoves.begin(), possibleMoves.end());
    return possibleMoves;
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
            vector<string> zebraMoves = possibleElephantMoves(thisBoard, char(122));
           // cout << zebraMoves.size() << endl;

           // printVector(zebraMoves);
           // cout << endl;
            allPossibleMoves.push_back( zebraMoves );

        }

        if(l == 'w'){
            vector<string> zebraMoves = possibleElephantMoves(thisBoard, char(90));
            //printVector(zebraMoves);
          //  cout << endl;
            allPossibleMoves.push_back( zebraMoves );
        }
    }

    //output all the possible moves for each input
    for(vector<string> v : allPossibleMoves){
        printVector(v);
    }
}
