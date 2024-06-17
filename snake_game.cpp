#include<iostream>
#include<windows.h>
#include<conio.h>

using namespace std;

bool gameOver;
const int width=20;
const int height=20;
int x,y,fruitX,fruitY,score;
int tailX[100], tailY[100];
int nTail; 
enum eDirection {STOP=0,LEFT,RIGHT,UP,DOWN};
eDirection dir;
eDirection tailDir[100];

void Setup()
{//assigning position of fruit and snake
    gameOver=false;
    dir=STOP;
    x=width/2;
    y=height/2;
    fruitX=rand() % width;
    fruitY=rand() % height;
    score=0;
    nTail = 0;
}

void Draw()
{//shape of snake , wall, and fruit
    system("cls");//this stop repeating printing many times
    for(int i=0; i<width+2; i++)
    cout<<"+";
    cout<<endl;

    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
          if (j==0)
          cout<<"|";
          if(i==y && j==x)
          cout<<"`";
          else if(i==fruitY && j==fruitX)
          cout<<"O";
          else
          { 
            bool print = false;
            for(int k=0; k<nTail; k++)
            {
                
                if (tailX[k] == j && tailY[k] == i) {
                        if (tailDir[k] == LEFT || tailDir[k] == RIGHT)
                            cout << "~"; // Horizontal segment
                        else if (tailDir[k] == UP || tailDir[k] == DOWN)
                            cout << "|"; // Vertical segment
                        print = true;
                } 
            }
            if(!print)
            cout<<" "; 
          } 
        

        if(j==width-1)
        cout<<"|";
    }
    cout<<endl;
}

for (int i=0;i<width+2;i++)
cout<<"+";
cout<<endl;
cout<<"Score: "<<score<<endl;
cout<<"O is fruit and ` is snake"<<endl;
}

void Input()
{//assigning key
    if(_kbhit())
    {
        switch(_getch())
        {
            case 'a':
            dir=LEFT;
            break;
            case 'd':
            dir=RIGHT;
            break;
            case 'w':
            dir=UP;
            break;
            case 's':
            dir=DOWN;
            break;
            case 'x':
            gameOver=true;
            break;
        }
    }
}

void Logic()
{
    int prevX=tailX[0];
    int prevY=tailY[0];
    int prev2X, prev2Y;
    eDirection prevDir = tailDir[0];
    tailX[0]=x;
    tailY[0]=y;
    tailDir[0] = dir;
    
    for(int i=1;i<nTail;i++)
    {
        prev2X=tailX[i];
        prev2Y=tailY[i];
        eDirection prev2Dir = tailDir[i];
        tailX[i]=prevX;
        tailY[i]=prevY;
        tailDir[i] = prevDir;
        prevX=prev2X;
        prevY=prev2Y;
        prevDir = prev2Dir;
    }
    //functioning of keys
    switch(dir)
    {
        case LEFT:
        x--;
        break;
        case RIGHT:
        x++;
        break;
        case UP:
        y--;
        break;
        case DOWN:
        y++;
        break;
        default:
        break;
    }

        // Check for collision with walls
    //if (x >= width || x < 0 || y >= height || y < 0) {
       // gameOver = true;

       if(x>=width) 
       x=0;
       else if (x<0)
       x=width-1;

       if(y>=height) 
       y=0;
       else if (y<0)
       y=height-1;

    for(int i=0;i<nTail;i++)
    if(tailX[i]==x && tailY[i]==y)
    gameOver=true;
    

    // Check for collision with the fruit
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}
    
int main()
{
   Setup();
   while(!gameOver){
   Draw();
   Input();
   Logic(); 
   Sleep(100);//sleep will slow down the speed
}
}