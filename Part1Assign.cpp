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

class Piece{

    // struct {
    //     string position;
    //     char rank;
    //     static int colum;
    //     string colour;
    //     string type_piece;
    // };

    public:
    string position;
    char rank;
    static int colum;
    string colour;
    string type_piece;

    string getPos(){
        return position;
    }
    string getCol(){
        return colour;
    }
    string getType(){
        return type_piece;
    }
    char getRank(){
        return rank;
    }
    int getColum(){
        return colum;
    }


};

bool my_cmp(const Piece& a, const Piece& b)
{

    
    // smallest comes first
    if(a.position.at(0) == b.position.at(0)){
        return a.position.at(1) < b.position.at(1);
    }

    return (int)a.position.at(0) < (int)b.position.at(0);
    
}

// class pieceCompare {
// public:
//     // Comparator function
//     bool operator()(Piece a,
//                     Piece b)
//     {
//         // If values are the same then
//         // return true
//         if (a.position.at(0) > b.position.at(0)) {
//             return true;
//         }
//         return false;
//     }
// };

// vector <Piece> bubble_sort(vector<Piece> vec_num){

//     Piece num;
    
//     for(int i = vec_num.size()-1; i > 0; i--){

//         for(int j = 0; j < i; j++){
            
//             int *x = vec_num[j].getColum;
//             int *y = vec_num[j+1].getColum;
//             if(x > y){
                
//                 num = vec_num[j];
//                 vec_num[j] = vec_num[j+1];
//                 vec_num[j+1] = num;

//             }

//         }

               

//     }

//     return vec_num;


// }




void output(vector<Piece> all_pieces){

    
    vector<Piece>w_pawns;
    vector<Piece>b_pawns;
    vector<Piece>w_spawns;
    vector<Piece>b_spawns;
    vector<Piece>w_giraffe;
    vector<Piece>b_giraffe;
    vector<Piece>w_monkey;
    vector<Piece>b_monkey;
    vector<Piece>w_elephant;
    vector<Piece>b_elephant;
    vector<Piece>w_lion;
    vector<Piece>b_lion;
    vector<Piece>w_crocodile;
    vector<Piece>b_crocodile;
    vector<Piece>w_zebra;
    vector<Piece>b_zebra;

    // all_pieces = bubble_sort(all_pieces);
    for(int i = 0; i < all_pieces.size(); i++){


        if(all_pieces.at(i).getType() == "pawn"){
            if((all_pieces.at(i).getCol()) == "white"){

                w_pawns.push_back(all_pieces.at(i));    

            }
            else{

                b_pawns.push_back(all_pieces.at(i));

            }
        }
        else if(all_pieces.at(i).getType() == "superpawn"){

            if((all_pieces.at(i).getCol()) == "white"){

                w_spawns.push_back(all_pieces.at(i));

            }
            else{

                b_spawns.push_back(all_pieces.at(i));

            }

        }
        else if(all_pieces.at(i).getType() == "monkey"){

            if((all_pieces.at(i).getCol()) == "white"){

                w_monkey.push_back(all_pieces.at(i));

            }
            else{

                b_monkey.push_back(all_pieces.at(i));

            }

        }
        else if(all_pieces.at(i).getType() == "giraffe"){

            if((all_pieces.at(i).getCol()) == "white"){

                w_giraffe.push_back(all_pieces.at(i));

            }
            else{

                b_giraffe.push_back(all_pieces.at(i));

            }

        }
        else if(all_pieces.at(i).getType() == "elephant"){

            if((all_pieces.at(i).getCol()) == "white"){

                w_elephant.push_back(all_pieces.at(i));
            }
            else{

                b_elephant.push_back(all_pieces.at(i));

            }
            
        }
        else if(all_pieces.at(i).getType() == "lion" ){

            if((all_pieces.at(i).getCol()) == "white"){

                w_lion.push_back(all_pieces.at(i));

            }
            else{

                b_lion.push_back(all_pieces.at(i));

            }
            
        }
        else if(all_pieces.at(i).getType() == "crocodile" ){

            if((all_pieces.at(i).getCol()) == "white"){

                w_crocodile.push_back(all_pieces.at(i));

            }
            else{

                b_crocodile.push_back(all_pieces.at(i));

            }
            
        }
        else if(all_pieces.at(i).getType() == "zebra" ){

            if((all_pieces.at(i).getCol()) == "white"){
                
                w_zebra.push_back(all_pieces.at(i));

            }
            else{

                b_zebra.push_back(all_pieces.at(i));

            }
            
        }

    }


    cout << "white pawn:";

    sort(w_pawns.begin(), w_pawns.end(), my_cmp);
    for(int i = 0; i < w_pawns.size(); i++){
        cout << " " << w_pawns.at(i).getPos();
    }

    cout << endl;
    cout << "black pawn:";

    sort(b_pawns.begin(), b_pawns.end(), my_cmp);
    for(int i = 0; i < b_pawns.size(); i++){
        cout << " " << b_pawns.at(i).getPos();
    }

    cout << endl;
    cout << "white superpawn:";

    sort(w_spawns.begin(), w_spawns.end(), my_cmp);
    for(int i = 0; i < w_spawns.size(); i++){
        cout << " " << w_spawns.at(i).getPos();
    }

    cout << endl;
    cout << "black superpawn:";

    sort(b_spawns.begin(), b_spawns.end(), my_cmp);
    for(int i = 0; i < b_spawns.size(); i++){
        cout << " " << b_spawns.at(i).getPos();
    }

    cout << endl;
    cout << "white giraffe:";

    sort(w_giraffe.begin(), w_giraffe.end(), my_cmp);
    for(int i = 0; i < w_giraffe.size(); i++){
        cout << " " << w_giraffe.at(i).getPos();
    }

    cout << endl;
    cout << "black giraffe:";

    sort(b_giraffe.begin(), b_giraffe.end(), my_cmp);
    for(int i = 0; i < b_giraffe.size(); i++){
        cout << " " << b_giraffe.at(i).getPos();
    }

    cout << endl;
    cout << "white monkey:";

    sort(w_monkey.begin(), w_monkey.end(), my_cmp);
    for(int i = 0; i < w_monkey.size(); i++){
        cout << " " << w_monkey.at(i).getPos();
    }

    cout << endl;
    cout << "black monkey:";

    sort(b_monkey.begin(), b_monkey.end(), my_cmp);
    for(int i = 0; i < b_monkey.size(); i++){
        cout << " " << b_monkey.at(i).getPos();
    }

    cout << endl;
    cout << "white elephant:";
    
    sort(w_elephant.begin(), w_elephant.end(), my_cmp);
    for(int i = 0; i < w_elephant.size(); i++){
        cout << " " << w_elephant.at(i).getPos();
    }

    cout << endl;
    cout << "black elephant:";

    sort(b_elephant.begin(), b_elephant.end(), my_cmp);
    for(int i = 0; i < b_elephant.size(); i++){
        cout << " " << b_elephant.at(i).getPos();
    }

    cout << endl;
    cout << "white lion:";

    sort(w_lion.begin(), w_lion.end(), my_cmp);
    for(int i = 0; i < w_lion.size(); i++){
        cout << " " << w_lion.at(i).getPos();
    }

    cout << endl;
    cout << "black lion:";

    sort(b_lion.begin(), b_lion.end(), my_cmp);
    for(int i = 0; i < b_lion.size(); i++){
        cout << " " << b_lion.at(i).getPos();
    }

    cout << endl;
    cout << "white crocodile:";

    sort(w_crocodile.begin(), w_crocodile.end(), my_cmp);
    for(int i = 0; i < w_crocodile.size(); i++){
        cout << " " << w_crocodile.at(i).getPos();
    }

    cout << endl;
    cout << "black crocodile:";

    sort(b_crocodile.begin(), b_crocodile.end(), my_cmp);
    for(int i = 0; i < b_crocodile.size(); i++){
        cout << " " << b_crocodile.at(i).getPos();
    }

    cout << endl;
    cout << "white zebra:";

    for(int i = 0; i < w_zebra.size(); i++){
        cout << " " << w_zebra.at(i).getPos();
    }

    cout << endl;
    cout << "black zebra:";

    for(int i = 0; i < b_zebra.size(); i++){
        cout << " " << b_zebra.at(i).getPos();
    }

} 

