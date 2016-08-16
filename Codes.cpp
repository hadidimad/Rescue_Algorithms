#include<iostream>
#include<conio.h>
#include<graphics.h>
using namespace std;
#define Max_X 12
#define Max_Y 12
 struct ROBOT{
 int x;
 int y;
 int Gy;
 int d;
 int LinterLabel;
}robot;
 struct Start{
 int x;
 int y;
}start;
struct MOUSE{
 long x;
 long y;       
}mouse;
 int moveD;
struct MAZE{
 bool wall_U;
 bool wall_D;
 bool wall_R;
 bool wall_L;   
} maze[Max_X][Max_Y]; 
struct FMAZE{
 bool wall_U;
 bool wall_D;
 bool wall_R;
 bool wall_L;   
 signed int score;  
 bool visited;       
}fmaze[Max_X][Max_Y];
#define MaxInters 100
struct Intersection{
 bool upVisited;
 bool rightVisited;
 bool leftVisited;
 bool downVisited;       
 int LastIntDir;
 signed int x;
 signed int y;
 int LTLabel;           
}inter[MaxInters];
struct Walls{
 bool u;
 bool r;
 bool l;
 bool d;
}walls;



signed long input=0;
bool mazechanged=1;
bool robotmoved=1;
bool gotoedit=1;
void cleartextScreen()
{
     cout<<"                                                                                  \n";  
     cout<<"                                                                                  \n";
     cout<<"                                                                                  \n";
     cout<<"                                                                                  \n";
     cout<<"                                                                                  \n";
     cout<<"                                                                                  \n";
     cout<<"                                                                                  \n";
     cout<<"                                                                                  \n";
     cout<<"                                                                                  \n";
     cout<<"                                                                                  \n";
     cout<<"                                                                                  \n";
     cout<<"                                                                                  \n";
     cout<<"                                                                                  \n";
     cout<<"                                                                                  \n";
     cout<<"                                                                                  \n";
     cout<<"                                                                                  \n";
     cout<<"                                                                                  \n";
     cout<<"                                                                                  \n";  
     cout<<"                                                                                  \n";
     cout<<"                                                                                  \n";
     cout<<"                                                                                  \n";
     cout<<"                                                                                  \n";
     cout<<"                                                                                  \n";
     cout<<"                                                                                  \n";
     cout<<"                                                                                  \n";
     cout<<"                                                                                  \n";
     cout<<"                                                                                  \n";
     cout<<"                                                                                  \n";
     cout<<"                                                                                  \n";
     cout<<"                                                                                  \n";
     cout<<"                                                                                  \n";
     cout<<"                                                                                  \n";
     cout<<"                                                                                  \n";
     cout<<"                                                                                  \n";
     
}
      
void DrawMaze(int dx,int dy)
{
    if(maze[dx][dy].wall_D)
    {
            setcolor(15);
            line(((dx+1)*60),((dy+1)*60),((dx+1)*60)-60,((dy+1)*60));                          
    } 
     if(maze[dx][dy].wall_L)
    {
            setcolor(15);
            line(((dx+1)*60)-60,((dy+1)*60)-60,((dx+1)*60)-60,((dy+1)*60));                          
    } 
    if(maze[dx][dy].wall_R)
    {
            setcolor(15);
            line(((dx+1)*60),((dy+1)*60)-60,((dx+1)*60),((dy+1)*60));                        
    }
    if(maze[dx][dy].wall_U)
    {
           setcolor(15);
           line(((dx+1)*60)-60,((dy+1)*60)-60,((dx+1)*60),((dy+1)*60)-60);                         
    }   
    if(!maze[dx][dy].wall_D)
    {
            setcolor(COLOR(0,100,0));
            line(((dx+1)*60),((dy+1)*60),((dx+1)*60)-60,((dy+1)*60));                          
    } 
     if(!maze[dx][dy].wall_L)
    {
            setcolor(COLOR(0,100,0));
            line(((dx+1)*60)-60,((dy+1)*60)-60,((dx+1)*60)-60,((dy+1)*60));                          
    } 
    if(!maze[dx][dy].wall_R)
    {
            setcolor(COLOR(0,100,0));
            line(((dx+1)*60),((dy+1)*60)-60,((dx+1)*60),((dy+1)*60));                        
    }
    if(!maze[dx][dy].wall_U)
    {
           setcolor(COLOR(100,100,0));
           line(((dx+1)*60)-60,((dy+1)*60)-60,((dx+1)*60),((dy+1)*60)-60);                         
    }   
}
 int LrobotplaceX;
 int LrobotplaceY;
