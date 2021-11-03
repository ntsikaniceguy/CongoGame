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
#include <map>
using std::istringstream;
using namespace std::chrono;
using namespace std;

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

    vector<int> coordinates;
    for(int row = 0; row < 7; row++){
        for(int col = 0; col < 7; col++){
            // cout << "row: " << row << "\t col:" << col << endl;

            if(board[row][col] == piece){
                coordinates.push_back(row);
                coordinates.push_back(col);
                return coordinates;
            }
        }
    }
}

void makeTextFile(vector<vector<string>> outputStrings){

    fstream myfile;
    myfile.open("Part3.txt", fstream::app);

    for(vector<string> v : outputStrings){

        for(int i = 0; i < 3; i++){
            myfile << v[i] << " ";
        }

        myfile << endl;
        myfile << v[3] << endl;
    }
}

int evaluateBoard(vector<vector<char>> board, char colour){

    map<char, int> myMap;
    
    //Lions
    myMap.insert(pair<char, int>('L', 0));
    myMap.insert(pair<char, int>('l', 0));

    //pawns
    myMap.insert(pair<char, int>('p', 0));
    myMap.insert(pair<char, int>('P', 0));    

    //elephants
    myMap.insert(pair<char, int>('e', 0));
    myMap.insert(pair<char, int>('E', 0));

    //zebras
    myMap.insert(pair<char, int>('z', 0));
    myMap.insert(pair<char, int>('Z', 0));


    for(int row = 0; row < 7; row++){
        for(int col = 0; col < 7; col++){

            if(board[row][col] == 'L'){
                myMap['L']++;
            }

            if(board[row][col] == 'l'){
               myMap['l']++;
            }

            if(board[row][col] == 'p'){
                myMap['p']++;
            }

            if(board[row][col] == 'P'){
                myMap['P']++;
            }

            if(board[row][col] == 'z'){
               myMap['z']++;
            }

            if(board[row][col] == 'Z'){
                myMap['Z']++;
            }

            if(board[row][col] == 'e'){
                myMap['e']++;
            }

            if(board[row][col] == 'E'){
                myMap['E']++;
            }
        }
    }

    //case 1: draw
    if(myMap['L'] == 1 && myMap['l'] == 1){

        bool noOtherPieces = true;

        for (auto& kv : myMap) {
            
            if(kv.first == 'L' || kv.first == 'l'){
                continue;
            }

            if(kv.second != 0){
                noOtherPieces = false;
            }
        }

        if(noOtherPieces){
            return 0;
        }
    }

    //case 2: black or white wins:
    if(myMap['l'] == 0 ^ myMap['L'] == 0){

        //white wins
        if(myMap['l'] == 0){
            if(colour == 'b'){
                return -10000;
            }
            else if(colour == 'w'){
                return 10000;
            }
        }

        //black wins
        if(myMap['L'] == 0){

            if(colour == 'b'){
                return 10000;
            }
            else if(colour == 'w'){
                return -10000;
            }
        }
    }
    //case 3: evaluate the board:
    int blackPieces = 100*myMap['p'] + 200*myMap['e'] + 300*myMap['z'];
    int whitePieces = 100*myMap['P'] + 200*myMap['E'] + 300*myMap['Z'];
    

    int total = whitePieces - blackPieces;

    if(colour == 'w'){
        return total;
    }

    if(colour == 'b'){
        return -total;
    }
    
}

void makeTextFile(vector<int> output){

    fstream myfile;
    myfile.open("Part4.txt", fstream::app);

    for(int i : output){
        myfile << i << endl;
    }
}


int main(){

    int nLines;

    cin >> nLines;

    vector<int> outputs;
    for(int i = 0; i < (nLines); i++){
        vector<string> fenString = readline(3);
        vector<string> boardSetup = tokenize(fenString.at(0), "/"); //{23le1z, ppppppp, 7, 7, 7, PPP1PPP, 2ELE1z}
        // printVector(boardSetup);
        // cout << endl;
        char colour = fenString[1][0];

        //this creates the 2D char vector of the board
        vector<vector<char> > thisBoard = makeBoard(boardSetup);
        int boardValue = evaluateBoard(thisBoard, colour);
        outputs.push_back(boardValue);
    }

    makeTextFile(outputs);

    for(int c : outputs){
        cout << c << endl;
    }

    return 0;
}