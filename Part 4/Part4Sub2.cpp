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
#include <set>
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

int evaluateBoard(vector<string> currentState){

    //this function takes in the current state of the board
    //outputs the value of the board according to the pieces
    //eg of currentState: vec = {"2ele1z/ppppppp/7/7/7/PPP1PPP/2ELE1Z", "w", "4"}

    string FEN = currentState[0];
    string colour = currentState[1]; //.at(0);

    vector<string> boardSetup = tokenize(FEN);
    vector<vector<char>> board = makeBoard(boardSetup);

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
    if(myMap['l'] == 0 || myMap['L'] == 0){

        //white wins
        if(myMap['l'] == 0){
            if(colour == "b"){
                return -10000;
            }
            else if(colour == "w"){
                return 10000;
            }
        }

        //black wins
        if(myMap['L'] == 0){

            if(colour == "b"){
                return 10000;
            }
            else if(colour == "w"){
                return -10000;
            }
        }
    }

    //case 3: evaluate the board:
    int blackPieces = 100*myMap['p'] + 200*myMap['e'] + 300*myMap['z'];
    int whitePieces = 100*myMap['P'] + 200*myMap['E'] + 300*myMap['Z'];

    int total = whitePieces - blackPieces;

    if(colour == "w"){
        return total;
    }

    if(colour == "b"){
        return -total;
    }
}

void makeTextFile(vector<int> output){

    fstream myfile;
    myfile.open("Part4Sub2.txt", fstream::app);

    for(int i : output){
        myfile << i << endl;
    }
}

static std::string removeSpaces(std::string str)
{
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	return str;
}