void DrawRobot(int rbx,int rby)
{
    
     setcolor(0);
     circle(LrobotplaceX,LrobotplaceY,29);
     int robotplaceX=((rbx+1)*60)-30;
     int robotplaceY=((rby+1)*60)-30; 
     setcolor(14);
     circle(robotplaceX,robotplaceY,29);  
     LrobotplaceX=robotplaceX;
     LrobotplaceY=robotplaceY;  
}
int Xsize=0;
int Ysize=0;
void moveDir(int dir)
{
     robot.Gy=(Ysize-1)-robot.y;
     if(dir==0 && maze[robot.x][robot.Gy].wall_U==0){robot.y++;}
     else if(dir==1 && maze[robot.x][robot.Gy].wall_R==0){robot.x++;}
     else if(dir==2 && maze[robot.x][robot.Gy].wall_D==0){robot.y--;}
     else if(dir==3 && maze[robot.x][robot.Gy].wall_L==0){robot.x--;}
     robot.Gy=(Ysize-1)-robot.y;
     DrawRobot(robot.x,robot.Gy);
}
void turnLeft()
{
     robot.d--;
     if(robot.d<0)robot.d=3;
}
void turnRight()
{
     robot.d++;
     if(robot.d>3)robot.d=0;
}
void turnU()
{
     turnLeft();
     turnLeft();
}
void showWalls()
{
     walls.u=0;
     walls.r=0;
     walls.l=0;
     walls.d=0;
   if(robot.d==0)
   {
       walls.u=maze[robot.x][robot.Gy].wall_U;
       walls.l=maze[robot.x][robot.Gy].wall_L;              
       walls.r=maze[robot.x][robot.Gy].wall_R; 
       walls.d=maze[robot.x][robot.Gy].wall_D;
   }
   else if(robot.d==1)
   {
       walls.u=maze[robot.x][robot.Gy].wall_R;
       walls.l=maze[robot.x][robot.Gy].wall_U;
       walls.r=maze[robot.x][robot.Gy].wall_D;     
       walls.d=maze[robot.x][robot.Gy].wall_L;     
   }
   else if(robot.d==2)
   {
       walls.u=maze[robot.x][robot.Gy].wall_D;
       walls.l=maze[robot.x][robot.Gy].wall_R;
       walls.r=maze[robot.x][robot.Gy].wall_L;     
       walls.d=maze[robot.x][robot.Gy].wall_U;     
   }  
   else if(robot.d==3)
   {
       walls.u=maze[robot.x][robot.Gy].wall_L;
       walls.l=maze[robot.x][robot.Gy].wall_D;
       walls.r=maze[robot.x][robot.Gy].wall_U;     
       walls.d=maze[robot.x][robot.Gy].wall_R;     
   }
     
}
void RightHand()
{
              showWalls();
               if(!walls.r){turnRight(); cout<<"turnRight";}
               else if(!walls.u) {cout<<"moveForward";}
               else if(!walls.l){turnLeft(); cout<<"turnLeft";}
               else {turnU(); cout<<"turnU";}
               cout<<"direction = "<<robot.d<<"\n";
               cout<<"X="<<robot.x<<"\n";
               cout<<"Y="<<robot.Gy<<"\n";
               cout<<"wallU"<<walls.u<<"\n";
               cout<<"wallL"<<walls.l<<"\n";
               cout<<"wallR"<<walls.r<<"\n";
               cout<<"wallD"<<walls.d<<"\n";
               moveDir(robot.d);             
}
//____________________FloodFillAlgorithmPart______________
void scoreing()
{
 int tileScore=0;
   for(int i=0;i<Xsize;i++)
  {
           for(int j=0;j<Ysize;j++)
           {
                   fmaze[i][j].score=-1;
           }
  }
  fmaze[robot.x][robot.Gy].score=0;
  
   for(tileScore=0;tileScore<=(Xsize*Ysize);tileScore++)
   {
      for(int i=0;i<Ysize;i++)
      {
         for(int j=0;j<Xsize;j++)
         {
            if(fmaze[j][i].score == tileScore)
            {
               if(j>0)           {if(fmaze[j-1][i].score < 0 && fmaze[j][i].wall_L == 0)  fmaze[j-1][i].score = tileScore+1; }
               if(j<Xsize)  {if(fmaze[j+1][i].score < 0 && fmaze[j][i].wall_R == 0)  fmaze[j+1][i].score = tileScore+1; }
               if(i>0)           {if(fmaze[j][i-1].score < 0 && fmaze[j][i].wall_U == 0)  fmaze[j][i-1].score = tileScore+1; }
               if(i<Ysize)  {if(fmaze[j][i+1].score < 0 && fmaze[j][i].wall_D == 0)  fmaze[j][i+1].score = tileScore+1; }
            }
         }
      }
   }     
     for(int si=0;si<Xsize;si++)
     {
          cout<<"start\n";
          for(int sj=0;sj<Ysize;sj++)
          {
                  cout<<"X :"<<si<<"__Y"<<sj<<"__score : "<<fmaze[si][sj].score<<"\n";  
          }
    }   
} 
 int nextX=0;
 int nextY=0;
