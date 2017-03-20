#include"startgame.h"

int Mario :: moveright()
{
   int i;
   sprite.move(5,0);     //moving right
   if(globalwidth < 2350){
      gameframe.move(-20,0);        //moving background
      for(i=0;i<=29;i++)
         coin[i].move(-20,0);
      for(i=0;i<2;i++)
         monster[i].move(-20,0);
      }
   width += 5;
   width1=width1+25;       //setting some variables
   globalwidth += 5;
   stepchange = 0; 
   return 0;
}
            
int Mario :: moveup()         //moving up
{
   int i;
   if(rightbound-globalwidth>=15){      //can jump if distance in step left is >=15
      for(int c = 0; c <15; c++){
	      sprite.move(5, -10);
			window.draw(sprite);
			window.display();
			width += 1;
			width1=width1+5;
			globalwidth += 1;
			height += 2;
			vertical-=10;
		   }
      if(levelchange){                 //if on stepchange
		   sprite.move(0,150+prevheight-heightlevel);   //proper coming back to ground
		   height -= 150-heightlevel+prevheight;
		   vertical+=150+prevheight-heightlevel;
		   stepchange = 1;
		   }
      else{
         sprite.move(0,150);           //normal jump
	      vertical=vertical+150;
	      height -= 150;
	      stepchange = 0;
         }

       if(globalwidth < 2350){      //moving frame
      gameframe.move(-20,0);
      for(i=0;i<=29;i++)
         coin[i].move(-20,0);
      for(i=0;i<2;i++)
         monster[i].move(-20,0);
      }
      width1=width1+20;
      globalwidth += 5;
      stepchange = 0;
      
   }
   return 0;
}
  

int Mario :: superjump(){     //superjump - jumps for longer distance
   int i;
   if(rightbound-globalwidth>=30){   //check for left over distance to be >= 30
      for(int c = 0; c <15; c++){
	      sprite.move(15, -10);
	      window.draw(sprite);
			window.display();
			width += 3;                   //incrementing required variables
			width1=width1+15;
			globalwidth += 3;
			height += 2;
			vertical=vertical-10;
		   }
		      
      if(levelchange){      //if step changes
		   sprite.move(0,150+prevheight-heightlevel);
		   height -= 150-heightlevel+prevheight;
		   vertical+=150-heightlevel+prevheight;
		   stepchange = 1;
		   }
      else{
		   sprite.move(0,150);
		   height -= 150;
		   vertical=vertical+150;
		   stepchange = 0;
		   }
		      
      if(globalwidth>=rightbound){    //if on jumping step changes, setting that
		   step++;
		   levelchange = 1;
		   leftbound = rightbound;
         rightbound = plotx[step];
         prevheight = heightlevel;
         nextheight = ploty[step];
         }
      if(globalwidth < 2350){             //moving frame
         gameframe.move(-20,0);
         for(i=0;i<=29;i++)
            coin[i].move(-20,0);
         for(i=0;i<2;i++)
            monster[i].move(-20,0);
         }
      width1=width1+20;
      globalwidth += 5;
      stepchange = 0; 
      }
   return 0;
}                               


int Mario :: moveframe()               //shifting frame
{
   int i;
   int moveback = 500;                       //moving everything except mario back by 500
   for(i=0;i<=29;i++)
      coin[i].move(-moveback,0);
   for(i=0;i<2;i++)
      monster[i].move(-moveback,0);
   gameframe.move(-moveback,0); 
   sprite.move(-moveback, 0);
   width -= moveback;
   return 0;
}
