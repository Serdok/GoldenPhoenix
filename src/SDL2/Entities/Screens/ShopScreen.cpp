//
// Created by serdok on 16/03/19.
//

#include "ShopScreen.h"

#include<iostream>

ShopScreen::ShopScreen( Castle* const castle, Translation* const trans )
        : _castle( castle ), _translation( trans ),
          Texture( "Marchand.png", true )
{
    _trader = new Trader( _castle->GetPlayer());

    _inputs = InputsManager::GetInstance();

    _money = new Texture( _translation->GetTranslation( 16 ) + " : ", "Roboto-Regular.ttf", 25, { 0, 0, 0 } );
    _money->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.8f, Graphics::SCREEN_HEIGHT*0.1f ));

    _crowbar = new Texture( "3 : " + _translation->GetTranslation( 5 ), "Roboto-Regular.ttf", 25, { 50, 50, 50 } );
    _crowbar->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.7f, Graphics::SCREEN_HEIGHT*0.46f ));

    _grapplingHook = new Texture( "1 : " + _translation->GetTranslation( 8 ), "Roboto-Regular.ttf", 25,
                                  { 50, 50, 50 } );
    _grapplingHook->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.24f, Graphics::SCREEN_HEIGHT*0.55f ));

    _torch = new Texture( "2 :  " + _translation->GetTranslation( 9 ), "Roboto-Regular.ttf", 25, { 50, 50, 50 } );
    _torch->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.45f, Graphics::SCREEN_HEIGHT*0.44f ));

    _lifePotion = new Texture( "4 :  " + _translation->GetTranslation( 10 ), "Roboto-Regular.ttf", 25, { 50, 50, 50 } );
    _lifePotion->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.85f, Graphics::SCREEN_HEIGHT*0.6f ));

    _price_Crowbar = new Texture( std::to_string( _trader->GetPrice( ObjectID::Crowbar )), "Roboto-Regular.ttf", 25,
                                  { 255, 255, 255 } );
    _price_Crowbar->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.62f, Graphics::SCREEN_HEIGHT*0.83f ));

    _price_GrapplingHook = new Texture( std::to_string( _trader->GetPrice( ObjectID::GrapplingHook )), "Roboto-Regular.ttf", 25,
                                        { 255, 255, 255 } );
    _price_GrapplingHook->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.25f, Graphics::SCREEN_HEIGHT*0.83f ));

    _price_Torch = new Texture( std::to_string( _trader->GetPrice( ObjectID::Torch )), "Roboto-Regular.ttf", 25, { 255, 255, 255 } );
    _price_Torch->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.45f, Graphics::SCREEN_HEIGHT*0.83f ));

    _price_LifePotion = new Texture( std::to_string( _trader->GetPrice( ObjectID::LifePotion )), "Roboto-Regular.ttf", 25,
                                     { 255, 255, 255 } );
    _price_LifePotion->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.8f, Graphics::SCREEN_HEIGHT*0.83f ));


}

ShopScreen::~ShopScreen()
{
    _castle = nullptr;
    delete _trader;
    _inputs = nullptr;

    delete _money;
    delete _price_Crowbar;
    delete _price_GrapplingHook;
    delete _price_Torch;
    delete _price_LifePotion;

    delete _crowbar;
    delete _grapplingHook;
    delete _torch;
    delete _lifePotion;

    delete _requires;

}

void ShopScreen::ProcessEvents( SDL_Event* event )
{
    std::string requires;
    delete _requires;
    _requires = nullptr;

    bool achat = false;
    if (_inputs->KeyPressed( SDL_SCANCODE_1 ))
    {
        if (_trader->Purchase( ObjectID::GrapplingHook ))
            requires = _translation->GetTranslation( 46 ) + _translation->GetTranslation( 8 );
        else
            requires = _translation->GetTranslation( 47 );
        achat = true;
    }
    else if (_inputs->KeyPressed( SDL_SCANCODE_2 ))
    {
        if (_trader->Purchase( ObjectID::Torch ))
            requires = _translation->GetTranslation( 46 ) + _translation->GetTranslation( 9 );
        else
            requires = _translation->GetTranslation( 47 );
        achat = true;
    }
    else if (_inputs->KeyPressed( SDL_SCANCODE_3 ))
    {
        if (_trader->Purchase( ObjectID::Crowbar ))
            requires = _translation->GetTranslation( 46 ) + _translation->GetTranslation( 5 );
        else
            requires = _translation->GetTranslation( 47 );
        achat = true;
    }
    else if (_inputs->KeyPressed( SDL_SCANCODE_4 ))
    {
        if (_trader->Purchase( ObjectID::LifePotion ))
            requires = _translation->GetTranslation( 46 ) + _translation->GetTranslation( 10 );
        else
            requires = _translation->GetTranslation( 47 );
        achat = true;
    }

    if (achat)
    {
        _requires = new Texture( requires, "Roboto-Regular.ttf", 24, { 255, 0, 0 } );
        _requires->SetPosition( Vector2i( Graphics::SCREEN_WIDTH/2, Graphics::SCREEN_HEIGHT*0.95 ));
    }

}

void ShopScreen::Update()
{
    //_castle->Update();
    _inputs->UnlockInputs();

    // Update the money
    delete _money;
    _money = new Texture(
            _translation->GetTranslation( 16 ) + " : " + std::to_string( _castle->GetPlayer()->GetMoney()),
            "Roboto-Regular.ttf", 25, { 0, 0, 0 } );
    _money->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.8f, Graphics::SCREEN_HEIGHT*0.1f ));
}

void ShopScreen::Render()
{
    // Render the background image
    Texture::Render();

    if (_requires)
        _requires->Render();

    _money->Render();
    _price_Crowbar->Render();
    _price_GrapplingHook->Render();
    _price_LifePotion->Render();
    _price_Torch->Render();
    _crowbar->Render();
    _grapplingHook->Render();
    _lifePotion->Render();
    _torch->Render();


}

void ShopScreen::SetTranslation( Translation* const translation )
{
    _translation = translation;

    delete _crowbar;
    delete _grapplingHook;
    delete _torch;
    delete _lifePotion;

    _crowbar = new Texture( "3 : " + _translation->GetTranslation( 5 ), "Roboto-Regular.ttf", 25, { 50, 50, 50 } );
    _crowbar->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.7f, Graphics::SCREEN_HEIGHT*0.46f ));

    _grapplingHook = new Texture( "1 : " + _translation->GetTranslation( 8 ),
                                  "Roboto-Regular.ttf",
                                  25,
                                  { 50, 50, 50 } );
    _grapplingHook->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.24f, Graphics::SCREEN_HEIGHT*0.55f ));

    _torch = new Texture( "2 :  " + _translation->GetTranslation( 9 ), "Roboto-Regular.ttf", 25, { 50, 50, 50 } );
    _torch->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.45f, Graphics::SCREEN_HEIGHT*0.44f ));

    _lifePotion = new Texture( "4 :  " + _translation->GetTranslation( 10 ), "Roboto-Regular.ttf", 25, { 50, 50, 50 } );
    _lifePotion->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.85f, Graphics::SCREEN_HEIGHT*0.6f ));

}