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

int columnchartoint(char x){

    vector<char> column = {'a','b','c','d','e','f','g'};

    for(int i = 0; i < column.size(); i++){

        if(x == column[i]){
            return i;
        }

    }
    

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

string boardToFEN(vector<vector<char>> board){

    string FEN = "";

    for(vector<char> row : board){

        string thisRow = "";
        int col = 0;

        while(col < 7){
           // cout << "col: " << col << endl;
            if(row[col] == '0'){
                int zeros = 0;
                
                while(row[col] == '0'){
                    col = col + 1;
                    zeros++;
                }

                thisRow += to_string(zeros);
            }

            else{
                thisRow += row[col];
                col = col + 1;
            }   
        }

        FEN += thisRow + "/";
    }

   // cout << "FEN size: " << FEN.length() << endl;
    FEN.resize(FEN.size() - 1);

    return FEN;
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

string execute_moves(vector<vector<char>> &board, string move, char side){

    //Determining the Initial and Final Rows and Columns from the move string

    int column_from = columnchartoint(move.at(0));
    // cout << "Initial Conlumn: " << column_from << endl;
    // cout << move[1] << endl;
    string c = {move[1]};
    istringstream input(c);
    int row_from;
    input >> row_from;
    row_from = row_from -1;
    // cout << "Initial Row: " << row_from << endl;

    int column_to = columnchartoint(move.at(2));

   // cout << "Final Column: " << column_to << endl;
    //cout << move[3] << endl;
    string c1 = {move[3]};
    istringstream input2(c1);
    int row_to;
    input2 >> row_to;
    row_to = row_to - 1;
   // cout << "Final Row: " << row_to << endl;

    //Determining the Piece that's in the initial spot

    char piece = board[6-row_from][column_from];

    //Setting the initial spot to '0'

    // cout << "Piece: " << piece << endl;
    board[6-row_from][column_from] = '0';
   

    // print2DVector(board, 7, 7);

    //Determining Moves For White
        if(side == 'w'){

        //Determining if White Won
        if(board[6-row_to][column_to] == 'l'){

            
            for(int i = 0; i < 7; i++){

                if(board[3][i] != '0' && isupper(board[3][i])){

                    board[3][i] = '0';

                }

            }
            board[6-row_to][column_to] = piece;
            if(6-row_to == 3 && 6-row_from == 3){

                board[6-row_to][column_to] = '0';

            }
            // print2DVector(board, 7, 7);
            return("White wins");

        }
        else{

            //Executing a Non-winning move
            
            for(int i = 0; i < 7; i++){

                if((board[3][i] != '0') && isupper(board[3][i])){

                    board[3][i] = '0';

                }

            }
            board[6-row_to][column_to] = piece;
            if(6-row_to == 3 && 6-row_from == 3){

                board[6-row_to][column_to] = '0';

            }
            return("Continue");
        }

    }

    //Determining Moves For Black
    else{

        //Determining if Black Won
        if(board[6-row_to][column_to] == 'L'){


            
            for(int i = 0; i < 7; i++){

                if(board[3][i] != '0' && islower(board[3][i])){

                    board[3][i] = '0';

                }

            }
            board[6-row_to][column_to] = piece;

            if(6-row_to == 3 && 6-row_from == 3){

                board[6-row_to][column_to] = '0';

            }
            // print2DVector(board, 7, 7);
            return("Black wins");

        }
        else{

            //Executing a Non-winning move
            
            for(int i = 0; i < 7; i++){

                if((board[3][i] != '0') && islower(board[3][i])){

                    board[3][i] = '0';

                }

            }
            board[6-row_to][column_to] = piece;

            if(6-row_to == 3 && 6-row_from == 3){

                board[6-row_to][column_to] = '0';

            }

            
            return("Continue");

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

int main(){

    int nLines;

    cin >> nLines;

    vector<vector<string>> outputStrings;

    for(int i = 0; i < (nLines); i++){
    
        //fenString vector will look something like this:
        
        vector<string> fenString = readline(3); ////{2ele1z/ppppppp/7/7/7/PPP1PPP/2ELE1Z, w, 4}
        // printVector(fenString);
        // cout << endl;
        int moveNumber = stoi(fenString[2]);
        string moves;
        cin >> moves;

        //cout << moves << endl;

        //the board is setup occording to fenstring[0] of course
        vector<string> boardSetup = tokenize(fenString.at(0), "/"); //{23le1z, ppppppp, 7, 7, 7, PPP1PPP, 2ELE1z}
        // printVector(boardSetup);
        // cout << endl;

        //this creates the 2D char vector of the board
        vector<vector<char> > thisBoard = makeBoard(boardSetup);
        // cout << "Before Moving: " << endl;
        // print2DVector(thisBoard, 7, 7);
        string FEN = boardToFEN(thisBoard);
        //cout << "Initial FEN: " << FEN << endl;
        // cout << endl;

        //this gets the colour's turn
        char l = fenString.at(1).at(0);
        
        if(l == 'b'){
            vector<string> outputString;

            string game_state = execute_moves(thisBoard, moves, l);
            string thisFEN = boardToFEN(thisBoard);

            moveNumber = moveNumber + 1;
            //thisBoard is passed by referece so you can just use the thisBoard, it's already updated
            //game_state contains the set of the game after the move is made
            
           // cout << "Post Move State: " << endl;
           // print2DVector(thisBoard, 7, 7);
           outputString.push_back(thisFEN);
           outputString.push_back("w");
           outputString.push_back(to_string(moveNumber));
           outputString.push_back(game_state);

            // cout << thisFEN << " " << 'w' << " " << moveNumber << endl;
            // cout << game_state << endl;
            //cout << "Resulting FEN: " << thisFEN << " " << 'w' << " " << moveNumber << endl;
            outputStrings.push_back(outputString);

        }

        if(l == 'w'){

            vector<string> outputString;
    
            string game_state = execute_moves(thisBoard, moves,l);
            //print2DVector(thisBoard, 7, 7);

            string thisFEN = boardToFEN(thisBoard);
            outputString.push_back(thisFEN);
            outputString.push_back("b");
            outputString.push_back(to_string(moveNumber));
            outputString.push_back(game_state);
        
            //cout << thisFEN << " " << 'b' << " " << moveNumber << endl;
            //cout << game_state << endl;

            outputStrings.push_back(outputString);
        
        }
    }

    makeTextFile(outputStrings);

    for(vector<string> v : outputStrings){
        for(int i = 0; i < 3; i++){
            cout << v[i] << " ";
        }
        cout << endl;
        cout << v[3] << endl;
    }
}