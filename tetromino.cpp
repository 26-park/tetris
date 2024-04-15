#include <iostream>
#include "tetromino.h"
#include <string>


  Tetromino::Tetromino() {}
  // Tetromino I("I", 4, "XXXXOOOOXXXXXXXX")
  Tetromino::Tetromino(std::string name, int size, std::string shape){
    
    this->original_=this;
    if (shape.length()==16)
    {
      int p=0;
      for (int i = 0; i < 4; i++)
      {
        for (int j = 0; j < 4; j++)
        {
          if (shape.at(p)=='O')
          {
            shape_[i][j]=true;
          }else{
            shape_[i][j]=false;
          }
          p++;
        }
        
      }
      
    }else if (shape.length()==4)
    {
      int p=0;
      for (int i = 0; i < 2; i++)
      {
        for (int j = 0; j < 2; j++)
        {
          if (shape.at(p)=='O')
          {
            shape_[i][j]=true;
          }else{
            shape_[i][j]=false;
          }
          p++;
        }
        
      }
    }else{
      int p=0;
      for (int i = 0; i < 3; i++)
      {
        for (int j = 0; j < 3; j++)
        {
          if (shape.at(p)=='O')
          {
            shape_[i][j]=true;
          }else{
            shape_[i][j]=false;
          }
          p++;
        }
        
      }

    }
    
    


  }
  // 시계 방향으로 회전한 모습의 테트로미노 객체를 반환한다.
  Tetromino Tetromino::rotatedCW(){
    bool temp[4][4];
    
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            temp[i][j]=shape_[4-j-1][i];
            
        }
        
    }
    std::string s="";
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
           if (temp[i][j]==true)
           {
            s+="O";
           }else{
            s+="X";
           }
        }
        
    }
    Tetromino t(name(),size(),s);
    t.original_=this->original_;
   //새로운 테트로미노 반환해야함 original에 원래 객체가 들어있음
   
    return t;
  }

  // 반시계 방향으로 회전한 모습의 테트로미노 객체를 반환한다.
  Tetromino Tetromino::rotatedCCW(){
    bool temp[4][4];
    
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            temp[i][j]=shape_[j][3-i];
        }
        
    }
    std::string s="";
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
           if (temp[i][j]==true)
           {
            s+="O";
           }else{
            s+="X";
           }
           
           
        }
        
    }
    Tetromino t(name(),size(),s);
    t.original_=this->original_;
   //새로운 테트로미노 반환해야함 original에 원래 객체가 들어있음
   
    return t;
    
    

  }

  // 화면의 x, y 위치에 s 문자열로  테트로미노를 그린다
  void Tetromino::drawAt(std::string s, int x, int y){



  }
Tetromino Tetromino::I("I", 4, "XXXXOOOOXXXXXXXX");
Tetromino Tetromino::O("O", 2, "OOOO");
Tetromino Tetromino::T("T", 3, "XOXOOOXXX");
Tetromino Tetromino::S("S", 3, "XOOOOXXXX");
Tetromino Tetromino::Z("Z", 3, "OOXXOOXXX");
Tetromino Tetromino::J("J", 3, "OXXOOOXXX");
Tetromino Tetromino::L("L", 3, "XXOOOOXXX");


  
  

 