void gotoxy(int goalX,int goalY)
{
   signed int nextScore;
    nextX=goalX;
    nextY=goalY;
   bool flag=0;
   signed int Xerr;
   signed int Yerr;
   scoreing();
    cout<<"NextX:"<<nextX<<"\n";
    cout<<"NextY:"<<nextY<<"\n";
   
   nextScore=fmaze[goalX][goalY].score;
    cout<<"GoalScore"<<fmaze[goalX][goalY].score<<"\n";
   while(nextScore>1)
   {
      if(nextX < Xsize-1) {if(fmaze[nextX+1][nextY].score == (nextScore-1) && !fmaze[nextX+1][nextY].wall_L){ nextX++;cout<<"Xplus One\n"; flag=1;}}  
      if(nextX > 0 && !flag) {if(fmaze[nextX-1][nextY].score == (nextScore-1) && !fmaze[nextX-1][nextY].wall_R) {nextX--;cout<<"Xminus One\n"; flag=1;}}
      if(nextY > 0 && !flag) {if(fmaze[nextX][nextY-1].score == (nextScore-1) && !fmaze[nextX][nextY].wall_U){ nextY--;cout<<"Ymines One One\n"; flag=1;}}
      if(nextY < Ysize-1 && !flag) {if(fmaze[nextX][nextY+1].score == (nextScore-1) && !fmaze[nextX][nextY].wall_D) {nextY++;cout<<"Yplus One\n"; flag=1;}}
      
      nextScore--;
      flag=0;
      cout<<"NextX:"<<nextX<<"\n";
    cout<<"NextY:"<<nextY<<"\n";
   }     
   cout<<"NextScore"<<nextScore<<"\n";
   cout<<"after NextX:"<<nextX<<"\n";
   cout<<"after NextY:"<<nextY<<"\n";
    Xerr=nextX-robot.x;
    Yerr=nextY-robot.Gy;
    cout<<"Xerr:"<<Xerr<<"\n";
    cout<<"Yerr"<<Yerr<<"\n";
    if(Xerr<0){moveDir(3);}
    else if(Xerr>0){moveDir(1);}
    else if(Yerr<0){moveDir(0);}
    else if(Yerr>0){moveDir(2);}   
}
bool sweep=0;
int NextStepX;
int NextStepY;
void FloodFill()
{
     int allvisited=0;
     scoreing();
    if(robot.x == Xsize-1) 
    {
               for(int j=0;j<Xsize;j++)
               {
                        if(fmaze[j][robot.Gy].visited == 0 &&  fmaze[j][robot.Gy].score != -1)
                        {
                             sweep=1;      
                        }
                }              
    }   
    else if(robot.x == 0) 
    {
         for(int j=0;j<Xsize;j++)
               {
                        if(fmaze[j][robot.Gy].visited == 0 &&  fmaze[j][robot.Gy].score != -1)
                        {
                             sweep=0;      
                        }
                }              
    }
   cout<<"sweep :"<<sweep<<"\n";
   if(sweep == 0)
   {
      for(int i=Ysize-1;i>=0;i--)
      {
         for(int j=0;j<Xsize;j++)
         {
            if(fmaze[j][i].visited == 0 &&  fmaze[j][i].score !=-1)
            {
               NextStepX=j;
               NextStepY=i;
               j=200;
               i=-1;
            }
         }
      }
   }
   
   if(sweep == 1)
   {
      for(int i=Ysize-1;i>=0;i--)
      {
         for(int j=Xsize-1;j>=0;j--)
         {
            if(fmaze[j][i].visited == 0 &&  fmaze[j][i].score != -1)
            {
               NextStepX=j;
               NextStepY=i;
               j=-1;
               i=-1;
            }
         } 
      }
   }
   for(int i=Ysize-1;i>=0;i--)
      {
         for(int j=Xsize-1;j>=0;j--)
         {
            if(fmaze[j][i].visited == 0 &&  fmaze[j][i].score !=-1)
            {
                  allvisited++;
            }
         } 
      }
      if(allvisited==0)
      {
           NextStepX=start.x;
           NextStepY=start.y;
      }
  
}
void maping(int mapX,int mapY)
{
     fmaze[mapX][mapY].wall_U=maze[mapX][mapY].wall_U;if(robot.Gy < Ysize) fmaze[mapX][mapY-1].wall_D = maze[mapX][mapY].wall_U; 
     fmaze[mapX][mapY].wall_D=maze[mapX][mapY].wall_D;if(robot.Gy > 0) fmaze[mapX][mapY+1].wall_U = maze[mapX][mapY].wall_D ;
     fmaze[mapX][mapY].wall_L=maze[mapX][mapY].wall_L;if(robot.x > 0) fmaze[mapX-1][mapY].wall_R = maze[mapX][mapY].wall_L ; 
     fmaze[mapX][mapY].wall_R=maze[mapX][mapY].wall_R;if(robot.x < Xsize) fmaze[mapX+1][mapY].wall_L = maze[mapX][mapY].wall_R ;      
}
bool goalReached=1;
void mainFloodFill()
{
    if(goalReached == 1)
      {
          cout<<"goalreached\n";
         FloodFill();
         goalReached=0;
      }
      if(!goalReached)
      {
         cout<<"not in goal\n";
          maping(robot.x,robot.Gy); 
         fmaze[robot.x][robot.Gy].visited=1;
         gotoxy(NextStepX,NextStepY);
         maping(robot.x,robot.Gy); 
         fmaze[robot.x][robot.Gy].visited=1;
         if(robot.x == NextStepX && robot.Gy== NextStepY || fmaze[NextStepX][NextStepY].score==-1) {goalReached=1;} 
             
      } 
     
     

}


