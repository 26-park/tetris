#include "game.h"
#include "console/console.h"
#include <ctime>
#include <iostream>
#include <array>
#include <chrono>
#include <thread>
#include <windows.h>

Game::Game(){
    
    tx=3;
    ty=0;
    leftLine=1;
    start = std::chrono::steady_clock::now();
    mainT=arr[ rand()%8];
    nextT=arr[ rand()%8];
    hold = false;
    holdcount=0;
    resultw=false;
    resultl=false;
    for (int i = 1; i < BOARD_HEIGHT; i++)
    {
        for (int j = 1; j <= BOARD_WIDTH; j++)
        {
            if (i==BOARD_HEIGHT-1)
            {
                board_[i][j]=true;
            }else{
                board_[i][j]=false;
            }
            
            
            
            
        }
        
    }
    
    
    
}
void Game::timePrint(){
    
        console::draw(1,BOARD_HEIGHT,"");
        // 현재 시간 기록
        auto end = std::chrono::steady_clock::now();

        // 경과 시간 계산
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

        // 시, 분, 초 계산
        
        int minutes = (elapsed % 3600) / 60;
        int seconds = (elapsed % 3600) % 60;
        int tenths = (elapsed % 1000) / 10;

        
       
        std::string time = "";
        
        time += (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":"; // 분
        time += (seconds < 10 ? "0" : "") + std::to_string(seconds) + "."; // 초
        time += (tenths < 10 ? "0" : "") + std::to_string(tenths); // 밀리초
        
        
        
        
        console::draw(1,BOARD_HEIGHT+1,time);
       
        
    
}
void Game::handleInput() {
    if(console::key(console::K_ESC)){
        exit(1);
    }
  
    if (console::key(console::K_LEFT)){
        bool flag=true;
        for (int i = 0; i < 4; i++) {
            for(int j =0;j<4;j++){
                if (mainT.check(i, j) && tx+j <= 1) { 
                flag=false;
            }
            }
            
            
        }
        if (flag)
        {
            tx--;
        }
        

      
      
    }
    if (console::key(console::K_RIGHT)){
        bool flag=true;
        for (int i = 0; i < 4; i++) {
            for(int j =0;j<4;j++){
                if (mainT.check(i, j) && tx+j >= BOARD_WIDTH ) { // 오른쪽 경계에 닿음
                flag=false;
            }


            }
            
            
        }
        if (flag)
        {
            tx++;
        }
      
      
      
      
      
    }
    if (console::key(console::K_UP)){
        
        
        while (!Game::contact(shadowT,ty,tx))
        {
            ty++;
        }
        
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (mainT.check(i,j))
                {
                    
                    board_[i+ty][j+tx]==true;
                }
            }
            
        }

      
    }
    if (console::key(console::K_DOWN)){
      
      
      if (!Game::contact(mainT,ty,tx))
      {
        ty++;
      }
      
    }

 
    if (console::key(console::K_SPACE)) {
        
        
        if (hold==false) //첫교환
        {
            holdT=*mainT.original();
            mainT=nextT;
            nextT=arr[rand()%8];
            hold=true;
        }else{    //이후교환
            if (holdcount<1)
            {
                Tetromino* t;
                t=mainT.original();
                mainT=holdT;
                holdT=*t;
            
            }
            
            
        }
        
        
        
        holdcount++;


    
    }
    if (console::key(console::K_Z)) {
        
        if (tx<=1)
        {
            tx=1;
        }
        if (tx>=BOARD_WIDTH-2)
        {
            tx=BOARD_WIDTH-3;
        }
        
        
        mainT=mainT.rotatedCCW();
        
    }
    if (console::key(console::K_X)) {
        if (tx<=1)
        {
            tx=1;
        }
        if (tx>=BOARD_WIDTH-2)
        {
            tx=BOARD_WIDTH-3;
        }
        
        mainT=mainT.rotatedCW();
        
        
    }
    if (console::key(console::K_ENTER)) {
        
    }if (console::key(console::K_NONE)) {
        
    }
    if (console::key(console::K_OTHER)) {
        
    }
  
    
    
    
  
  
}
bool Game::contact(Tetromino t,int y,int x){
    bool con = false;
    for (int i = 0; i < 4; i++){
        for (int j= 0; j < 4; j++)
        {
               
            
            

            if(t.check(i,j) && board_[i+y+1][j+x]&& !t.check(i+1,j)){
                con=true;
                    
                return con;

            }
            if (t.check(i,j) && i+1+y==BOARD_HEIGHT-1)
            {
                con=true;
                    
                return con;
            }
                 


        }
            
    }
    return con;
}
void Game::lineCheck(){
    for (int i = 1; i < BOARD_HEIGHT-1; i++)
    {
        bool check=true;
        for(int j = 1 ;j <= BOARD_WIDTH; j++){
            if(board_[i][j]==false){
                check=false;
            }
            
        }
        
        if (check)
        {
            leftLine--;
            for (int k = 1; k <= BOARD_WIDTH; k++)//한줄 지우기
            {
                board_[i][k]=false;
            }
            
            for (int q = i-1; q >=1; q--)
            {
                for(int w = 1 ;w <= BOARD_WIDTH; w++){
                    if (board_[q][w]==true)
                    {
                        board_[q+1][w]=true;
                        board_[q][w]=false;
                    }
                    

                }
                

            
            }
        
        }
    
    }
    if (leftLine<=0)
    {
        leftLine=0;
    }
    
}
void Game::update(){
    
    
    clock_t startTime = clock();

    timePrint();
    if (resultl || resultw)
    {
        exit(0);
        
        
    }
    
    

    if (Game::contact(mainT,ty,tx))
    {
        holdcount=0;
        for (int i = 0; i < 4; i++){
            for (int j= 0; j < 4; j++)
            {
                if (mainT.check(i, j)) {
                    board_[i + ty][j + tx] = true;
                }

                
                


            }
            
        }
        
        tx=3;
        ty=1;
        mainT=nextT;
        nextT=arr[rand()%8];
        Game::lineCheck();
    }
    //초기화
    
        for (int i = 0; i < 4; i++){
            for (int j= 0; j < 4; j++)
            {
                if (mainT.check(i,j))
                {
                    board_[i+ty][j+tx]=false;
                }
                
                


            }
            
        }
    if (ty==1)
    {
        bool flag = false;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if(mainT.check(i,j) && board_[i+1+ty][j+tx]){
                    flag=true;
                }
            }
        }
        if (flag)
        {
            for (int k = 1; k <= BOARD_WIDTH; k++)
            {
                board_[BOARD_HEIGHT/2][k]=false;
            }
            resultl=true;
            
           
        }
        
        
    }
    if(leftLine<=0){
        
    
        
        
        resultw=true;
           
        
        
    
    }
    

    if (!Game::contact(mainT,ty,tx))
    {
        ty++;
    }
    
    
    
    handleInput();
    
    
    
    

    




    
    
    
    
    clock_t endTime = clock();
    float elapsedTime = static_cast<float>((endTime - startTime) * 1000 / CLOCKS_PER_SEC);
    float remainingTime = DROP_DELAY/60.0*1000.0 - elapsedTime;

    clock_t waitStartTime = clock();
    while ((clock() - waitStartTime) * 1000.0 / CLOCKS_PER_SEC < remainingTime) {
        // 대기
    }


    
    

}

    
   
       
    
    
    
    
    
    
    
    
    


