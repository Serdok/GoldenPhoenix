#include "InventoryScreen.h"

InventoryScreen::InventoryScreen( Castle* const castle )
: _castle( castle ), GameEntity()
{

}

InventoryScreen::~InventoryScreen()
{
    _castle = nullptr;
}

void InventoryScreen::ProcessEvents( SDL_Event* event )
{

}

void InventoryScreen::Update()
{
    _castle->Update();
}

void InventoryScreen::Render()
{
	Graphics::GetInstance()->SetBackgroundColor(217,207,141);
}