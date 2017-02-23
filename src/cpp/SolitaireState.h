#ifndef SolitaireState_H
#define SolitaireState_H


#include <string>
#include <vector>
#include <iostream>

using std::vector;
using std::string;
using std::cout;

class SolitaireState  {

public:

  SolitaireState(short r, short c, string st, short from = 0, short target = 0): rows(r), cols(c), state(st), from(from), target(target){};

  vector<SolitaireState> childrens() {

    vector<SolitaireState> childs;

    // loop through board
    for (short r = 0; r < rows; r++){
      for (short cd = 0; cd < cols; cd++){
        short index = r * cols + cd;

        if (state[index] == 'x'){

          short east =  (cd-2 > 0) ? index-2 : -1;
          short north = (r-2 > 0) ? ((r-2)*cols)+cd : -1;
          short west = (cd+2 < cols) ? index+2 : -1;
          short south = (r+2 < rows) ? ((r+2)*cols)+cd : -1;


          if ( east >= 0 && state[east] == 'o' && state[east+1] == 'x' && !dontGo(east)){
              childs.push_back(SolitaireState(rows, cols, swap(index, east+1, east, state), index, east ));
          }

          if ( north >= 0 && state[north] == 'o' && state[north+cols] == 'x' && !dontGo(north) ){
            childs.push_back(SolitaireState(rows, cols, swap(index, north+cols, north, state), index, north));
          }


          if ( west >= 0 && state[west] == 'o' && state[west-1] == 'x' && !dontGo(west)  ){
            childs.push_back(SolitaireState(rows, cols, swap(index, west-1, west, state), index, west));
          }

          if ( south >= 0 && state[south] == 'o' && state[south-cols] == 'x' && !dontGo(south)) {
            childs.push_back(SolitaireState(rows, cols, swap(index, south-cols, south, state), index, south));
          }

        }


      }
    }


    return childs;
  };

  bool operator==(const SolitaireState& r) {
   return state == r.state;
 };


bool dontGo(short npos){

  if(npos-1 > 0 && state[npos-1] == 'x'){
    return false;
  }

  if(npos-cols > 0 && state[npos-cols] == 'x'){
    return false;
  }

  if(npos+1 < (cols*rows) && state[npos+1] == 'x'){
    return false;
  }

  if(npos+cols < (cols*rows) && state[npos+cols] == 'x'){
    return false;
  }

  return true;
}

 void print (){

   for (int r = 0; r < rows; r++){
     for (int c = 0; c < cols; c++){
       int index = r * cols + c;
       //cout << index;
       cout << state[index];
     }

     cout << "\n";
   }

   cout << "\n";
 }

 string getTarget(){
   return std::to_string(target);
 }

 string getFrom(){
   return std::to_string(from);
 }


  string state;
private:

  short rows;
  short cols;


  short from;
  short target;

  string swap(short x, short y, short z, string &state){
    string temp = state;
    temp[x] = 'o';
    temp[y] = 'o';
    temp[z] = 'x';

    return temp;

  }

};


#endif
