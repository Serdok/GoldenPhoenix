#ifndef GOLDEN_PHOENIX_EndScreen_H
#define GOLDEN_PHOENIX_EndScreen_H

// Custom headers
#include "Castle.h"

#include "AnimatedTexture.h"
#include "InputsManager.h"
#include "AudioManager.h"


class EndScreen : public GameEntity
{
private:

    Castle* _castle;

    InputsManager* _inputs;

    int _temps = 0;

    bool _quit = false;
    Texture* Text;
    int stepAnimFirst = 0;
        
    const std::string text1 = "Bravo vous etes venu à bout de ce labyrinthe...";
    const std::string text2 = "Vous avez finis avec un score : ";
    const std::string text3 = "Mais seriez vous capable de faire mieux....";
    const std::string text4 = "Car après tout vous etes mort ";


    static const int NBTEXTINSCREEN = 10;

    std::array< Texture*, NBTEXTINSCREEN > _textscroll;

    static const int MAXSCROLL = 22;

    std::string textScroll[MAXSCROLL];

    int StepScroll = 0;

    bool _animCredit = false;

public:

    explicit EndScreen(Castle* castle);

    ~EndScreen() final;

    //! Process inputs and SDL2 events
    void ProcessEvents( SDL_Event* event );

    //! Update textures and game
    void Update() final;

    //! Render the buffer
    void Render();

    //! Return if quit
    bool GetQuit() const;

};


#endif
