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
            // cout << "row: " << row << "\t col:" << col << endl;

            if(board[row][col] == piece){
                coOrdinates.push_back(row);
                coOrdinates.push_back(col);
                return coOrdinates;
            }
        }
    }

    // pair<int, int> nullpair = make_pair(NULL, NULL);

    // return nullpair;
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

    cout << "Final Conlumn: " << column_to << endl;
    cout << move[3] << endl;
    string c1 = {move[3]};
    istringstream input2(c1);
    int row_to;
    input2 >> row_to;
    row_to = row_to - 1;
    cout << "Final Row: " << row_to << endl;

    //Determining the Piece that's in the initial spot

    char piece = board[6-row_from][column_from];

    //Setting the initial spot to '0'

    // cout << "Piece: " << piece << endl;
    board[6-row_from][column_from] = '0';
    cout << endl;

    // print2DVector(board, 7, 7);


    //Determining Moves For White
    if(side == 'w'){

        //Determining if White Won
        if(board[6-row_to][column_to] == 'l'){

            board[6-row_to][column_to] = piece;
            for(int i = 0; i < 7; i++){

                if(board[3][i] != '0' && isupper(board[3][i]) && (board[3][i] != piece)){

                    board[3][i] = '0';

                }

            }
            // print2DVector(board, 7, 7);
            return("White wins");

        }
        else{

            //Executing a Non-winning move
            board[6-row_to][column_to] = piece;
            for(int i = 0; i < 7; i++){

                if((board[3][i] != '0') && isupper(board[3][i]) && (board[3][i] != piece)){

                    board[3][i] = '0';

                }

            }
            return("Continue");
        }

    }

    //Determining Moves For Black
    else{

        //Determining if Black Won
        if(board[6-row_to][column_to] == 'L'){


            board[6-row_to][column_to] = piece;
            for(int i = 0; i < 7; i++){

                if(board[3][i] != '0' && !(isupper(board[3][i])) && (board[3][i] != piece)){

                    board[3][i] = '0';

                }

            }
            // print2DVector(board, 7, 7);
            return("Black wins");

        }
        else{

            //Executing a Non-winning move
            board[6-row_to][column_to] = piece;
            for(int i = 0; i < 7; i++){

                if((board[3][i] != '0') && !(isupper(board[3][i])) && (board[3][i] != piece)){

                    board[3][i] = '0';

                }

            }
            return("Continue");

        }

    }

    
    

    

    


}