string whats_thepiece(char piece){


    if(piece == 'l' || piece == 'L'){
        return "lion";
    }
    else if(piece == 'p' || piece == 'P'){
        return "pawn";
    }
    else if(piece == 'm' || piece == 'M'){
        return "monkey";
    }
    else if(piece == 'e' || piece == 'E'){
        return "elephant";
    }

    else if (piece == 'c' || piece == 'C'){
        return "crocodile";
    }
    else if (piece == 'z' || piece == 'Z'){
        return "zebra";
    }
    else if(piece == 'g' || piece == 'G'){
        return "giraffe";
    }
    else if(piece == 's' || piece == 'S'){
        return "superpawn";
    }
}


vector<Piece> posi_piece(string loc_pie){

    int rank = 6;
    int num = 0;
    char col[] = {'a','b','c','d','e','f','g'};
    vector<Piece>ieces;

    for(int i = 0; i < loc_pie.size(); i++){

        if(loc_pie[i] == '/'){

            rank=rank-1;
            num = 0;
        }

        else if (isdigit(loc_pie[i]) == true){

            string c = {loc_pie[i]};
            istringstream input(c);
            int value;
            input >> value;
            num = num + value;
        }
        else{
            
            Piece p1;
            if(isupper(loc_pie[i])){
                p1.colour = "white";
                p1.type_piece = whats_thepiece(loc_pie[i]);
                string pos = {col[num]};
                // p1.colum = num;
                pos.append(to_string(rank+1));
                p1.position = pos;
                num = num +1;

            }
            else{
                p1.colour = "black";
                p1.type_piece = whats_thepiece(loc_pie[i]);
                string pos = {col[num]};
                // p1.colum = num;
                pos.append(to_string(rank+1));
                p1.position = pos;
                num = num +1;


            }
            ieces.push_back(p1);
        }
        
    }

    return(ieces);


}


int main(){

    int no_lines;
    cin >> no_lines;
    string fen_string,fen;
    vector<string> list_fen;

    for(int i = 0; i <= no_lines; i++){
        getline(cin,fen_string);
        fen = " " + fen_string;
        istringstream input(fen);
        string value;

        while(input >> value){
            list_fen.push_back(value);
        }
    }
    


    for(int i = 0; i < list_fen.size(); i = i +3){
        vector<Piece>ieces = posi_piece(list_fen.at(i));
        output(ieces);
        cout << endl;
        if(list_fen.at(i+1) == "w"){
            cout << "side to play: " << "white" << endl;
        }
        else if(list_fen.at(i+1) == "b"){
            cout << "side to play: " << "black" << endl;

        }
        cout << endl;
        ieces.clear();
        
    }
}