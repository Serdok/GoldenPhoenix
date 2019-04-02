#ifndef GOLDEN_PHOENIX_PAUSESCREEN_H
#define GOLDEN_PHOENIX_PAUSESCREEN_H

#include "Texture.h"
#include "Translation.h"
#include "Graphics.h"

class PauseScreen : public GameEntity
{
	private:
		Texture* _text;
		Texture* _textLang;
        Translation* _translation;

	public:

    explicit PauseScreen(Translation* trans);

    ~PauseScreen() final;

    //! Process inputs and SDL2 events
    void ProcessEvents( SDL_Event* event );

    //! Update textures and game
    void Update() final;

    //! Render the buffer
    void Render();
};


#endif