//____________________FloodFillAlgorithmPart______________

//____________________TREMAUX_Algorithm_Part______________
bool openWays[4];
bool hereIsInter=0;
int hereLabel=0;
bool firstTime=1;
int countOfInters=0;
void getInformation()
{
     openWays[0]=0;
     openWays[1]=0;
     openWays[2]=0;
     openWays[3]=0;
     showWalls();
     if(!walls.u)
     {
          if(robot.d==0)
          {
              for(int i=0;i<=countOfInters;i++)
              {
                  if(inter[i].x==robot.x && inter[i].y==robot.y+1)
                  {
                       if(i==robot.LinterLabel)
                       {
                            openWays[0]=1;
                            i=200;
                       }                  
                       else
                       {
                            openWays[0]=0;
                            inter[i].downVisited=1;    
                            i=200;
                       }      
                  }
                  else{openWays[0]=1;}
                                            
                                     
              }                       
                        
          }
          if(robot.d==1)
          {
              for(int i=0;i<=countOfInters;i++)
              {
                  if(inter[i].x==robot.x+1 && inter[i].y==robot.y)
                  {
                       if(i==robot.LinterLabel)
                       {
                            openWays[1]=1;
                            i=200;
                       }                  
                       else
                       {
                            openWays[1]=0;
                            inter[i].leftVisited=1;    
                            i=200;
                       }      
                  }
                  else{openWays[1]=1;}
                                            
                                     
              }                       
                        
          } 
          if(robot.d==2)
          {
              for(int i=0;i<=countOfInters;i++)
              {
                  if(inter[i].x==robot.x && inter[i].y==robot.y-1)
                  {
                       if(i==robot.LinterLabel)
                       {
                            openWays[2]=1;
                            i=200;
                       }                  
                       else
                       {
                            openWays[2]=0;
                            inter[i].upVisited=1;    
                            i=200;
                       }      
                  }
                  else{openWays[2]=1;}
                                            
                                     
              }                       
                        
          }                
          if(robot.d==3)
          {
              for(int i=0;i<=countOfInters;i++)
              {
                  if(inter[i].x==robot.x-1 && inter[i].y==robot.y)
                  {
                       if(i==robot.LinterLabel)
                       {
                            openWays[3]=1;
                            i=200;
                       }                  
                       else
                       {
                            openWays[3]=0;
                            inter[i].rightVisited=1;    
                            i=200;
                       }      
                  }
                  else{openWays[3]=1;}
                                            
                                     
              }                       
                        
          }                 
       
                 
     }    
     if(!walls.r)
     {
          if(robot.d==0)
          {
              for(int i=0;i<=countOfInters;i++)
              {
                  if(inter[i].x==robot.x+1 && inter[i].y==robot.y)
                  {
                       if(i==robot.LinterLabel)
                       {
                            openWays[1]=1;
                            i=200;
                       }                  
                       else
                       {
                            openWays[1]=0;
                            inter[i].leftVisited=1;    
                            i=200;
                       }      
                  }
                  else{openWays[1]=1;}
                                            
                                     
              }                       
                        
          }
          if(robot.d==1)
          {
              for(int i=0;i<=countOfInters;i++)
              {
                  if(inter[i].x==robot.x && inter[i].y==robot.y-1)
                  {
                       if(i==robot.LinterLabel)
                       {
                            openWays[2]=1;
                            i=200;
                       }                  
                       else
                       {
                            openWays[2]=0;
                            inter[i].upVisited=1;    
                            i=200;
                       }      
                  }
                  else{openWays[2]=1;}
                                            
                                     
              }                       
                        
          } 
          if(robot.d==2)
          {
              for(int i=0;i<=countOfInters;i++)
              {
                  if(inter[i].x==robot.x-1 && inter[i].y==robot.y)
                  {
                       if(i==robot.LinterLabel)
                       {
                            openWays[3]=1;
                            i=200;
                       }                  
                       else
                       {
                            openWays[3]=0;
                            inter[i].rightVisited=1;    
                            i=200;
                       }      
                  }
                  else{openWays[3]=1;}
                                            
                                     
              }                       
                        
          }                
          if(robot.d==3)
          {
              for(int i=0;i<=countOfInters;i++)
              {
                  if(inter[i].x==robot.x && inter[i].y==robot.y+1)
                  {
                       if(i==robot.LinterLabel)
                       {
                            openWays[0]=1;
                            i=200;
                       }                  
                       else
                       {
                            openWays[0]=0;
                            inter[i].downVisited=1;    
                            i=200;
                       }      
                  }
                  else{openWays[0]=1;}
                                            
                                     
              }                       
                        
          }           
                 
     
     
     
     
     }
     
     
     if(!walls.l)
     {
          if(robot.d==0)
          {
              for(int i=0;i<=countOfInters;i++)
              {
                  if(inter[i].x==robot.x-1 && inter[i].y==robot.y)
                  {
                       if(i==robot.LinterLabel)
                       {
                            openWays[3]=1;
                            i=200;
                       }                  
                       else
                       {
                            openWays[3]=0;
                            inter[i].rightVisited=1;    
                            i=200;
                       }      
                  }
                  else{openWays[3]=1;}
                                            
                                     
              }                       
                        
          }
          if(robot.d==1)
          {
              for(int i=0;i<=countOfInters;i++)
              {
                  if(inter[i].x==robot.x && inter[i].y==robot.y+1)
                  {
                       if(i==robot.LinterLabel)
                       {
                            openWays[0]=1;
                            i=200;
                       }                  
                       else
                       {
                            openWays[0]=0;
                            inter[i].downVisited=1;    
                            i=200;
                       }      
                  }
                  else{openWays[0]=1;}
                                            
                                     
              }                       
                        
          } 
          if(robot.d==2)
          {
              for(int i=0;i<=countOfInters;i++)
              {
                  if(inter[i].x==robot.x+1 && inter[i].y==robot.y)
                  {
                       if(i==robot.LinterLabel)
                       {
                            openWays[1]=1;
                            i=200;
                       }                  
                       else
                       {
                            openWays[1]=0;
                            inter[i].leftVisited=1;    
                            i=200;
                       }      
                  }
                  else{openWays[1]=1;}
                                            
                                     
              }                       
                        
          }                
          if(robot.d==3)
          {
              for(int i=0;i<=countOfInters;i++)
              {
                  if(inter[i].x==robot.x && inter[i].y==robot.y-1)
                  {
                       if(i==robot.LinterLabel)
                       {
                            openWays[2]=1;
                            i=200;
                       }                  
                       else
                       {
                            openWays[2]=0;
                            inter[i].upVisited=1;    
                            i=200;
                       }      
                  }
                  else{openWays[2]=1;}
                                            
                                     
              }                       
                        
          }           
     }     
    if(firstTime)
     {
          if(!walls.d)
          {             
              if(robot.d==0)
              {
                  openWays[2]=1;
              }        
              if(robot.d==1)
              {
                  openWays[3]=1;
              }
              if(robot.d==2)
              {
                  openWays[0]=1;
              }
              if(robot.d==3)
              {
                  openWays[1]=1;
              }
          }
                
     }
     hereIsInter=0;
     for(int i=1;i<=countOfInters;i++)
     {
             if(inter[i].x==robot.x && inter[i].y==robot.y)
             {
                   hereIsInter=1;
                   hereLabel=i;
                   i=200;
             }
     }
     
     cout<<"openWays[0] = "<<openWays[0]<<"\n";
     cout<<"openWays[1] = "<<openWays[1]<<"\n";
     cout<<"openWays[2] = "<<openWays[2]<<"\n";
     cout<<"openWays[3] = "<<openWays[3]<<"\n";
    
     cout<<"robot.X"<<robot.x<<"\n";    
     cout<<"robot.Y"<<robot.y<<"\n";
      cout<<"robot.d before"<<robot.d<<"\n";
    
      cout<<"__________________________________\n";
   
}

