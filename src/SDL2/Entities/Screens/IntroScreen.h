#ifndef GOLDEN_PHOENIX_INTROSCREEN_H
#define GOLDEN_PHOENIX_INTROSCREEN_H

// Custom headers
#include "AnimatedTexture.h"
#include "InputsManager.h"
#include "AudioManager.h"

class IntroScreen : public GameEntity
{
private:
    SDL_Event _event;
    InputsManager* _inputs;

    const int FPS = 120;

    Texture* _text1;
    Texture* _text2;
    Texture* _text3;
    int _nbCaractereRead1,_nbCaractereRead2=0,_nbCaractereRead3=0;
    std::string _caractereRead1;
    std::string _caractereRead2;
    std::string _caractereRead3;
    const std::string text1 = "Jeune voyageur, penses-tu etre le meilleur aventurier ?";
    const std::string text2 = "Entre dans le chateau de Phénix et trouve l'oeuf du phénix !";
    const std::string text3 = "D'autre s'y sont aventurer mais ne sont jamais ressorti...";

public:

    explicit IntroScreen();

    ~IntroScreen() final;

    //! Process inputs and SDL2 events
    void ProcessEvents( SDL_Event* event );

    //! Update textures and game
    void Update() final;

    //! Render the buffer
    void Render();

    //! Return if quit
  //  bool GetQuit() const;

};


#endif
