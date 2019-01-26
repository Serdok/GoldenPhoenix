//
// Created by serdok on 24/01/19.
//

#ifndef MYPROJECT_GAME_HPP
#define MYPROJECT_GAME_HPP

// Custom headers
#include "Exceptions.hpp"
#include "Cleanup.hpp"

// SDL2 headers
#include "SDL_image.h"

// C++ headers
#include <cassert>
#include <iostream>


//! Structure containing useful window info
struct SDL_WindowInfo
{
    std::string title; ///< Title of the window
    int x; ///< Position of the window
    int y; ///< Position of the window
    int width; ///< Size of the window
    int height; ///< Size of the window
    Uint32 flags; ///< Flags of the window
};

//! Game class
class Game
{
private:
    static SDL_Window* _window;
    static SDL_WindowInfo _windowInfo;
    static SDL_Renderer* _renderer;
    static SDL_RendererInfo _rendererInfo;
    static SDL_Event _event;
    static SDL_Rect _camera;
    bool _running;


public:
    Game(); ///< Initialize game graphics engine.
    ~Game();

    /**
     * Initialize the game components
     * @param title [in] The window title
     * @param width [in] The window width
     * @param height [in] The window height
     * @param fullscreen [in] If the game should run on fullscreen
     */
    void Init( const std::string& title = std::string(), int width = 800, int height = 600, bool fullscreen = false );

    void Run(); ///< Run the game. Must be called after Init().

    static SDL_WindowInfo GetWindowInfo(); ///< Getter for the window info.
    static SDL_Renderer* GetRenderer(); ///< Getter for the renderer.
    static SDL_RendererInfo GetRendererInfo(); ///< Getter for the renderer info.
    static SDL_Event GetEvents(); ///< Getter for the game events.
    static SDL_Rect GetCamera(); ///< Getter for the game camera.

private:
    void InitSDL2(); // Initialize SDL2
    void InitSDL2_image(); // Initialize SDL2_image
    void InitSDL2_ttf(); // Initialize SDL2_ttf
    void InitSDL2_mixer(); // Initialize SDL2_mixer

    void InitObjects(); // Initialize game objects

    bool Running() const; // Getter for the running state

    void ProcessEvents(); // Process game events
    void Update(); // Update game objects
    void Render(); // Render game objects

    void Clean(); // Clean game resources
};



#endif //MYPROJECT_GAME_HPP
