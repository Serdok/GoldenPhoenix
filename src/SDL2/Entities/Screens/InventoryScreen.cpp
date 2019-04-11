#include "InventoryScreen.h"

InventoryScreen::InventoryScreen( Castle* const castle, Translation* const trans ) : _castle( castle ), _translation(trans), GameEntity()
{
    _inputs = InputsManager::GetInstance();

    UpdateLanguage();
}

InventoryScreen::~InventoryScreen()
{
    _castle = nullptr;
    _inputs = nullptr;

    for (auto texture : _textures)
        delete texture.second;
    _textures.clear();

    for (auto& name : _names)
        delete name.second;
    _names.clear();

    for (auto& number : _numbers)
        delete number.second;
    _numbers.clear();

    for (auto& description : _descriptions)
        delete description.second;
    _descriptions.clear();

    delete _score;
    delete _money;
}

void InventoryScreen::ProcessEvents( SDL_Event* event )
{

}

void InventoryScreen::Update()
{
    _castle->Update();
    UpdateLanguage();
    ActivateItems();
    SelectItem();
}

void InventoryScreen::Render()
{
    _score->Render();
    _money->Render();

    for (const auto& texture : _textures)
        texture.second->Render();

    for (const auto& name : _names)
        name.second->Render();

    for (const auto& number : _numbers)
        if (number.second->GetActive())
            number.second->Render();

    for (const auto& description : _descriptions)
        if (description.second->GetActive())
            description.second->Render();
}

void InventoryScreen::SetTranslation( Translation* const translation )
{
    _translation = translation;
}

void InventoryScreen::ActivateItems()
{
    for (auto& texture : _textures)
        texture.second->SetAlpha( 50 );
    for (auto& name : _names)
        name.second->SetAlpha( 50 );
    for (auto& number : _numbers)
    {
        number.second->SetAlpha( 50 );
        number.second->SetActive( false );
    }
    for (auto& description : _descriptions)
        description.second->SetActive( false );



    for (int i=0 ; i<_castle->GetPlayer()->GetItems().size() ; ++i)
    {
        const ItemStack& item = _castle->GetPlayer()->GetItems()[ i ];
        const Object& obj = item.GetObject();
        if (obj.GetID() == ObjectID::Nothing)
            continue;

        _textures.at( obj.GetID() )->SetAlpha( 255 );
        _names.at( obj.GetID() )->SetAlpha( 255 );
        UpdateNumbers( item );
    }
}

void InventoryScreen::SelectItem()
{
    if (_inputs->KeyPressed( SDL_SCANCODE_RIGHT ) || _inputs->KeyPressed( SDL_SCANCODE_D )) ++_selected;
    if (_inputs->KeyPressed( SDL_SCANCODE_LEFT ) || _inputs->KeyPressed( SDL_SCANCODE_A ) ) --_selected;

    if (_selected <= ObjectID::Nothing)  _selected = ObjectID::Egg;
    if (_selected >= ObjectID::TOTAL)   _selected = ObjectID::TOTAL-1;

    std::cout << _selected << std::endl;

    _descriptions.at( (ObjectID) _selected )->SetActive( true );

    if (_inputs->KeyPressed( SDL_SCANCODE_RETURN ))
    {
        if (_names.at( (ObjectID) _selected )->GetActive())
        {
            const auto& items = _castle->GetPlayer()->GetItems();
            for (int i = 0 ; i < items.size() ; ++i)
                switch (_selected)
                {
                    case ObjectID::Crowbar:
                    case ObjectID::IronKey:
                    case ObjectID::GoldKey:
                    case ObjectID::GrapplingHook:
                    case ObjectID::Torch:
                    case ObjectID::LifePotion:
                        if (items[ i ].GetObject().GetID() == (ObjectID) _selected)
                        {
                            _castle->GetPlayer()->SetHeldItem( i );
                            std::cout << "Selected " << _castle->GetPlayer()->GetHeldItem().GetObject().name << std::endl;
                        }
                        break;
                    default:
                        break;
                }
        }
    }
}

void InventoryScreen::UpdateNumbers( const ItemStack& item )
{
    _numbers[ item.GetObject().GetID() ] = new Texture( "x " + std::to_string( item.GetAmount() ), "Roboto-Regular.ttf", 17, { 0, 0, 0 } );
    _numbers.at( item.GetObject().GetID() )->SetPosition( _names.at( item.GetObject().GetID() )->GetPosition() + Vector2i( 0, _names.at( item.GetObject().GetID() )->GetHeight() ) );
    _numbers.at( item.GetObject().GetID() )->SetActive( true );
    _numbers.at( item.GetObject().GetID() )->SetAlpha( 255 );
}