void setAsInter()
{
     countOfInters++;
     inter[countOfInters].x=robot.x;
     inter[countOfInters].y=robot.y;
     inter[countOfInters]. LTLabel=robot.LinterLabel;
     if(robot.d==0){inter[countOfInters].LastIntDir=2;}
     if(robot.d==1){inter[countOfInters].LastIntDir=3;}
     if(robot.d==2){inter[countOfInters].LastIntDir=0;}
     if(robot.d==3){inter[countOfInters].LastIntDir=1;}
     cout<<"setAsInter"<<"\n";
     cout<<"InterX = "<<inter[countOfInters].x<<"\n";
     cout<<"InterY = "<<inter[countOfInters].y<<"\n";
      inter[countOfInters].upVisited=!openWays[0];
      inter[countOfInters].rightVisited=!openWays[1];
      inter[countOfInters].downVisited=!openWays[2];
      inter[countOfInters].leftVisited=!openWays[3];
     
}
int nextDir=0;
int sumOfWays=0;
void ChoseDirection()
{
     if(robot.d==0)
     {
         sumOfWays=openWays[3]+openWays[0]+openWays[1];
     }
     else if(robot.d==1)
     {
         sumOfWays=openWays[0]+openWays[1]+openWays[2];  
     }
     else if(robot.d==2)
     {
         sumOfWays=openWays[1]+openWays[2]+openWays[3];  
     }
     else if(robot.d==3)
     {
         sumOfWays=openWays[2]+openWays[3]+openWays[0];  
     }
     
    while(true)
    {
        if(firstTime)
        {
             setAsInter();
             hereIsInter=1;
             hereLabel=countOfInters;
             inter[countOfInters].LastIntDir=5;
             firstTime=0;
        }
        if(!hereIsInter && sumOfWays==1)
        { 
             if(robot.d==0) 
             {
                  if(openWays[3]){nextDir=3;break;}
                  else if(openWays[0]){nextDir=0;break;}
                  else if(openWays[1]){nextDir=1;break;}     
             }
             else if(robot.d==1)
             {
                  if(openWays[0]){nextDir=0;break;}
                  else if(openWays[1]){nextDir=1;break;}
                  else if(openWays[2]){nextDir=2;break;} 
             }
             else if(robot.d==2)
             {
                  if(openWays[1]){nextDir=1;break;}
                  else if(openWays[2]){nextDir=2;break;}
                  else if(openWays[3]){nextDir=3;break;} 
             }
             else if(robot.d==3)
             {
                  if(openWays[2]){nextDir=2;break;}
                  else if(openWays[3]){nextDir=3;break;}
                  else if(openWays[0]){nextDir=0;break;} 
             }
        }
        
        else if(!hereIsInter && sumOfWays==0)
        { 
             if(robot.d==0)
             {
                 nextDir=2;
                 break;
             }
             else if(robot.d==1)
             {
                nextDir=3;
                 break; 
             }
             else if(robot.d==2)
             {
                 nextDir=0;
                 break;
             }
             else if(robot.d==3)
             {
                 nextDir=1;
                 break;
             }
        }
        
        else if(!hereIsInter && sumOfWays >= 2)
        {
             setAsInter();
             hereIsInter=1;
             hereLabel=countOfInters; 
                
        }
        
        if(hereIsInter)
        {
             bool fl=0;
             cout<<"____________________________________________\n";
             cout<<"upvisited : "<<inter[hereLabel].upVisited<<"\n";
             cout<<"rightvisited : "<<inter[hereLabel].rightVisited<<"\n";
             cout<<"downvisited : "<<inter[hereLabel].downVisited<<"\n";
             cout<<"leftvisited : "<<inter[hereLabel].leftVisited<<"\n";
             cout<<"LastInterDir : "<<inter[hereLabel].LastIntDir<<"\n";
             cout<<"____________________________________________\n";
             if(robot.d==0)
             {
                  if(inter[hereLabel].leftVisited==0)
                  {
                        nextDir=3;
                        inter[hereLabel].leftVisited=1;
                        fl=1;
                  }
                  if(inter[hereLabel].upVisited==0 && !fl)
                  {
                        nextDir=0;
                        inter[hereLabel].upVisited=1;
                        fl=1;
                  }
                  if(inter[hereLabel].rightVisited==0 && !fl)
                  {
                        nextDir=1;
                        inter[hereLabel].rightVisited=1;
                        fl=1;
                  }
                  if(!fl){nextDir=inter[hereLabel].LastIntDir;}
             }
             if(robot.d==1)
             {
                  if(inter[hereLabel].upVisited==0 && !fl)
                  {
                        nextDir=0;
                        inter[hereLabel].upVisited=1;
                        fl=1;
                  }
                  if(inter[hereLabel].rightVisited==0 && !fl)
                  {
                        nextDir=1;
                        inter[hereLabel].rightVisited=1;
                        fl=1;
                  }
                  if(inter[hereLabel].downVisited==0 && !fl)
                  {
                        nextDir=2;
                        inter[hereLabel].downVisited=1;
                        fl=1;
                  }
                  if(!fl){nextDir=inter[hereLabel].LastIntDir;}
             }
             if(robot.d==2)
             {
                 
                  if(inter[hereLabel].rightVisited==0 && !fl)
                  {
                        nextDir=1;
                        inter[hereLabel].rightVisited=1;
                        fl=1;
                  }
                  if(inter[hereLabel].downVisited==0 && !fl)
                  {
                        nextDir=2;
                        inter[hereLabel].downVisited=1;
                        fl=1;
                  }
                   if(inter[hereLabel].leftVisited==0 && !fl)
                  {
                        nextDir=3;
                        inter[hereLabel].leftVisited=1;
                        fl=1;
                  }
                  if(!fl){nextDir=inter[hereLabel].LastIntDir;}
             }
             if(robot.d==3)
             {
                 
                  if(inter[hereLabel].downVisited==0 && !fl)
                  {
                        nextDir=2;
                        inter[hereLabel].downVisited=1;
                        fl=1;
                  }
                   if(inter[hereLabel].leftVisited==0 && !fl)
                  {
                        nextDir=3;
                        inter[hereLabel].leftVisited=1;
                        fl=1;
                  }
                   if(inter[hereLabel].upVisited==0 && !fl)
                  {
                        nextDir=0;
                        inter[hereLabel].upVisited=1;
                        fl=1;
                  }
                  if(!fl){nextDir=inter[hereLabel].LastIntDir;}          
             }
             if(fl)
             {
                   robot.LinterLabel=hereLabel;break;
             }
             if(!fl)
             {
                   robot.LinterLabel=inter[hereLabel].LTLabel;break;
             }
             
        }
        
        break;
    }
}