vector<string> possibleLionMoves(vector<vector<char>> board, char piece, int row, int col){

    vector<string> column = {"a", "b", "c", "d", "e", "f,", "g"};
    vector<int> rank = {7, 6, 5, 4, 3, 2, 1};
    vector<string> possibleMoves;

    string ourColour;
    string opponentColour;

    string boardPosition = column.at(col) + to_string(rank.at(row)); //this holds the position wrt how we will display it

    
    //can we move up:
    //we can only (potentially) move up if we're not on the top row already

    //black 
    if(islower(piece)){

        if(row > 0){
            //either straight up
            //then we need to check if there's a piece above us:
            if(board[row-1][col] == '0'){
            // cout << "nope! no piece here. straight above " << endl;
                //if the answer is no, we can make this move
                string up = column.at(col) + to_string(rank.at(row-1));
                string possibleMove = boardPosition + up;
                //removeSpaces(possibleMove);
                possibleMoves.push_back(possibleMove);
            }

            //else there is a piece above us
            else{
                //cout << "oops! looks like someone's already here. straight above" << endl;
                //check if the piece is the same colour or opposite colour:
                char above = board.at(row-1).at(col);

                if( isupper(above) ){
                // cout << "this is an opp!" << endl;
                    string up = column.at(col) + to_string(rank.at(row-1));
                    string possibleMove = boardPosition + up;
                    //removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }
            }

            //left diagonally up
            //can we even move left?
            if(col > 2){
                //check if there's a piece there:
                if(board[row-1][col-1] == '0'){
                    //cout << "nope! no piece here. left diagonally up" << endl;
                    //if the answer is no, we can make this move
                    string upLeft = column[col-1] + to_string(rank[row-1]);
                    string possibleMove = boardPosition + upLeft;
                    //removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }

                //there's a piece there
                else{
                    //check if the piece is the same colour or opposite colour:
                // cout << "oops! looks like someone's already here. left diagonally up " << endl;
                    char above = board[row-1][col-1];
                    

                    if( isupper(above) ){
                        //cout << "this is an opp!" << endl;
                        string upLeft = column[col-1] + to_string(rank[row-1]);
                        string possibleMove = boardPosition + upLeft;
                        //removeSpaces(possibleMove);
                        possibleMoves.push_back(possibleMove);
                    }
                }
            }

            //right diagonally up
            //can we even move right?
            if(col < 4){
                //check if there's a piece there:
                if(board[row-1][col+1] == '0'){
                    //if the answer is no, we can make this move
                    //cout << "nope! no piece here. right diagonally up" << endl;
                    string upRight = column[col+1] + to_string(rank[row-1]);

                    string possibleMove = boardPosition + upRight;
                    //removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }

                //there's a piece there
                else{
                    //cout << "oops! some piece already right. left diagonally up" << endl;
                    //check if the piece is the same colour or opposite colour:
                    char above = board[row-1][col+1];

                    if( isupper(above) ){
                    // cout << "this is an opp!" << endl;
                        string upRight = column[col+1] + to_string(rank[row-1]);
                        string possibleMove = boardPosition + upRight;
                        //removeSpaces(possibleMove);
                        possibleMoves.push_back(possibleMove);
                    }
                }
            }
        }

        //can we move down:
        if(row < 2){

            //either straight down
            //then we need to check if there's a piece below us:
            if(board[row+1][col] == '0'){

                //cout << "nope! no piece here. straight down" << endl;
                //if the answer is no, we can make this move
                string down = column[col] + to_string(rank[row+1]);
                string possibleMove = boardPosition + down;
                //removeSpaces(possibleMove);
                possibleMoves.push_back(possibleMove);
            }

            //else there is a piece below us
            else{
                //cout << "oops! some piece already here here. straight down" << endl;
                //check if the piece is the same colour or opposite colour:
                char below = board[row+1][col];

                if( isupper(below) ){
                    string down = column[col] + to_string(rank[row+1]);
                    string possibleMove = boardPosition + down;
                   // removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }
            }

            //left diagonally down
            //can we even move left?
            if(col > 2){
                //check if there's a piece there:
                if(board[row+1][col-1] == '0'){
                // cout << "nope! no piece here. left diagonally down" << endl;
                    //if the answer is no, we can make this move
                    string downLeft = column.at(col-1) + to_string(rank.at((row+1)));
                    string possibleMove = boardPosition + downLeft;
                    //removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }

                //there's a piece there
                else{
                // cout << "oops! some piece already here. left diagonally down" << endl;
                    //check if the piece is the same colour or opposite colour:
                    char above = board[row+1][col-1];
                    

                    if( isupper(above)){
                        string downLeft = column.at(col-1) + to_string(rank.at(row+1));
                        string possibleMove = boardPosition + downLeft;
                        //removeSpaces(possibleMove);
                        possibleMoves.push_back(possibleMove);
                    }
                }
            }

            //right diagonally down
            //can we even move right?
            if(col < 4){
                //check if there's a piece there:
                if(board[row+1][col+1] == '0'){
                //  cout << "nope! no piece here. right diagonally down" << endl;
                    //if the answer is no, we can make this move
                    string downRight = column[col+1] + to_string(rank[row+1]);
                    string possibleMove = boardPosition + downRight;
                    //removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }

                //there's a piece there
                else{
                // cout << "oops! piece here. right diagonally down" << endl;
                    //check if the piece is the same colour or opposite colour:
                    char below = board[row+1][col+1];
                   
                    if( isupper(below) ){
                        string downRight = column[col+1] + to_string(rank[row+1]);
                        string possibleMove = boardPosition + downRight;
                        //removeSpaces(possibleMove);
                        possibleMoves.push_back(possibleMove);
                    }
                }
            }
        }

        //can we move horizontally left?
        if(col > 2){
            //check if there's a piece there:
            if(board[row][col-1] == '0'){
                //cout << "nope! no piece here. left horizontally" << endl;
                //if the answer is no, we can move w there no problem
                
                string left = column[col-1] + to_string(rank[row]);
                string possibleMove = boardPosition + left;
                //removeSpaces(possibleMove);
                possibleMoves.push_back(possibleMove);
            }

            //the position is occupied
            else{
                //cout << "oops! piece here. left horizontally" << endl;
                //check if the piece is the same colour as our piece:
                char left = board.at(row).at(col-1);
    
                if( isupper(left) ){
                    string left = column.at(col-1) + to_string(rank.at(row));
                    string possibleMove = boardPosition + left;
                    //removeSpaces(possibleMove);
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
                //removeSpaces(possibleMove);
                possibleMoves.push_back(possibleMove);
            }

            //the position is occupied
            else{
                //cout << "oops! piece here. right horizontally" << endl;
                //check if the piece is the same colour as our piece:
                char right = board.at(row).at(col+1);
                
                //we know we're black
                if( isupper(right) ){
                    string right = column.at(col+1) + to_string(rank.at(row));
                    string possibleMove = boardPosition + right;
                    //removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }
            }

        }

        //lion to lion:
        vector<int> otherLionPosition = getPosition(board, 'L');

      //  cout << "BEFORE: \n";
        int otherLionRow = otherLionPosition[0];
        int otherLionCol = otherLionPosition[1];
     //   cout << "other lion row: " << otherLionRow <<"\t" << "other lion col: " << otherLionCol << endl;;
        

        string stringOtherLionPosition = column[otherLionCol] + to_string(rank[otherLionRow]);
     //   cout << "Other Lion Position: " << stringOtherLionPosition << endl;
        // if we are in the same column
        if(otherLionCol == col){

            bool canAttack = true;
            //if it's above us
            for(int i = row+1; i < otherLionRow; i++){
                if(board[i][col] != '0'){
                    canAttack = false;
                }
            }

            if(canAttack){
                string possibleMove = boardPosition +  stringOtherLionPosition;
               // removeSpaces(possibleMove);
                possibleMoves.push_back(possibleMove);
            }
        }

        //if it's a diagonal ting going on:
        if(otherLionRow == row+2){
            //to the right
            // cout << "AFTER: \n";
            // cout << "other lion row: " << otherLionRow <<"\t" << "other lion col: " << otherLionCol << endl;
            if(col + 2 == otherLionCol){
                //check if anything is in the way
                if(board.at(row+1).at(col+1) == '0'){
                    // cout << "This is where it's happening" << endl;
                    string possibleMove = boardPosition + stringOtherLionPosition;
                   // removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }
            }

            //to the left
            if(col - 2 == otherLionCol){
                //check if anything is in the way
                if(board.at(row+1).at(col-1) == '0'){
                    string possibleMove = boardPosition + stringOtherLionPosition;
                    //removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }
            }
        }
    }

    //else:
    else{
        //going up
        if(row > 4){
            //either straight up
            //then we need to check if there's a piece above us:
            if(board.at(row-1).at(col) == '0'){
            // cout << "nope! no piece here. straight above " << endl;
                //if the answer is no, we can make this move
                string up = column.at(col) + to_string(rank.at(row-1));
                string possibleMove = boardPosition + up;
                //removeSpaces(possibleMove);
                possibleMoves.push_back(possibleMove);
            }

            //else there is a piece above us
            else{
                //cout << "oops! looks like someone's already here. straight above" << endl;
                //check if the piece is the same colour or opposite colour:
                char above = board.at(row-1).at(col);
                
                //we know we're white
                if( islower(above) ){
                // cout << "this is an opp!" << endl;
                    string up = column.at(col) + to_string(rank.at(row-1));
                    string possibleMove = boardPosition + up;
                    //removeSpaces(possibleMove);
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
                    //removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }

                //there's a piece there
                else{
                    //check if the piece is the same colour or opposite colour:
                // cout << "oops! looks like someone's already here. left diagonally up " << endl;
                    char above = board.at(row-1).at(col-1);
                    
                    //we know we're white
                    if( islower(above) ){
                        //cout << "this is an opp!" << endl;
                        string upLeft = column.at(col-1) + to_string(rank.at(row-1));
                        string possibleMove = boardPosition + upLeft;
                        //removeSpaces(possibleMove);
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
                    //removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }

                //there's a piece there
                else{
                    //cout << "oops! some piece already right. left diagonally up" << endl;
                    //check if the piece is the same colour or opposite colour:
                    char above = board.at(row-1).at(col+1);
                    
                    //we know we're white
                    if( islower(above) ){
                    // cout << "this is an opp!" << endl;
                        string upRight = column.at(col+1) + to_string(rank.at((row-1)));
                        string possibleMove = boardPosition + upRight;
                       // removeSpaces(possibleMove);
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
                //removeSpaces(possibleMove);
                possibleMoves.push_back(possibleMove);
            }

            //else there is a piece below us
            else{
                //cout << "oops! some piece already here here. straight down" << endl;
                //check if the piece is the same colour or opposite colour:
                char below = board.at(row+1).at(col);
                

                if( islower(below) ){
                    string down = column.at(col) + to_string(rank.at(row+1));
                    string possibleMove = boardPosition + down;
                   // removeSpaces(possibleMove);
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
                    //removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }

                //there's a piece there
                else{
                // cout << "oops! some piece already here. left diagonally down" << endl;
                    //check if the piece is the same colour or opposite colour:
                    char above = board.at(row+1).at(col-1);
                    
                    //we know we are white
                    if( islower(above) ){
                        string downLeft = column.at(col-1) + to_string(rank.at(row+1));
                        string possibleMove = boardPosition + downLeft;
                        //removeSpaces(possibleMove);
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
                    //removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }

                //there's a piece there
                else{
                    // cout << "oops! piece here. right diagonally down" << endl;
                    //check if the piece is the same colour or opposite colour:
                    char below = board.at(row+1).at(col+1);
                    
                    //we know we're white
                    if( islower(below)){
                        string downRight = column.at(col+1) + to_string(rank.at(row+1));
                        string possibleMove = boardPosition + downRight;
                        //removeSpaces(possibleMove);
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
               // removeSpaces(possibleMove);
                possibleMoves.push_back(possibleMove);
            }

            //the position is occupied
            else{
                //cout << "oops! piece here. left horizontally" << endl;
                //check if the piece is the same colour as our piece:
                char left = board.at(row).at(col-1);
        
                if( islower(left) ){
                    string left = column.at(col-1) + to_string(rank.at(row));
                    string possibleMove = boardPosition + left;
                   // removeSpaces(possibleMove);
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
                //removeSpaces(possibleMove);
                possibleMoves.push_back(possibleMove);
            }

            //the position is occupied
            else{
                //cout << "oops! piece here. right horizontally" << endl;
                //check if the piece is the same colour as our piece:
                char right = board.at(row).at(col+1);
                
                if( islower(right) ){
                    string right = column.at(col+1) + to_string(rank.at(row));
                    string possibleMove = boardPosition + right;
                    //removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }
            }

        }

        //lion to lion:
        vector<int> otherLionPosition = getPosition(board, 'l');

        int otherLionRow = otherLionPosition[0];
        int otherLionCol = otherLionPosition[1];

        string stringOtherLionPosition = column.at(otherLionCol) + to_string(rank.at(otherLionRow));
       // cout << "other Lion position: " << stringOtherLionPosition << endl;

        // if we are in the same column
        if(otherLionCol == col){

            bool canAttack = true;
            //if it's above us
            for(int i = row-1; i > otherLionRow; i--){
                if(board[i][col] != '0'){
                    canAttack = false;
                }
            }

            if(canAttack){
                string possibleMove = boardPosition +  stringOtherLionPosition;
                //removeSpaces(possibleMove);
                possibleMoves.push_back(possibleMove);
            }
        }


        //if it's a diagonal ting going on:
        if(row - 2 == otherLionRow){
            //to the right
            if(col + 2 == otherLionCol){
                //check if anything is in the way
                if(board.at(row-1).at(col+1) == '0'){
                    string possibleMove = boardPosition + stringOtherLionPosition;
                    //removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }
            }

            //to the left
            if(col - 2 == otherLionCol){
                //check if anything is in the way
                if(board.at(row-1).at(col-1) == '0'){
                    string possibleMove = boardPosition + stringOtherLionPosition;
                    //removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }
            }
        }
    }

    

    //sort(possibleMoves.begin(), possibleMoves.end());

    return possibleMoves;
}

vector<string> possibleZebraMoves(vector<vector<char>> board, char z, int row, int col){

    vector<string> column = {"a", "b", "c", "d", "e", "f", "g"};
    vector<int> rank = {7, 6, 5, 4, 3, 2, 1};
    vector<string> possibleMoves;

    // vector<int> position = getPosition(board, z);
    
    // if(position.size() == 0){
    //     return possibleMoves;
    // }


    // int row = position.at(0);
    // int col = position.at(1);

  //  cout << "row: " << row << "\t col:" << col << endl;
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

    //sort(possibleMoves.begin(), possibleMoves.end());
    return possibleMoves;
}

vector<string> possibleElephantMoves(vector<vector<char>> board, char e, int row, int col){

    vector<string> column = {"a", "b", "c", "d", "e", "f", "g"};
    vector<int> rank = {7, 6, 5, 4, 3, 2, 1};
    vector<string> possibleMoves;

    string ourColour;
    string opponentColour;

    string boardPosition = column[col] + to_string(rank[row]); 

    //case 1: up or up up:
    if(row > 0){

        //sub case 1: up

        //check if piece is occupied:
        if(board[row-1][col] == '0'){
            //not occupied so we can move there
            string up = column[col] + to_string(rank[row-1]);
            string possibleMove = boardPosition + up;
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
                possibleMoves.push_back(possibleMove);
            }

            else{
                //check if the piece is opponent:
                char abovePiece = board[row-2][col];

                bool ourColour = isupper(e);
                bool otherColour = isupper(abovePiece);

                if(ourColour ^ otherColour){
                    //we can move there
                    string upUp = column[col] + to_string(rank[row-2]);
                    string possibleMove = boardPosition + upUp;
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
            string down = column[col] + to_string(rank[row+1]);
            string possibleMove = boardPosition + down;
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
            possibleMoves.push_back(possibleMove);
        }

        else{
            //check if the piece is opponent:
            char rightPiece = board[row][col+1];

            bool ourColour = isupper(e);
            bool otherColour = isupper(rightPiece);

            if(ourColour ^ otherColour){
                //we can move there
                string right = column[col+1] + to_string(rank[row]);
                string possibleMove = boardPosition + right;
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
            possibleMoves.push_back(possibleMove);
        }

        else{
            //check if the piece is opponent:
            char leftPiece = board[row][col-1];

            bool ourColour = isupper(e);
            bool otherColour = isupper(leftPiece);

            if(ourColour ^ otherColour){
                //we can move there
                string left = column[col-1] + to_string(rank[row]);
                string possibleMove = boardPosition + left;
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
                    possibleMoves.push_back(possibleMove);
                }
            }
        }
    }
    
    //sort(possibleMoves.begin(), possibleMoves.end());
    return possibleMoves;
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
    
    //sort(possibleMoves.begin(), possibleMoves.end());
    return possibleMoves;
}

void copyVector(vector<string> v1, vector<string> &v2){
    //add v1 into v2

    for(string s : v1){
        v2.push_back(s);
    }
}

//needs testing
void addVectorToSet(vector<string> v, set<string> &s){

    for(string str : v){
        s.insert(str);
    }

}

//needs testing
set<string> generateMoves(vector<vector<char>> board, string colour){
    
    //this function generates all possible moves for 
    //all the pieces on the board
    //returns a set of all possible moves

    set<string> allMoves;

    if(colour == "w"){

        for(int row = 0; row < 7; row++){
            for(int col = 0; col < 7; col++){

                if(board[row][col] == 'L'){
                    vector<string> lionMoves = possibleLionMoves(board, 'L', row, col);
                    addVectorToSet(lionMoves, allMoves);
                }

                if(board[row][col] == 'Z'){
                    vector<string> zebraMoves = possibleZebraMoves(board, 'Z', row, col);
                    addVectorToSet(zebraMoves, allMoves);
                }

                if(board[row][col] == 'E'){
                    vector<string> elephantMoves = possibleElephantMoves(board, 'E', row, col);
                    addVectorToSet(elephantMoves, allMoves);
                }

                if(board[row][col] == 'P'){
                    vector<string> pawnMoves = possiblePawnMoves(board, 'P', row, col);
                    addVectorToSet(pawnMoves, allMoves);
                }
            }
        }

        return allMoves;
    }
    
    if(colour == "b"){
        for(int row = 0; row < 7; row++){
            for(int col = 0; col < 7; col++){

                if(board[row][col] == 'l'){
                    vector<string> lionMoves = possibleLionMoves(board, 'l', row, col);
                    addVectorToSet(lionMoves, allMoves);
                }

                if(board[row][col] == 'z'){
                    vector<string> zebraMoves = possibleZebraMoves(board, 'z', row, col);
                    addVectorToSet(zebraMoves, allMoves);
                }
   
                if(board[row][col] == 'e'){
                    vector<string> elephantMoves = possibleElephantMoves(board, 'e', row, col);
                    addVectorToSet(elephantMoves, allMoves);
                }

                if(board[row][col] == 'p'){
                    vector<string> pawnMoves = possiblePawnMoves(board, 'p', row, col);
                    addVectorToSet(pawnMoves, allMoves);
                }
            }
        }

        return allMoves;

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

    FEN.resize(FEN.size() - 1);

    return FEN;
}

vector<string> makeMove(vector<vector<char>> board, vector<string> currentState, string move){

    //takes in the current state vec and a wanted move 
    //example of current state: vec = {"2ele1z/ppppppp/7/7/7/PPP1PPP/2ELE1Z", "w", "4"}
    //returns a vector<string> of the next state
    //ideal output: FENstring, the next turn's colour, the moveNumber 
    //and whether we continue.

    // map<char, int> column = {{'a', 0}, {'b', 1}, {'c', 2}, {'d', 3}, {'e', 4}, {'f', 5}, {'g', 6}}; //col['a'] == 0
    // map<char, int> rankToRow = {{'1',0}, {'2',1}, {'3',2}, {'4',3}, {'5',4}, {'6',5}, {'7',6}}; //rankToRow[1] => 0 means rank 1 = row 0

    // int col = column[ move[0] ];
    // int row = rankToRow[ move[1] ];

    // char movingPiece = board[row][col]; 

    vector<string> boardSetup = tokenize(currentState[0]);
    //vector<vector<char>> board = makeBoard(boardSetup);

    string side = currentState[1];
    int moveNumber = stoi(currentState[2]);

    int column_from = columnchartoint(move.at(0));
    // cout << "Initial Column: " << column_from << endl;
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
    if(isupper(piece)){

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
            
            vector<string> nextState;  
            string FEN = boardToFEN(board);
            string nextSide = "b";
            string stringNextMoveNumber = to_string(moveNumber);


            nextState.push_back(FEN); 
            nextState.push_back(nextSide); 
            nextState.push_back(stringNextMoveNumber);   

            return nextState;
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

            vector<string> nextState;  
            string FEN = boardToFEN(board);
            string nextSide = "b";
            string stringNextMoveNumber = to_string(moveNumber);
  

            nextState.push_back(FEN); 
            nextState.push_back(nextSide); 
            nextState.push_back(stringNextMoveNumber);   

            return nextState;
        }

    }

    //Determining Moves For Black
    if(islower(piece)){

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
            vector<string> nextState;  
            string FEN = boardToFEN(board);
            string side = "w";
            string stringNextMoveNumber = to_string(moveNumber+1);
          

            nextState.push_back(FEN); 
            nextState.push_back(side); 
            nextState.push_back(stringNextMoveNumber);   

            return nextState;

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

            vector<string> nextState;  
            string FEN = boardToFEN(board);
            string nextSide = "w";
            string stringNextMoveNumber = to_string(moveNumber+1);
         

            nextState.push_back(FEN); 
            nextState.push_back(nextSide); 
            nextState.push_back(stringNextMoveNumber);   

            return nextState;
        }
    }
    
}

int minimax(vector<string> currentState, int depth){

    //this takes in a vector of the current state
    //eg of current state: vec = {"2ele1z/ppppppp/7/7/7/PPP1PPP/2ELE1Z", "w", "4"}
    string FENstring = currentState[0];

    vector<string> boardSetup = tokenize(FENstring);
    vector<vector<char>> board = makeBoard(boardSetup);

    int boardValue = evaluateBoard(currentState);

    if(abs(boardValue) == 10000 || depth <= 0){
        // cout << "depth: " << depth << endl;
        // cout << "board value: " << boardValue << endl;
        return boardValue;
    }

    int value = -numeric_limits<int>::max();

    set<string> moves = generateMoves(board, currentState[1]);
    
    // cout << "OG Board:\n";
    // print2DVector(board, 7, 7);
    // cout << "Board evaluation: " << evaluateBoard(currentState) << endl;
    // cout << endl << endl;


    for(string move : moves){
        // cout << "current state: ";
        // printVector(currentState);

        vector<string> nextState = makeMove(board, currentState, move);

        // cout << "move: " << move << endl;
        // cout << "next state: ";
        // printVector(nextState);

        vector<string> boardSetup = tokenize(nextState[0]);
        vector<vector<char>> board = makeBoard(boardSetup);

        // cout << "Board setup after move:" << endl;    
        // print2DVector(board, 7, 7);
        
        //cout << "Board evaluation: " << evaluateBoard(nextState) << endl;

        int eval = -minimax(nextState, depth-1);

        //cout << "Minimax evaluation: " << eval << endl;
        value = max(value, eval);
        //cout << "value: " << value << endl << endl;
    }

    return value;
}

int main(){

    int nLines;

    cin >> nLines;

    vector<int> outputs;

    for(int i = 0; i < nLines; i++){
        vector<string> currentState = readline(3);
        
        //char colour = currentState[1][0];

        int value = minimax(currentState, 2);
        outputs.push_back(value);
    }

    //write outputs to text file for debugging purposes:
    makeTextFile(outputs);

    //print outputs for marker
    for(int c : outputs){
        cout << c << endl;
    }

    

    return 0;
}