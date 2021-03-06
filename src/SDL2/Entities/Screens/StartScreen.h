//
// Created by serdok on 05/03/19.
//

#ifndef GOLDEN_PHOENIX_STARTSCREEN_H
#define GOLDEN_PHOENIX_STARTSCREEN_H

// Custom headers
#include "Castle.h"
#include "Translation.h"

#include "AnimatedTexture.h"
#include "InputsManager.h"


//! Class rendering the start screen of the game
class StartScreen : public Texture
{
private:
    Castle* _castle;

    Translation* _translation;

    InputsManager* _inputs;

    Texture* _startText;
    Texture* _shopText;
    Texture* _tomb;
    Texture* _reset;


public:
    //! Load the start screen with the data from a Castle
    explicit StartScreen( Castle* castle, Translation * trans );

    //! Free resources without deleting the Castle
    ~StartScreen() final;

    void SetTranslation( Translation* const translation );

    //! Process inputs and SDL2 events
    void ProcessEvents( SDL_Event* event );

    //! Update textures and game
    void Update() final;

    //! Render the buffer
    void Render() final;
};


#endif //GOLDEN_PHOENIX_STARTSCREEN_H
