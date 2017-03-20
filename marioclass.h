#include<iostream>
#include<vector>
#include<thread>
using namespace std;

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
using namespace sf;

class Mario{     //decalring class mario with functions and variables
   public:
   vector<VideoMode> array1;
   RenderWindow window;                      //game window
   VideoMode mode;
   
   Texture texture;
   RectangleShape sprite;                         //sprite and texture for mario
   
   Texture background,background1,background2,background3;
   Sprite gameframe;  
   Sprite ins;
   Sprite credit;

   Texture ins_page;             //different textures for coins and mosters
   Texture cre_page;
   Texture gameover,gamewin;
   Texture co,spco,enemy;
   
   sf::Font font;
   Text text, text1, text2,text3,text5, score1, score, scorename, timename;
   Text credits1, credits2, credits3;
   
   Sprite frame;  
   Sprite f1,f2; 
   Sprite bigframe; 
    
   Clock clock; 
   int bulletcount;           //variables needded throughout game
   int coinswon;
   bool isfiring;
   int baseheight;
   int width, height, globalwidth, allowright,otherycounter, jumpcounter, jumpnextheight;
   int leftbound, rightbound, heightlevel, step, stepchange, nextheight,prevheight,levelchange, isgameover,isgamewin;
   int vertical;
   int width1;
   
   int initialise();          //member functions defined in various header files
   int movemario();
   int moveright();
   int moveup();
   int superjump();
   int moveframe();
   int setstep();
   int startdraw();
   int drawing();
   int startgame();
   int scoreboard();
   
};   

//distances of various obstacles in game
int plotx[40] = {105,150,265,325,365,405,445,500,545,580,615,670,860,880,945,960,1085,1145,1260,1295,1340,1360,1395,1435,1510,1540,1620, 1695,1765,1815,1840,1880,1910,1940,2015,2070,2155,2215,2280,2340};
int ploty[40] = {95,0,-80,0,50,115,185,0,0,0,180,0,0,0,0,0,130,0,115,0,0,0,175,0,125,0,0,0,175,0,0,0,0,0,175,0,0,0,0,55}; 
int anotherwaypossible[40] = {0,0,0,0,0,0,0,2,0,0,0,0,1,1,1,0,-2,0,0,2,0,0,0,0,0,0,1,1,0,0,-1,0,-1,0,-2,-1,-1,-1,-1,-1};
int othery[7] = {165,240,165,185,0,120}; 
int jumpx[6] = {505,1300,1625,1675};
int jumpy[8] = {270,275,0,0,340,185,-70,80};

RectangleShape rect;    //bullets  array
vector<sf::RectangleShape> bullet(10,RectangleShape(rect));
CircleShape circle1;
vector<CircleShape>coin(30,CircleShape(circle1));  //array of coins
CircleShape circle2;
vector<CircleShape>spcoin(3,CircleShape(circle2)); //array of special coins
CircleShape circle3;
vector<CircleShape>monster(2,CircleShape(circle3));   //array of monsters

int visible[30]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

int timebefore;
//coordinates of coins
int x[30]={200,350,500,700,950,1200,1500,1800,2000,2200,2800,3600,3800,4000,4375,4575,4775,6200,6430,6750,6700,7100,7400,7650,7900,8200,8300, 8700,8925,9425};
int y[30]={465,465,465,350,465,465,550,450,410,350,180,465,465,465,300,230,300,465,330,465,190,290,465,330,465,280,280,465,270,450};

int mon_low[2]={1350,2525};
int mon_up[2]={1600,3000};
int mon_ver[2]={495,410};


int vis[2]={1,1}; //for the monsters
int flag1[2]={0,0};
int dis[2] = {1600,2800};

int Mario :: movemario()  //function which moves mario
{
   thread t[3];
      
   if(globalwidth<rightbound){      //checks right bound
      allowright = 1;
      levelchange = 0;
      }
   else if(globalwidth == rightbound && ((anotherwaypossible[step] == -1 && (Keyboard::isKeyPressed(Keyboard::Up) ||Keyboard::isKeyPressed(Keyboard::Right))) || (anotherwaypossible[step] == -2 && (Keyboard::isKeyPressed(Keyboard::Space) ||Keyboard::isKeyPressed(Keyboard::Right))))){   //when mario falls off or steps on thorns
      isgameover = -1;
      } 
   else if(globalwidth>=rightbound && (nextheight<=heightlevel || Keyboard::isKeyPressed(Keyboard::Up)|| Keyboard::isKeyPressed(Keyboard::Space) || (anotherwaypossible[step]==1 && anotherwaypossible[step+1]!=1))){   //setting next step properly
      allowright = 1; 
      t[0] =thread (&Mario::setstep, this);
      t[0].join();
       }  
   else{
      allowright = 0;
      levelchange = 0;
      } 
  
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && allowright)    //on moving right
{
      t[1] =thread (&Mario::moveright, this);
      t[1].join();

 }
   else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))         //if superjump
   {
      t[1] =thread (&Mario::superjump, this);
      t[1].join();
      }
   else if (Keyboard::isKeyPressed(sf::Keyboard::Up))          //if jump
   {
      t[1] =thread (&Mario::moveup, this);
      t[1].join();
      }
      
   if (Keyboard::isKeyPressed( Keyboard::LControl))         //firing bullets
      isfiring=true;

   if(globalwidth == 500 || globalwidth == 850 || globalwidth == 1150 || globalwidth == 1350 || globalwidth == 1650 || globalwidth == 2000 ){
      t[2] =thread (&Mario::moveframe, this);            //moving frames
      t[2].join();
      }
      
   return 0;
}
 
 
int Mario :: setstep()           //fyunction that does proper setting of next step
{
   leftbound = rightbound;
    
   int other=0;
   int dojump = 0;
   if(anotherwaypossible[step]==1 && Keyboard::isKeyPressed(Keyboard::Up))   //if normal jump
      other++; 
   if(anotherwaypossible[step]==1)
      otherycounter++;
      
   if((anotherwaypossible[step]==-1 || anotherwaypossible[step]==2) && Keyboard::isKeyPressed(Keyboard::Space))  //if superjump
      dojump++;
   if(anotherwaypossible[step]==-1 || anotherwaypossible[step]==2){
      jumpcounter++;   
      jumpnextheight = jumpy[jumpcounter];
      }
            
   if(globalwidth >= rightbound && nextheight<heightlevel && heightlevel>=0 && !(Keyboard::isKeyPressed(Keyboard::Space)) && !(Keyboard::isKeyPressed(Keyboard::Up))  ){    //moving down oon step end
      sprite.move(0,abs(heightlevel-nextheight));  
      vertical=vertical+abs(heightlevel-nextheight);
      stepchange = 1; 
      }    
   step++;
   levelchange = 1;
   rightbound = plotx[step];
   prevheight = heightlevel;
   heightlevel = nextheight;
   nextheight = ploty[step];
     
   if(other){
      heightlevel = othery[otherycounter];   //setting variables accordingly
      if(anotherwaypossible[step]==1)
         nextheight = othery[otherycounter+1]; 
      }            
   if(dojump)
      heightlevel = jumpnextheight;
   
   return 0;
}            //end of setstep function



int Mario :: drawing(){
   window.clear();
   window.draw(gameframe);
   window.draw(sprite);
   window.draw(text5);
   window.draw(text);  
   window.display();
   return 0;
}




