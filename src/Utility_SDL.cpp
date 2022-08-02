// Standard library
#include <iostream>
#include <fstream>
// #include <SDL_ttf.h>

//Utility file
#include "Utility_SDL.h"
#include "Food.h"
#include "Wall.h"


void SDL_Utility::DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
   const int32_t diameter = (radius * 2);

   int32_t x = (radius - 1);
   int32_t y = 0;
   int32_t tx = 1;
   int32_t ty = 1;
   int32_t error = (tx - diameter);

   while (x >= y)
   {
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }

      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }
}

void SDL_Utility::DrawCircleF(SDL_Renderer* renderer, float centreX, float centreY, float radius){
   const float diameter = (radius * 2);

   float x = (radius - 1);
   float y = 0;
   float tx = 1;
   float ty = 1;
   float error = (tx - diameter);

   while (x >= y)
   {
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPointF(renderer, centreX + x, centreY - y);
      SDL_RenderDrawPointF(renderer, centreX + x, centreY + y);
      SDL_RenderDrawPointF(renderer, centreX - x, centreY - y);
      SDL_RenderDrawPointF(renderer, centreX - x, centreY + y);
      SDL_RenderDrawPointF(renderer, centreX + y, centreY - x);
      SDL_RenderDrawPointF(renderer, centreX + y, centreY + x);
      SDL_RenderDrawPointF(renderer, centreX - y, centreY - x);
      SDL_RenderDrawPointF(renderer, centreX - y, centreY + x);

      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }

      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }
}

void SDL_Utility::DrawRing(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius, int32_t width){
   for(int i = radius; i <= radius + width; i++){
      SDL_Utility::DrawCircle(renderer, centreX, centreY, i);
   }
}

void SDL_Utility::DrawRingF(SDL_Renderer* renderer, float centreX, float centreY, float radius, float width){
   // Add step parameter for drawing?
   for(float i = radius; i <= radius + width; i += 0.1){
      SDL_Utility::DrawCircleF(renderer, centreX, centreY, i);
   }
}


void SDL_Utility::DrawFood(SDL_Renderer* renderer, Arena2D* arena, double radius){

   if(arena->GetFood() != nullptr){
      Vector2d<double> room_center = arena->GetRoomCenter(arena->GetFood()->GetRoom());
      SDL_SetRenderDrawColor(renderer, 255, 0, 125, SDL_ALPHA_OPAQUE);
      SDL_Utility::DrawCircleF(renderer,room_center.x, room_center.y, radius);
/* 
      //this opens a font style and sets a size
      TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24);

      // this is the color in rgb format,
      // maxing out all would give you the color white,
      // and it will be your text's color
      SDL_Color White = {255, 255, 255};

      // as TTF_RenderText_Solid could only be used on
      // SDL_Surface then you have to create the surface first
      SDL_Surface* surfaceMessage =
      TTF_RenderText_Solid(Sans, "put your text here", White); 

      // now you can convert it into a texture
      SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

      SDL_Rect Message_rect; //create a rect
      Message_rect.x = 0;  //controls the rect's x coordinate 
      Message_rect.y = 0; // controls the rect's y coordinte
      Message_rect.w = 100; // controls the width of the rect
      Message_rect.h = 100; // controls the height of the rect

      // (0,0) is on the top left of the window/screen,
      // think a rect as the text's box,
      // that way it would be very simple to understand

      // Now since it's a texture, you have to put RenderCopy
      // in your game loop area, the area where the whole code executes

      // you put the renderer's name first, the Message,
      // the crop size (you can ignore this if you don't want
      // to dabble with cropping), and the rect which is the size
      // and coordinate of your texture
      SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

      // Don't forget to free your surface and texture
      SDL_FreeSurface(surfaceMessage);
      SDL_DestroyTexture(Message);
 */
   }

}