vector<string> possibleZebraMoves(vector<vector<char>> board, char z){

    vector<string> column = {"a", "b", "c", "d", "e", "f", "g"};
    vector<int> rank = {7, 6, 5, 4, 3, 2, 1};
    vector<string> possibleMoves;

    vector<int> position = getPosition(board, z);
    // cout << position.size() << endl;

    // if(position.first == NULL && position.second == NULL){
    //     return possibleMoves;
    // }

    // cout << "this is the problem" << endl;
    int row = position.at(0);
    // cout << "or this is the problem" << endl;
    int col = position.at(1);

    // cout << "row: " << row << "\t col:" << col << endl;
    string ourColour;
    string opponentColour;

    string boardPosition = column.at(col) + to_string(rank.at(row)); 

    //case 1: up up left
    if(row > 1 && col > 0){

        //check if the piece is occupied
        if(board.at(row-2).at(col-1) == '0'){
            //if the position is empty
            string upUpLeft = column.at(col-1) + to_string(rank.at(row-2));
            string possibleMove = boardPosition + upUpLeft;
            possibleMoves.push_back(possibleMove);
        }

        //there is a piece above us
        else{
            char upUpLeftPiece = board.at(row-2).at(col-1);
           // cout << above << " is here: " << row-1 << " " << col << endl;
            bool ourColour = isupper(z);
            bool otherColour = isupper(upUpLeftPiece);
            
            if(ourColour != otherColour){
            //if( (isupper(z) && islower(upUpLeftPiece)) || (isupper(upUpLeftPiece) && islower(z)) ){
               // cout << "this is an opp!" << endl;
                string upUpLeft = column.at(col-1) + to_string(rank.at(row-2));
                string possibleMove = boardPosition + upUpLeft;
                possibleMoves.push_back(possibleMove);
            }
        }
    }

    //case 2: up, up, right:
    if(row > 1 && col < 6){

        //check if the piece is occupied
        if(board.at(row-2).at(col+1) == '0'){
            //if the position is empty
            string upUpRight = column.at(col+1) + to_string(rank.at(row-2));
            string possibleMove = boardPosition + upUpRight;
            possibleMoves.push_back(possibleMove);
        }

        //there is a piece above us
        else{
            char upUpRightPiece = board.at(row-2).at(col+1);
           // cout << above << " is here: " << row-1 << " " << col << endl;
            bool ourColour = isupper(z);
            bool otherColour = isupper(upUpRightPiece);
            
            if(ourColour != otherColour){
           // if( (isupper(z) && islower(upUpRightPiece)) || (isupper(upUpRightPiece) && islower(z)) ){
               // cout << "this is an opp!" << endl;
                string upUpRight = column.at(col+1) + to_string(rank.at(row-2));
                string possibleMove = boardPosition + upUpRight;
                possibleMoves.push_back(possibleMove);
            }
        }

    }

    //case 3: right, right, up
    if(col < 5 && row > 0){
         //check if the piece is occupied
        if(board.at(row-1).at(col+2) == '0'){
            //if the position is empty
            string rightRightUp = column.at(col+2) + to_string(rank.at(row-1));
            string possibleMove = boardPosition + rightRightUp;
            possibleMoves.push_back(possibleMove);
        }

        //there is a piece above us
        else{
            char rightRightUpPiece = board.at(row-1).at(col+2);
           // cout << above << " is here: " << row-1 << " " << col << endl;
            bool ourColour = isupper(z);
            bool otherColour = isupper(rightRightUpPiece);
            
            if(ourColour != otherColour){
           // if( (isupper(z) && islower(rightRightUpPiece)) || (isupper(rightRightUpPiece) && islower(z)) ){
               // cout << "this is an opp!" << endl;
                string rightRightUp = column.at(col+2) + to_string(rank.at(row-1));
                string possibleMove = boardPosition + rightRightUp;
                possibleMoves.push_back(possibleMove);
            }
        }
    }

    //case 4: right right down:
    if(col < 5 && row < 6){

         //check if the piece is occupied
        if(board.at(row+1).at(col+2) == '0'){
            //if the position is empty
            string rightRightDown = column.at(col+2) + to_string(rank.at(row+1));
            string possibleMove = boardPosition + rightRightDown;
            possibleMoves.push_back(possibleMove);
        }

        //there is a piece above us
        else{
            char rightRightDownPiece = board.at(row+1).at(col+2);
           // cout << above << " is here: " << row+1 << " " << col << endl;
            bool ourColour = isupper(z);
            bool otherColour = isupper(rightRightDownPiece);

            if(ourColour != otherColour){
           // if( (isupper(z) && islower(rightRightDownPiece)) || (isupper(rightRightDownPiece) && islower(z)) ){
               // cout << "this is an opp!" << endl;
                string rightRightDown = column.at(col+2) + to_string(rank.at(row+1));
                string possibleMove = boardPosition + rightRightDown;
                possibleMoves.push_back(possibleMove);
            }
        }
    } 

    //case 5: left left up:
    if(col > 1 && row > 0){
        //check if the piece is occupied
        if(board.at(row-1).at(col-2) == '0'){
            //if the position is empty
            string leftLeftUp = column.at(col-2) + to_string(rank.at(row-1));
            string possibleMove = boardPosition + leftLeftUp;
            possibleMoves.push_back(possibleMove);
        }

        //there is a piece below us
        else{
            char leftLeftUpPiece = board.at(row-1).at(col-2);
           // cout << above << " is here: " << row-1 << " " << col << endl;
            bool ourColour = isupper(z);
            bool otherColour = isupper(leftLeftUpPiece);

            if(ourColour != otherColour){
            //if( (isupper(z) && islower(leftLeftUpPiece)) || (isupper(leftLeftUpPiece) && islower(z)) ){
               // cout << "this is an opp!" << endl;
                string leftLeftUp = column.at(col-2) + to_string(rank.at(row-1));
                string possibleMove = boardPosition + leftLeftUp;
                possibleMoves.push_back(possibleMove);
            }
        }
        
    }

    //case 6: left left down:
    if(col > 1 && row < 6){
        //check if the piece is occupied
        if(board.at(row+1).at(col-2) == '0'){
            //if the position is empty
            string leftLeftDown = column.at(col-2) + to_string(rank.at(row+1));
            string possibleMove = boardPosition + leftLeftDown;
            possibleMoves.push_back(possibleMove);
        }

        //there is a piece below us
        else{
            char leftLeftDownPiece = board.at(row+1).at(col-2);
           // cout << above << " is here: " << row-1 << " " << col << endl;
            bool ourColour = isupper(z);
            bool otherColour = isupper(leftLeftDownPiece);

            if(ourColour != otherColour){

            //if( (isupper(z) && islower(leftLeftDownPiece)) || (isupper(leftLeftDownPiece) && islower(z)) ){
               // cout << "this is an opp!" << endl;
                string leftLeftUp = column.at(col-2) + to_string(rank.at(row+1));
                string possibleMove = boardPosition + leftLeftUp;
                possibleMoves.push_back(possibleMove);
            }
        }
    }

    //case 7: down down left
    if(row < 5 && col > 0){
        //check if the piece is occupied
        if(board.at(row+2).at(col-1) == '0'){
            //if the position is empty
            string downDownLeft = column.at(col-1) + to_string(rank.at(row+2));
            string possibleMove = boardPosition + downDownLeft;
            possibleMoves.push_back(possibleMove);
        }

        //there is a piece below us
        else{
            char downDownLeftPiece = board.at(row+2).at(col-1);
           // cout << above << " is here: " << row-1 << " " << col << endl;
            bool ourColour = isupper(z);
            bool otherColour = isupper(downDownLeftPiece);

           // if( (isupper(z) && islower(downDownLeftPiece)) || (isupper(downDownLeftPiece) && islower(z)) ){
               // cout << "this is an opp!" << endl;
            if(ourColour != otherColour){
                string downDownLeft = column.at(col-1) + to_string(rank.at(row+2));
                string possibleMove = boardPosition + downDownLeft;
                possibleMoves.push_back(possibleMove);
            }
        }
    }

    //case 8: down down right:
    if(row < 5 && col < 6){
        //check if the piece is occupied
        if(board.at(row+2).at(col+1) == '0'){
            //if the position is empty
            string downDownRight = column.at(col+1) + to_string(rank.at(row+2));
            string possibleMove = boardPosition + downDownRight;
            possibleMoves.push_back(possibleMove);
        }

        //there is a piece below us
        else{
            char downDownRightPiece = board.at(row+2).at(col+1);
           // cout << above << " is here: " << row-1 << " " << col << endl;
            bool ourColour = isupper(z);
            bool otherColour = isupper(downDownRightPiece);

            if( ourColour != otherColour ){
               // cout << "this is an opp!" << endl;
                string downDownRight = column.at(col+1) + to_string(rank.at(row+2));
                string possibleMove = boardPosition + downDownRight;
                possibleMoves.push_back(possibleMove);
            }
        }

    }

    sort(possibleMoves.begin(), possibleMoves.end());
    return possibleMoves;
}