void InventoryScreen::UpdateLanguage()
{
    for (auto texture : _textures)
        delete texture.second;
    _textures.clear();

    for (auto& name : _names)
        delete name.second;
    _names.clear();

    for (auto& number : _numbers)
        delete number.second;
    _numbers.clear();

    for (auto& description : _descriptions)
        delete description.second;
    _descriptions.clear();

    delete _score;
    delete _money;



    _textures[ ObjectID::IronKey ] = new Texture( "Objets/Clé en Fer.png" );
    _names[ ObjectID::IronKey ] = new Texture( _translation->GetTranslation( 6 ), "Roboto-Regular.ttf", 17, { 0, 0, 0 } );
    _numbers[ ObjectID::IronKey ] = new Texture( "x 1", "Roboto-Regular.ttf", 17, { 0, 0, 0 } );
    _descriptions[ ObjectID::IronKey ] = new Texture( _translation->GetTranslation( 26 ), "Roboto-Regular.ttf", 24, { 0, 0, 0 } );

    _textures[ ObjectID::GoldKey ] = new Texture( "Objets/Clé en Or.png" );
    _names[ ObjectID::GoldKey ] = new Texture( _translation->GetTranslation( 7 ), "Roboto-Regular.ttf", 17, { 0, 0, 0 } );
    _numbers[ ObjectID::GoldKey ] = new Texture( "x 1", "Roboto-Regular.ttf", 17, { 0, 0, 0 } );
    _descriptions[ ObjectID::GoldKey ] = new Texture( _translation->GetTranslation( 27 ), "Roboto-Regular.ttf", 24, { 0, 0, 0 } );

    _textures[ ObjectID::LifePotion ] = new Texture( "Objets/Fiole.png" );
    _names[ ObjectID::LifePotion ] = new Texture( _translation->GetTranslation( 10 ), "Roboto-Regular.ttf", 17, { 0, 0, 0 } );
    _numbers[ ObjectID::LifePotion ] = new Texture( "x 1", "Roboto-Regular.ttf", 17, { 0, 0, 0 } );
    _descriptions[ ObjectID::LifePotion ] = new Texture( _translation->GetTranslation( 28 ), "Roboto-Regular.ttf", 24, { 0, 0, 0 } );

    _textures[ ObjectID::GrapplingHook ] = new Texture( "Objets/Grapin.png" );
    _names[ ObjectID::GrapplingHook ] = new Texture( _translation->GetTranslation( 8 ), "Roboto-Regular.ttf", 17, { 0, 0, 0 } );
    _numbers[ ObjectID::GrapplingHook ] = new Texture( "x 1", "Roboto-Regular.ttf", 17, { 0, 0, 0 } );
    _descriptions[ ObjectID::GrapplingHook ] = new Texture( _translation->GetTranslation( 29 ), "Roboto-Regular.ttf", 24, { 0, 0, 0 } );

    _textures[ ObjectID::Egg ] = new Texture( "Objets/Oeuf.png" );
    _names[ ObjectID::Egg ] = new Texture( _translation->GetTranslation( 1 ), "Roboto-Regular.ttf", 17, { 0, 0, 0 } );
    _numbers[ ObjectID::Egg ] = new Texture( "x 1", "Roboto-Regular.ttf", 17, { 0, 0, 0 } );
    _descriptions[ ObjectID::Egg ] = new Texture( _translation->GetTranslation( 30 ), "Roboto-Regular.ttf", 24, { 0, 0, 0 } );

    _textures[ ObjectID::Hint1 ] = new Texture( "Objets/Parchemin.png" );
    _names[ ObjectID::Hint1 ] = new Texture( _translation->GetTranslation( 11 ), "Roboto-Regular.ttf", 17, { 0, 0, 0 } );
    _numbers[ ObjectID::Hint1 ] = new Texture( "x 1", "Roboto-Regular.ttf", 17, { 0, 0, 0 } );
    _descriptions[ ObjectID::Hint1 ] = new Texture( _translation->GetTranslation( 19 ), "Roboto-Regular.ttf", 24, { 0, 0, 0 } );

    _textures[ ObjectID::Hint2 ] = new Texture( "Objets/Parchemin.png" );
    _names[ ObjectID::Hint2 ] = new Texture( _translation->GetTranslation( 11 ), "Roboto-Regular.ttf", 17, { 0, 0, 0 } );
    _numbers[ ObjectID::Hint2 ] = new Texture( "x 1", "Roboto-Regular.ttf", 17, { 0, 0, 0 } );
    _descriptions[ ObjectID::Hint2 ] = new Texture( _translation->GetTranslation( 19 ), "Roboto-Regular.ttf", 24, { 0, 0, 0 } );

    _textures[ ObjectID::Hint3 ] = new Texture( "Objets/Parchemin.png" );
    _names[ ObjectID::Hint3 ] = new Texture( _translation->GetTranslation( 11 ), "Roboto-Regular.ttf", 17, { 0, 0, 0 } );
    _numbers[ ObjectID::Hint3 ] = new Texture( "x 1", "Roboto-Regular.ttf", 17, { 0, 0, 0 } );
    _descriptions[ ObjectID::Hint3 ] = new Texture( _translation->GetTranslation( 19 ), "Roboto-Regular.ttf", 24, { 0, 0, 0 } );

    _textures[ ObjectID::Crowbar ] = new Texture( "Objets/Pied de biche.png" );
    _names[ ObjectID::Crowbar ] = new Texture( _translation->GetTranslation( 5 ), "Roboto-Regular.ttf", 17, { 0, 0, 0 } );
    _numbers[ ObjectID::Crowbar ] = new Texture( "x 1", "Roboto-Regular.ttf", 17, { 0, 0, 0 } );
    _descriptions[ ObjectID::Crowbar ] = new Texture( _translation->GetTranslation( 31 ), "Roboto-Regular.ttf", 24, { 0, 0, 0 } );

    _textures[ ObjectID::Torch ] = new Texture( "Objets/Torche.png" );
    _names[ ObjectID::Torch ] = new Texture( _translation->GetTranslation( 9 ), "Roboto-Regular.ttf", 17, { 0, 0, 0 } );
    _numbers[ ObjectID::Torch ] = new Texture( "x 1", "Roboto-Regular.ttf", 17, { 0, 0, 0 } );
    _descriptions[ ObjectID::Torch ] = new Texture( _translation->GetTranslation( 32 ), "Roboto-Regular.ttf", 24, { 0, 0, 0 } );

    _textures[ ObjectID::CursedRing ] = new Texture( "Objets/Bague.png" );
    _names[ ObjectID::CursedRing ] = new Texture( _translation->GetTranslation( 12 ), "Roboto-Regular.ttf", 17, { 0, 0, 0 } );
    _numbers[ ObjectID::CursedRing ] = new Texture( "x 1", "Roboto-Regular.ttf", 17, { 0, 0, 0 } );
    _descriptions[ ObjectID::CursedRing ] = new Texture( _translation->GetTranslation( 33 ), "Roboto-Regular.ttf", 24, { 0, 0, 0 } );

    for (int i=ObjectID::Egg ; i<ObjectID::TOTAL ; ++i )
    {
        _textures.at( (ObjectID) i )->SetPosition( coordinates[ i-1 ] );
        _textures.at( (ObjectID) i )->SetScale( Vector2f( 0.15f, 0.15f ));
        _textures.at( (ObjectID) i )->SetAlpha( 50 );

        _names.at( (ObjectID) i )->SetPosition( _textures.at( (ObjectID) i )->GetPosition() + Vector2i( 0, _textures.at( (ObjectID) i )->GetHeight()*_textures.at( (ObjectID) i )->GetScale().y ) );
        _names.at( (ObjectID) i )->SetAlpha( 50 );

        _numbers.at( (ObjectID) i )->SetPosition( _names.at( (ObjectID) i )->GetPosition() + Vector2i( 0, _names.at( (ObjectID) i )->GetHeight() ) );
        _numbers.at( (ObjectID) i )->SetAlpha( 50 );

        _descriptions.at( (ObjectID) i )->SetPosition( Vector2i( Graphics::SCREEN_WIDTH*0.5f, Graphics::SCREEN_HEIGHT*0.8f ) );
    }


    _score = new Texture(_translation->GetTranslation( 13 ) + " : " + std::to_string( _castle->GetScore() ), "Roboto-Regular.ttf", 24, { 0, 0, 0 } );
    _score->SetPosition( Vector2i( Graphics::SCREEN_WIDTH*0.07f, Graphics::SCREEN_HEIGHT*0.05f ) );

    _money = new Texture( _translation->GetTranslation( 16 ) + " : " + std::to_string( _castle->GetPlayer()->GetMoney() ), "Roboto-Regular.ttf", 24, { 0, 0, 0 } );
    _money->SetPosition( Vector2i( Graphics::SCREEN_WIDTH*0.9f, Graphics::SCREEN_HEIGHT*0.05f ));
}

void InventoryScreen::SetCastle( Castle* castle )
{
    _castle = castle;
}