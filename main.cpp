#include"intialize.h"

Mario mar;     //mario object the player

int main(){
  
    int w1,w2,w3,w4;
    w1=1;
    w2=0; 
    w3=0;
    w4=0; 
    
   mar.initialise();   //function that initialises
   int i,j;
   Clock clock;
   thread th;
   
   while (mar.window.isOpen()){
    
      sf::Event event;
      
      if(w1==1){      //displays main page - menu

         if(Keyboard::isKeyPressed(Keyboard::Num1)){   //going to startgame
           
            w1=0;
            w2=1;
            timebefore=clock.getElapsedTime().asSeconds();
            mar.window.clear();
            }

         if(Keyboard::isKeyPressed(Keyboard::Num2)){   //going to instructions
            w1=0;
            w3=1;
            mar.window.clear();
            }
  
        if(Keyboard::isKeyPressed(Keyboard::Num3)){  //going to credits
            w4=1;
            w1=0;
            mar.window.clear();
            }
         mar.startdraw();

         if (Keyboard::isKeyPressed(Keyboard::Escape))    //close window
            mar.window.close();

         while (mar.window.pollEvent(event)){            //closes window
            if (event.type == Event::Closed)
               mar.window.close();
         }
      }
      
      if(w3==1){                       //in instructions
         mar.window.clear();
         mar.window.draw(mar.ins);
         mar.window.display();
          
         if (Keyboard::isKeyPressed(Keyboard::Escape))
            mar.window.close();
        
         if (Keyboard::isKeyPressed(Keyboard::BackSpace)){  //coming back
            w1=1;
            w3=0;
            w2=0;
         }

         while (mar.window.pollEvent(event)){  //closing window
            if (event.type == Event::Closed)
               mar.window.close();
         }
      }

     if(w4==1)          //credits
{    
      mar.window.clear();
      mar.window.draw(mar.credit);
      mar.window.display();
          
      
       if (Keyboard::isKeyPressed(Keyboard::Escape))
            mar.window.close();
        
         if (Keyboard::isKeyPressed(Keyboard::BackSpace)){   //coming back
            w1=1;
            w4=0;
         }

      
      while (mar.window.pollEvent(event)){
            if (event.type == Event::Closed)
               mar.window.close();
         }
}

      if(w2==1)            //start actual game
         mar.startgame();
   
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
         mar.window.close();
   }
  //cout<<mar.globalwidth<<"and"<<mar.coinswon;
   return 0;
}   //end of program