void Moving()
{
     cout<<"ChosedDir : "<<nextDir<<"\n";
     cout<<"hereisInter : "<<hereIsInter<<"\n";
     cout<<"hereLabel : "<<hereLabel<<"\n";
     signed int DirErr=0;
     DirErr=nextDir-robot.d;
     while(DirErr!=0)
     {
          if(nextDir==5){break;}
          DirErr=nextDir-robot.d;
          if(DirErr==0){break;}
          if(DirErr > 0 && DirErr<=2)
          {
             turnRight();  
          }
          if(DirErr < 0 && DirErr>=-2)
          {
             turnLeft();  
          }
          if(DirErr > 0 && DirErr==3)
          {
             turnLeft();  
          }
          if(DirErr < 0 && DirErr==-3)
          {
             turnRight();  
          }
           cout<<"robot.d"<<robot.d<<"\n";
           cout<<"__________________________________\n";
     }
     if(nextDir!=5)
     {
     moveDir(robot.d);
     }
}



//____________________TREMAUX_Algorithm_Part______________
void cleareveryThing()
{
     for(int i=Ysize;i>=0;i--)
      {
         for(int j=Xsize;j>=0;j--)
         {
            maze[j][i].wall_U=0;
            maze[j][i].wall_L=0;
            maze[j][i].wall_R=0;
            maze[j][i].wall_D=0;
            fmaze[j][i].wall_U=0;
            fmaze[j][i].wall_L=0;
            fmaze[j][i].wall_R=0;
            fmaze[j][i].wall_D=0;
            fmaze[j][i].score=0;
            fmaze[j][i].visited=0;
         } 
      }
      for(int i=0;i<MaxInters;i++)
      {
             
           
            inter[i].upVisited=0;
            inter[i].rightVisited=0;
            inter[i].leftVisited=0;
            inter[i].downVisited=0;       
            inter[i].LastIntDir=0;
            inter[i].x=0;
            inter[i].y=0;
            inter[i].LTLabel=0;        
              
      }
openWays[4];
hereIsInter=0;
hereLabel=0;
firstTime=1;
countOfInters=0;
 inter[0].x=100;
 inter[0].y=100;
mazechanged=1;
robotmoved=1;
gotoedit=1;
robot.x=0;
robot.y=0;
}
int main()
{     
while(true)
{

      int kind_of_algorithm=0;
      cleartextScreen();
      cleareveryThing();
       cout<<"******************************************\n"; 
       cout<<"*************_Hello User_*****************\n";
       cout<<"******************************************\n";
       cout<<"************_rescue-algorithms_***********\n";
       cout<<"************_version:1.5.0_***************\n";  
      cout<<"this program is a virtual rescue b maze\n"; 
      cout<< "that you can show or test your algorithm\n";
      cout<< "__________________________________\n";
      cout<< "this app was programed by 'Di-Mad'\n";
      cout<< "__________________________________\n";
     cout<<"Enter your maze X size{0 < X <10 }:  ";
     cin>>Xsize;
     if(Xsize>10){Xsize=10;}
     cout<<"Enter your maze Y size{0 < Y <12 }: ";
     cin>>Ysize;
     if(Ysize>12){Ysize=12;}
      cout<< "__________________________________\n";
      cout<<"Enter Your Algorithm :\n";
      cout<<"1.selfcontrol(control by your self No special Algorithm)\n";
      cout<<"2.RightHandAlgorithm\n";
      cout<<"3.FloodFill\n";
      cout<<"4.Tremaux Algorithm\n";
      cin>>kind_of_algorithm;
      if(kind_of_algorithm>4){kind_of_algorithm=4;}
      if(kind_of_algorithm==2)
      {
            cout<< "__________RightHand___________\n";
            cout<<"Enter starting direction\n";
            cout<<"0.North\n";
            cout<<"1.East\n";
            cout<<"2.South\n";
            cout<<"3.West\n";
            cin>>robot.d;                           
      }
      if(kind_of_algorithm==3)
      {
           cout<< "__________FloodFill___________\n"; 
           cout<<"Enter starting tile X : \n";
           cin>>robot.x;
           if(robot.x>Xsize-1){robot.x=Xsize-1;}
            cout<<"Enter starting tile Y : \n";
           cin>>robot.y;
           if(robot.y>Ysize-1){robot.y=Ysize-1;} 
           start.x=robot.x;
           start.y=(Ysize-1)-robot.y;                                  
      }
      if(kind_of_algorithm==4)
      {
           cout<<"___________tremaux____________\n";
           cout<<"Enter starting tile X : \n";
           cin>>robot.x;
           cout<<"Enter starting tile Y : \n";
           cin>>robot.y;
           cout<<"Enter starting direction\n";
            cout<<"0.North\n";
            cout<<"1.East\n";
            cout<<"2.South\n";
            cout<<"3.West\n";
            cin>>robot.d;                           
      }
      
     for(int i=0;i<Xsize;i++)
     {
             maze[i][0].wall_U=1;
     }
     for(int i=0;i<Ysize;i++)
     {
             maze[0][i].wall_L=1;
     }
     for(int i=0;i<Ysize;i++)
     {
             maze[Xsize-1][i].wall_R=1;
             maze[Xsize][i].wall_L=1;
     }
     for(int i=0;i<Xsize;i++)
     {
             maze[i][Ysize-1].wall_D=1;
             maze[i][Ysize].wall_U=1;
     }
     initwindow(610,800,"Rescue B version:1.5.0"); 
     int mx=0;
     int my=0;
    robot.Gy=(Ysize-1)-robot.y;
    DrawRobot(robot.x,robot.Gy);   
    while(true)
    {
         if(gotoedit==1)
         {
          setcolor(15);              
         outtextxy(0,750,"click on walls and place them then press any key to start moving robot");
         outtextxy(0,765,"press 'E' to edit the maze then press any key to move robot    ");
         outtextxy(0,780,"press 'Esc' to close the window and go back to main page     programmed By__Di-MaD__");
         while(!kbhit())
         {
              if((mx!=mousex())||(my!=mousey()))
              {
              setcolor(0);
              circle(mx,my,10);
              mx=mousex();
              my=mousey();
              setcolor(15);
              circle(mx,my,10);
              }
              
              
              
               for(int a=0;a<Max_X;a++)
               {
                        for(int b=0;b<Max_Y;b++)
                        {          
                                       setcolor(15);
                                       DrawMaze(a,b); 
                                      
                        }
                }
                DrawRobot(robot.x,robot.Gy);
                if(ismouseclick(WM_LBUTTONDOWN))
                {
                        mouse.x=mousex();
                        mouse.y=mousey();
                        int point_X=(mouse.x/60);
                        int dir_X =(mouse.x%60);
                        int point_Y=(mouse.y/60);
                        int dir_Y =(mouse.y%60);
                        if(dir_X<5)
                        {
                                    if(maze[point_X][point_Y].wall_L==1){maze[point_X][point_Y].wall_L=0;maze[point_X-1][point_Y].wall_R=0;}
                                    else if(maze[point_X][point_Y].wall_L==0){maze[point_X][point_Y].wall_L=1;maze[point_X-1][point_Y].wall_R=1;}
                        }
                        if(dir_X>55)
                        {
                                   if(maze[point_X][point_Y].wall_R==1){maze[point_X][point_Y].wall_R=0;maze[point_X+1][point_Y].wall_L=0;}
                                   else if(maze[point_X][point_Y].wall_R==0){maze[point_X][point_Y].wall_R=1;maze[point_X+1][point_Y].wall_L=1;}   
                        }
                        if(dir_Y>55)
                        {
                                    if(maze[point_X][point_Y].wall_D==1){maze[point_X][point_Y].wall_D=0;maze[point_X][point_Y+1].wall_U=0;}
                                    else if(maze[point_X][point_Y].wall_D==0){maze[point_X][point_Y].wall_D=1;maze[point_X][point_Y+1].wall_U=1;}
                        }
                        if(dir_Y<5)
                        {
                                    if(maze[point_X][point_Y].wall_U==1){maze[point_X][point_Y].wall_U=0;maze[point_X][point_Y-1].wall_D=0;}
                                    else if(maze[point_X][point_Y].wall_U==0){maze[point_X][point_Y].wall_U=1;maze[point_X][point_Y-1].wall_D=1;}
                        }
                        mazechanged=1;
                        clearmouseclick(WM_LBUTTONDOWN);                              
                }
                
         }
         gotoedit=0;
         }
                       
                if(gotoedit==0)
                {
                input=getch();
                
                }
                if(input==27)
                {
                      break;
                }
               if(input==101)
               {
                     gotoedit=1;                  
               } 
               if(kind_of_algorithm==1)
               {
                          if(input==77)
                        {
                                     moveDir(1);
                                     input=0;
                         
                         }   
                         if(input==75)
                         {                         
                                     moveDir(3);        
                                     input=0;
                         }   
                        if(input==72)
                        {
                                     moveDir(0);                  
                                     input=0; 
                        }   
                         if(input==80)
                         {
                                      moveDir(2);
                                      input=0;
                         }                                                
               }
             
               
              
               if(kind_of_algorithm==2)
               {
                RightHand();                
               } 
               if(kind_of_algorithm==3)
               {
                   mainFloodFill();                        
               }
               if(kind_of_algorithm==4)
               {
                   getInformation();
                   ChoseDirection();
                   Moving();
               }
                
    }
    closegraph();
}            
}