void Game::draw(){
    
    
    console::drawBox(0,0,BOARD_WIDTH+1,BOARD_HEIGHT-1);
    console::drawBox(BOARD_WIDTH+2,0,BOARD_WIDTH+7,7);
    console::drawBox(BOARD_WIDTH+8,0,BOARD_WIDTH+13,7);
    console::draw(BOARD_WIDTH+3,0,"NEXT");
    console::draw(BOARD_WIDTH+9,0,"HOLD");
    

    
    
    
    for (int i = 0; i < 4; i++){
        for (int j= 0; j < 4; j++){
            if (mainT.check(i,j))
            {
                board_[i+ty][j+tx]=true;
            }
            
            


        }
            
    }


    //쉐도우
    shadowT=mainT;
    int sy=ty;
    int sx=tx;
    while (!Game::contact(shadowT,sy,sx))
    {
        sy++;
    }
    
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (shadowT.check(i,j))
            {
                console::draw(sx+j,sy+i,SHADOW_STRING);
            }
        }
        
    }


    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (nextT.check(i,j))
            {
                console::draw(BOARD_WIDTH+3+j,i+3,BLOCK_STRING);
            }
        }
        
    }
    if (hold==true)
    {
    
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (holdT.check(i,j))
            {
                console::draw(BOARD_WIDTH+9+j,i+3,BLOCK_STRING);
            }
        }
        
    }
    }
    
    
    
    for (int i = 1; i < BOARD_HEIGHT-1; i++)
    {
        for (int j = 1; j <= BOARD_WIDTH; j++)
        {
            if (board_[i][j])
            {
                console::draw(j,i,BLOCK_STRING);
            }
            
            
        }
        
    }
    
    std::string line = std::to_string(leftLine);
    line+=" lines left";
    console::draw(1,BOARD_HEIGHT,line);
    
    if (resultw)
    {
        
        console::draw(BOARD_WIDTH/4,BOARD_HEIGHT/2,"You Win");
        
    }if (resultl)
    {
        console::draw(BOARD_WIDTH/4,BOARD_HEIGHT/2,"You lose");
        
    }
    
    
    

    
}

bool Game::shouldExit(){


}

