#include "PauseScreen.h"

#include <iostream>

PauseScreen::PauseScreen()
{
	_background = Graphics::GetInstance();
	_background->SetBackgroundColor(0, 0, 0);
	_text = new Texture("PAUSE","Pasatona.ttf", 60, {255, 255, 255});
	_text->SetPosition(Vector2f( Graphics::SCREEN_WIDTH*0.5f, Graphics::SCREEN_HEIGHT*0.1f));

}

PauseScreen::~PauseScreen()
{
	_background = nullptr;
	delete _text;
}

void PauseScreen::ProcessEvents(SDL_Event* event)
{

}

void PauseScreen::Update()
{

}

void PauseScreen::Render()
{
	_text->Render();
}