#include <iostream>
#include<cassert>
using namespace std;

class Board{

private:

public:
  int ** board;//Board sous forme de tableau
  int boardH;//Hauteur du board
  int boardW;//Largeur du board
  int boardType;//1:circle / 2:losange /3:triangle

  Board(){}//constructeur uniquement pour la déclaration de la variable dans Tetris.hpp

  Board(int boardType, int height, int width){//constructeur principal du tableau
    this->boardType=boardType;

    switch(this->boardType){
      case 1:
        board_circle(height, width);
        break;
      case 2:
        board_losange(height,width);
        break;
      case 3:
        board_triangle(height, width);
        break;
      default:
        cout<<"ERROR in board constructor"<<endl;
    }
  }

  void board_malloc(){//alloue espace memoire pour le board en fonction de sa taille
    int i;

    this->board=(int**)malloc(this->boardH*sizeof(int*));
    assert(this->board);
    for(i=0; i<this->boardH; i++){
      this->board[i]=(int*)malloc(this->boardW*sizeof(int));
      assert(this->board[i]);
    }
  }

  void board_circle(int height, int width){//création du plateau sous la forme de cercle

    int i, j, size;

    this->boardW=width;
    this->boardH=height;
    board_malloc();
    fill_board1();

    if(this->boardW<this->boardH)
      size=this->boardW/4;
    else
      size=this->boardH/4;

    for(j=0; j<size; j++){
      for(i=0; i<size-j; i++){
        this->board[j][i]=-1;
      }
    }

    for(i=0 ; i<size; i++){
      for(j=this->boardH-1; j>this->boardH-1-size+i; j--){
        this->board[j][i]=-1;
      }
    }

    for(j=0; j<size; j++){
      for(i=this->boardW-size+j; i<this->boardW; i++){
        this->board[j][i]=-1;
      }
    }

    for(i=0; i<size; i++){
      for(j=this->boardW-1; j>this->boardW-1-size+i; j--){
        this->board[this->boardH-1-i][j]=-1;
      }
    }
  }

  void board_triangle(int height, int width){//création du plateau sous la forme de triangle

    int i, j;

    if(height%2==0)
      height--;

    if(width%2==0)
      width--;

    if(height>width/2+1){
      while(height>width/2+1){
        height--;
      }
    }

    else{
      while(width/2+1>height){
        width--;
      }
    }

    this->boardW=width;
    this->boardH=height;
    board_malloc();
    fill_board1();

    for(j=0; j<this->boardH-1; j++){
      for(i=0; i<this->boardW/2-j; i++){
        this->board[j][i]=-1;
      }
    }

    for(j=0; j<this->boardH-1; j++){
      for(i=this->boardW/2+1+j; i<this->boardW; i++){
        this->board[j][i]=-1;
      }
    }




  }

  void board_losange(int height, int width){//création du plateau sous la forme de losange

    int size, i, j;

    if(height<width)
      size=height;
    else
      size=width;

    if(size%2==0)
      size--;

    this->boardW=size;
    this->boardH=size;
    board_malloc();
    fill_board1();

    for(j=0; j<this->boardH-1; j++){
      for(i=0; i<this->boardW/2-j; i++){
        this->board[j][i]=-1;
      }
    }

    for(j=0; j<this->boardH-1; j++){
      for(i=this->boardW/2+1+j; i<this->boardW; i++){
        this->board[j][i]=-1;
      }
    }

    for(j=this->boardH/2; j<this->boardH; j++){
      for(i=0; i<j-this->boardH/2; i++){
        this->board[j][i]=-1;
      }
    }

    for(j=this->boardH-1; j>this->boardH/2; j--){
      for(i=this->boardW/2+(this->boardH-1-j)+1; i<this->boardW; i++){
        this->board[j][i]=-1;
      }
    }




  }

  void fill_board1(){

    int i, j;

    for(j=0; j<this->boardH; j++){
      for(i=0; i<this->boardW; i++){
        this->board[j][i]=0;
      }
    }
  }

  void board_display(){//affiche le plateau de jeu
    int i, j;

    for(j=0; j<this->boardH; j++){
      for(i=0; i<this->boardW; i++){
        cout<<this->board[j][i]<<"  ";
      }
      cout<<endl;
    }
  }



























};