int main(){

    int nLines;

    cin >> nLines;

    vector<vector<string> > allPossibleMoves;

    for(int i = 0; i < (nLines); i++){
    
        //fenString vector will look something like this:
        
        vector<string> fenString = readline(3); ////{2ele1z/ppppppp/7/7/7/PPP1PPP/2ELE1Z, w, 4}
        // printVector(fenString);
        // cout << endl;
        string moves;
        cin >> moves;

        cout << moves << endl;


        //the board is setup occording to fenstring[0] of course
        vector<string> boardSetup = tokenize(fenString.at(0), "/"); //{23le1z, ppppppp, 7, 7, 7, PPP1PPP, 2ELE1z}
        // printVector(boardSetup);
        // cout << endl;

        //this creates the 2D char vector of the board
        vector<vector<char> > thisBoard = makeBoard(boardSetup);
        print2DVector(thisBoard, 7, 7);
        cout << endl;

        //this gets the colour's turn
        char l = fenString.at(1).at(0);

        cout << l << endl;

        if(l == 'b'){
            // vector<string> zebraMoves = possibleZebraMoves(thisBoard, 'z');
            // cout << moves << endl;
            string game_state = execute_moves(thisBoard, moves,l);

            //thisBoard is passed by referece so you can just use the thisBoard, it's already updated
            //game_state contains the set of the game after the move is made

            print2DVector(thisBoard, 7, 7);
            cout << game_state << endl;
            // cout << zebraMoves.size() << endl;

            // printVector(zebraMoves);
            // cout << endl;
            // allPossibleMoves.push_back( zebraMoves );

        }

        if(l == 'w'){

            // vector<string> zebraMoves = possibleZebraMoves(thisBoard, 'Z')
            string game_state = execute_moves(thisBoard, moves,l);
            print2DVector(thisBoard, 7, 7);
            cout << game_state << endl;
            // printVector(zebraMoves);
            // cout << endl;
            // allPossibleMoves.push_back( zebraMoves );
        }
    }

    //output all the possible moves for each input
    // for(vector<string> v : allPossibleMoves){
    //     printVector(v);
    // }
}