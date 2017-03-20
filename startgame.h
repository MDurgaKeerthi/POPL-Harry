#include"marioclass.h"      //including header file

int Mario :: startdraw(){          //function to draw various texts and fonts 
   window.clear();
   window.draw(frame);
   window.draw(text1);
   window.draw(text2);
   window.draw(text3);
   window.display();
   return 0;
}

int Mario :: scoreboard(){      //function for scoreboard
   if(coinswon>=10) 
      score1.setString(char(48+(coinswon/10)));
   score.setString(char(48+(coinswon%10))); 
   return 0;
}

int mon1=0;
int flag_bull[10];
int a=0;
int gone[2]={1,1};

int move_monster()        //functin to move monster
{
     int i;
     mon1++;
   if(mon1%10==0)
{
      a++;
      
      for(i=0;i<2;i++){
         if(dis[i]==mon_low[i])     //if lower bound then move right
            flag1[i]=1;
         if(dis[i]==mon_up[i])       //if upper bound then move left
            flag1[i]=-1;

         if(flag1[i]==1){
            monster[i].move(5,0);       //moving the monster by a distance of 5                   
            dis[i]=dis[i]+5;
            }

         else{
            monster[i].move(-5,0);
            dis[i]=dis[i]-5;
         }
      }
   }


return 0;


}
   
int Mario :: startgame()     //function to start the game 
{
   
   int i, j,timetoprint;
   Event event;
   int flag=0;
   
   thread th1,th2,th3;
   th2=thread(move_monster);    //creating a thread to move the monster

   if (Keyboard::isKeyPressed(Keyboard::Escape))    //if escape is pressed then close the window
      window.close();

   while (window.pollEvent(event)){
      if (event.type == Event::KeyPressed){
         th1 = thread(&Mario::movemario, this);      //thread to move mario
         th1.join();
         }
      if (event.type == Event::Closed)
         window.close();
      }

th2.join();

   if(isfiring==true)    //when bullet is fired
{
      RectangleShape new_bullet;
      new_bullet.setSize(Vector2f(20,5));
      new_bullet.setFillColor(Color::Yellow);
      new_bullet.setPosition(sprite.getPosition().x+50,sprite.getPosition().y+20);   //setting the position of the bullet
      bullet[bulletcount]=new_bullet;
      flag_bull[bulletcount]=1;
      bulletcount++;
      isfiring=false;    //make is isfiring false
   }

   for(i=0;i<bulletcount;i++)
   {
      bullet[i].move(5,0);
   }

   timetoprint = clock.getElapsedTime().asSeconds()-timebefore;   //timer 
   if(timetoprint>=10) 
      text5.setString(char(48+(timetoprint/10)));     //setting the string for the timer
   else   
      text5.setString("0");
   text.setString(char(48+(timetoprint%10))); 

   for(i=0;i<=29;i++)
   {
      if(visible[i] && (width1>=x[i]-50) && (vertical>=y[i]-50 && vertical<=y[i]+50)){    //if mario reaches position of coin then the coin should dissapear
         visible[i]=0;
         coinswon++;
         if(i==10 || i==18 || i==29)
            coinswon++;
         th3=thread(&Mario::scoreboard, this);      //thread for scoreboard
         th3.join();
      }
   }

     for(i=0;i<2;i++)
{
   
    if((sprite.getPosition().x>=monster[i].getPosition().x+100)  && (vertical>=mon_ver[i]-50) && gone[i]==1 && step!=10)   //if mario hits the monster the game is over
{
     isgameover=-1;                                      //game over is -1
     break;
}

    if(step==10)
    gone[1]=0;


}


  for(i=0;i<2;i++)
  {
          if(isfiring==false)     //bullets for killing the monster
{
         if(((abs(bullet[bulletcount-1].getPosition().x-monster[i].getPosition().x))<=mon_up[i]-mon_low[i]) && flag_bull[bulletcount-1]==1 && vis[i]==1 && (vertical>=mon_ver[i]+40))
{
            vis[i]=0;
            flag_bull[bulletcount-1]=0;                //if the bullet hits the monster the monster should disappear
            gone[i]=0;
            break;
 }
         else
         flag_bull[bulletcount-1]=0;
}



}  

   if(timetoprint>70)            //if time is up i.e timer is 70    
  {
       isgameover=-1;
  }

  if(globalwidth>=2325)        //gamewin when he reaches the castle
{
    isgamewin=-1;
}


   if(timetoprint<=70 && isgameover!=-1 && isgamewin != -1){

      window.clear();
      window.draw(bigframe);                    //drawing mario,outerbackground and the game background
      window.draw(gameframe);
      window.draw(sprite);

      for(i=0;i<=29;i++){
         if(i!=10 && i!=18){
            if(visible[i]==1)                            //drawing the coins
               window.draw(coin[i]);
            }
         }

      if(visible[10] && a%2==0)
          window.draw(coin[10]);                                       //drawing special coins and monsters

      if(visible[10] && a%2==1)
           window.draw(spcoin[0]);

      if(visible[18] && a%2==0)
          window.draw(coin[18]);

      if(visible[18] && a%2==1)
           window.draw(spcoin[1]);

      if(visible[29] && a%2==0)
          window.draw(coin[29]);

      if(visible[29] && a%2==1)
           window.draw(spcoin[2]);

      for(i=0;i<2;i++){
         if(vis[i]==1)
            window.draw(monster[i]);
         }
        
      for(i=0;i<bullet.size();i++)                   //drawing the fired bullets
         window.draw(bullet[i]);

      window.draw(timename);
      window.draw(text5);
      window.draw(text); 
      window.draw(scorename);
      window.draw(score1);
      window.draw(score);
      window.display();
      }

   if(isgameover==-1){                      //if game over display gameover screen
      window.clear();
      window.draw(f1);
      window.display();
      }
      
   if(isgamewin==-1){                      //if game is won then dispaly game won
      window.clear();
      window.draw(f2);
      window.display();
      }   
      

   return 0;
}


