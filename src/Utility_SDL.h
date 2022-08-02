#ifndef UTILITY_SDL_H
#define UTILITY_SDL_H

// Third party
#if defined(WIN32) || defined(_WIN32)
    #include <SDL2/SDL.h>
#elif __APPLE__
    #include <SDL.h>
#endif
// Project
#include "Rectangle.h"
#include "Arena2D.h"
#include "Fly2D.h"
#include "Food.h"
#include "Simulation2D.h"

// Utility file header
namespace SDL_Utility {
    

    /**
     * @brief Midpoint Circle Algorithm SDL implementation
     * 
     * @param renderer SDL renderer ptr target for drawing
     * @param centreX x coordinate of center 
     * @param centreY y coordinate of center
     * @param radius radius of circle
     */
    void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius);

    /**
     * @brief Midpoint Circle Algorithm SDL float implementation
     * 
     * @param renderer SDL renderer ptr target for drawing
     * @param centreX x coordinate of center 
     * @param centreY y coordinate of center
     * @param radius radius of circle
     */
    void DrawCircleF(SDL_Renderer* renderer, float centreX, float centreY, float radius);

    /**
     * @brief Draw a ring on renderer
     * 
     * @param renderer SDL renderer ptr target for drawing
     * @param centreX x coordinate of center 
     * @param centreY y coordinate of center
     * @param radius radius of circle
     * @param width width of ring
     */
    void DrawRing(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius, int32_t width);

    /**
     * @brief Draw a ring on renderer usning floats
     * 
     * @param renderer SDL renderer ptr target for drawing
     * @param centreX x coordinate of center 
     * @param centreY y coordinate of center
     * @param radius radius of circle
     * @param width width of ring
     */
    void DrawRingF(SDL_Renderer* renderer, float centreX, float centreY, float radius, float width);

    /**
     * @brief Draw Arena2D object on SDL renderer
     * 
     * @param renderer SDL renderer
     * @param arena Arena to plot
     */
    void DrawArena(SDL_Renderer* renderer, Arena2D* arena);

    /**
     * @brief Draw agent object on SDL renderer
     * 
     * @param renderer ptr to SDL renderer
     * @param fly ptr to agent in the sim
     */
    void DrawAgent(SDL_Renderer* renderer, Fly2D* fly);

    /**
     * @brief Draw food object on SDL renderer
     * 
     * @param renderer SDL renderer
     * @param arena arena from which food object is extracted, draw nothing if nullptr
     * @param radius purely visual element to draw food
     */
    void DrawFood(SDL_Renderer* renderer, Arena2D* arena, double radius = 50.0);
} 

#endif