void SDL_Utility::DrawArena(SDL_Renderer* renderer, Arena2D* arena){
   
   // Outer ring wall
   double width = 1.0;
   if(arena->GetNbWalls() != 0){
      width = arena->GetWalls()[0].GetWidth();
   }

   SDL_Utility::DrawCircleF(renderer, arena->GetCenter().x, arena->GetCenter().y, arena->GetRadius());
   SDL_Utility::DrawCircleF(renderer, arena->GetCenter().x, arena->GetCenter().y, arena->GetRadius() + width);

   // Wall drawing
   for(int i = 0; i<arena->GetNbWalls(); i++){
      // Use RenderDrawLines as we need tilted shapes
      // Wall coordinates
      std::vector<Vector2d<double> > coords = arena->GetWalls()[i].GetCoord();
      // Set color to white
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

      for(int j = 0; j < arena->GetWalls()[i].GetNbSides(); j++){
         
         if(j+1 == arena->GetWalls()[i].GetNbSides()){
            SDL_RenderDrawLineF(renderer, coords[0].x, coords[0].y, coords[j].x, coords[j].y);
         }
         
         else{
            SDL_RenderDrawLineF(renderer, coords[j].x, coords[j].y, coords[j+1].x, coords[j+1].y);
            }

      }

      // Draw entrances
      // Set color to green
      SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);      
      for(int j=0; j<arena->GetWalls()[i].GetNbEnts(); j++){
         // Entrance coordinates
         std::vector<Vector2d<double> > coords_e = arena->GetWalls()[i].GetEntrances()[j].GetCoord();

         if(arena->GetWalls()[i].GetEntrances()[j].IsFake()){SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);}

         if(!arena->GetWalls()[i].GetEntrances()[j].IsFake()){SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);}


         for(int k = 0; k < arena->GetWalls()[i].GetNbSides(); k++){

            if(k+1 == arena->GetWalls()[i].GetNbSides()){
               SDL_RenderDrawLineF(renderer, coords_e[0].x, coords_e[0].y, coords_e[k].x, coords_e[k].y);
            }
            
            else{
               SDL_RenderDrawLineF(renderer, coords_e[k].x, coords_e[k].y, coords_e[k+1].x, coords_e[k+1].y);
               }
         }
   
      } 
   }

   // Draw Food object
   SDL_Utility::DrawFood(renderer, arena);
}

void SDL_Utility::DrawAgent(SDL_Renderer* renderer, Fly2D* fly){
   Vector2d<double> orient = fly->GetPosition() - fly->GetVelocity();
   orient /= EuclideanNorm(orient);

   double radius = 10.0;
   orient *= radius;
   SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE); 
   SDL_Utility::DrawCircleF(renderer, fly->GetPosition().x, fly->GetPosition().y, radius);
   // SDL_RenderDrawLineF(renderer, fly->GetPosition().x, fly->GetPosition().y, fly->GetPosition().x + radius * cos(fly->GetAngle()), fly->GetPosition().y + radius * sin(fly->GetAngle()));
   // SDL_RenderDrawLineF(renderer, fly->GetPosition().x, fly->GetPosition().y, fly->GetPosition().x + orient.x, fly->GetPosition().y + orient.y);

   // Draw Fres
   SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE); 
   if(EuclideanNorm(fly->GetFres()) != 0){
      SDL_RenderDrawLineF(renderer, fly->GetPosition().x, fly->GetPosition().y, fly->GetPosition().x + fly->GetFres().x * 10 / EuclideanNorm(fly->GetFres()), fly->GetPosition().y + fly->GetFres().y * 10/ EuclideanNorm(fly->GetFres()));
   }

   // Draw velocity
   SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);      

   Vector2d<double> v(fly->GetVelocity());
   // v *= 5;
   SDL_RenderDrawLineF(renderer, fly->GetPosition().x, fly->GetPosition().y, fly->GetPosition().x + v.x, fly->GetPosition().y + v.y);

}
