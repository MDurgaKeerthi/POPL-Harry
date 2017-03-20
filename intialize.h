#include "moving.h"

int Mario :: initialise()              //function for initializing variables
{
   array1 = VideoMode::getFullscreenModes();
   window.create(VideoMode(array1[0].width, array1[0].height), "SFML Window", Style::Fullscreen);
   mode.width =  window.getSize().x;
   mode.height = window.getSize().y;
   
   if(!texture.loadFromFile("mario.png")){
      cout<<"error1";                                  //initializing texture for mario
      return 0;
      }
   if(!background3.loadFromFile("final.png")){
      std::cout<<"error";                                 //initializing texture for game background          
      return 0;
      }
   if(!font.loadFromFile("LUMOS.TTF")){
      std::cout<<"error2";                                    //initializing font
      return 0;
      }  
   if(!background1.loadFromFile("start.jpg")){
      cout<<"Error in loading file"<<endl;                    //initializing texture for start page
      return 0;
   }
   if(!gameover.loadFromFile("gameover.jpg")){
      cout<<"Error in loading file"<<endl;                 //initializing texture for gameover
      return 0;
   }
   if(!background2.loadFromFile("back1.jpg")){
      std::cout<<"error";                                     //initializing texture for background
      return 0;
   }
   if(!ins_page.loadFromFile("instructions.png")){
    cout<<"error";                                                   //initializing texture for instructions        
    return 0;
   } 
   if(!co.loadFromFile("coin.png")){
    cout<<"error";
    return 0;                                                            //initializing texture for coin
   }
   if(!spco.loadFromFile("spcoin.png")){
    cout<<"error";
    return 0;                                                             //initializing texture for special coin
   }
   if(!enemy.loadFromFile("enemy.png")){
      cout<<"error";                                                        //initializing texture for monster
      return 0;
   }
   if(!gamewin.loadFromFile("gamewin.jpg"))
{
      cout<<"Error in loading file"<<endl;                        //initializing texture for gamewin
      return 0;
}
    if(!cre_page.loadFromFile("credits.png"))
{
      cout<<"Error in loading file"<<endl;                      //initializing texture for credits
      return 0;
}


   frame.setTexture(background1);
   f1.setTexture(gameover);
   f2.setTexture(gamewin);
   //f2.move(50,50);
   bigframe.setScale(sf::Vector2f(5.f, 2.f));  
   bigframe.setTexture(background2);                                       //setting textures to mario
   ins.setTexture(ins_page);                                                //setting textures to gamebackground,background,gameover,gamewin

   credit.setTexture(cre_page);
   credit.setScale(sf::Vector2f(1.f, 1.f)); 
   credit.move(150,0);
   
   baseheight = 427;
   sprite.setSize(sf::Vector2f(100,100));
   sprite.setTexture(&texture);
   sprite.move(0,baseheight);                       //setting position of mario
   
   gameframe.setScale(Vector2f(1.5f, 1.25f));  
   gameframe.setTexture(background3);                     //setting background for game frame
   gameframe.move(0,50);
   
   int i;
   for(i=0;i<=29;i++){
      if(i!=10 && i!=18 && i!=29){
          coin[i].setRadius(30.f);
          coin[i].setTexture(&co);                            //setting size,texture and position of coins
          coin[i].setPosition(x[i],y[i]);
      }
      else{
          coin[i].setRadius(40.f);
          coin[i].setTexture(&spco);
          coin[i].setPosition(x[i],y[i]);
      }
   }

   for(i=0;i<3;i++){
      spcoin[i].setRadius(30.f);
      spcoin[i].setTexture(&spco);                                        //setting size,texture and position of special coins
   }

   spcoin[0].setPosition(x[10]+10,y[10]+10);
   spcoin[1].setPosition(x[18]+10,y[18]+10);
   spcoin[2].setPosition(x[29]+10,y[29]+10);

   for(i=0;i<2;i++){
      monster[i].setRadius(60.f);
      monster[i].setTexture(&enemy);
   }

   monster[0].setPosition(1600,495);
   monster[1].setPosition(2800,410);
   
   text1.setFont(font);
   text1.setString("1:START GAME");
   text1.setCharacterSize(50);
   text1.setColor(Color::Cyan);                                         //initializing text for start game
   text1.setStyle(Text::Bold);
   text1.move(9*mode.width/28, (10*mode.height)/40);
   
   text2.setFont(font);
   text2.setString("2:INSTRUCTIONS");
   text2.setCharacterSize(50);                                           //initializing text for instructions
   text2.setColor(Color::Cyan);
   text2.setStyle(Text::Bold);
   text2.move(9*mode.width/28, (15*mode.height)/40);

   text3.setFont(font);
   text3.setString("3:CREDITS");
   text3.setCharacterSize(50);
   text3.setColor(Color::Cyan);                                            //initializing text for credits
   text3.setStyle(Text::Bold);
   text3.move(9*mode.width/28, 20*mode.height/40);
   
   timename.setFont(font);
   timename.setString("TIME:");
   timename.setCharacterSize(40);
   timename.setColor(Color::Cyan);                                    //initializing text for time
   timename.setStyle(Text::Bold);
   timename.move(23*mode.width/28, 1*mode.height/40);
   text.setFont(font);
   text.setCharacterSize(40);
   text.setColor(Color::Red);
   text.move(27*mode.width/28, 1*mode.height/40);
   text5.setFont(font);
   text5.setCharacterSize(40);
   text5.setColor(Color::Red);
   text5.move(27*mode.width/28-37, 1*mode.height/40);    
   
   scorename.setFont(font);
   scorename.setString("Score: ");
   scorename.setCharacterSize(40);
   scorename.setColor(Color::Cyan);                                      //initializing text for score
   scorename.setStyle(Text::Bold);
   scorename.move(20*mode.width/28-100, 1*mode.height/40);
   score.setFont(font);
   score.setCharacterSize(40);
   score.setColor(Color::Blue);
   score.move(21*mode.width/27-10, 1*mode.height/40);
   score.setString("0");
   score1.setFont(font);
   score1.setCharacterSize(40);
   score1.setColor(Color::Blue);
   score1.move(21*mode.width/27-47, 1*mode.height/40);
   score1.setString("0");
   
   
   coinswon=0;
   vertical=465;
   width1=100;                                            //initializing the various variables required
   width = 0;
   height = 0;
   globalwidth = 0;
   allowright=0;
   leftbound=0;
   rightbound = plotx[0];
   heightlevel=0;
   step=0;
   stepchange = 0;
   nextheight = ploty[0];
   prevheight=0;
   levelchange=0;
   isgameover=0;
   isgamewin=0;
   bulletcount = 0;
   isfiring = false;
   otherycounter = -1;
   jumpcounter = -1;
   jumpnextheight =0;
   return 0;
}   
