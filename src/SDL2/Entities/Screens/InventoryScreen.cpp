#include "InventoryScreen.h"

InventoryScreen::InventoryScreen( Castle* const castle, Translation* const trans ) : _castle( castle ), _translation(trans), GameEntity()
{
    _inputs = InputsManager::GetInstance();


    _textures[ ObjectID::IronKey ] = new Texture( "Objets/Clé en Fer.png" );
    _names[ ObjectID::IronKey ] = new Texture( "Iron key", "Roboto-Regular.ttf", 24, { 0, 0, 0 } );
    _numbers[ ObjectID::IronKey ] = new Texture( "x 1", "Roboto-Regular.ttf", 24, { 0, 0, 0 } );
    _descriptions[ ObjectID::IronKey ] = new Texture( "A key made out of stainless steel allowing to open doors. Infinite number of usages.", "Roboto-Regular.ttf", 24, { 0, 0, 0 } );

    _textures[ ObjectID::GoldKey ] = new Texture( "Objets/Clé en Or.png" );
    _names[ ObjectID::GoldKey ] = new Texture( "Gold key", "Roboto-Regular.ttf", 24, { 0, 0, 0 } );
    _numbers[ ObjectID::GoldKey ] = new Texture( "x 1", "Roboto-Regular.ttf", 24, { 0, 0, 0 } );
    _descriptions[ ObjectID::GoldKey ] = new Texture( "A key made out of shining gold allowing to open doors. Infinite number of usages.", "Roboto-Regular.ttf", 24, { 0, 0, 0 } );

    _textures[ ObjectID::LifePotion ] = new Texture( "Objets/Fiole.png" );
    _names[ ObjectID::LifePotion ] = new Texture( "Life potion", "Roboto-Regular.ttf", 24, { 0, 0, 0 } );
    _numbers[ ObjectID::LifePotion ] = new Texture( "x 1", "Roboto-Regular.ttf", 24, { 0, 0, 0 } );
    _descriptions[ ObjectID::LifePotion ] = new Texture( "A suspicious looking potion. Restores 80 life points.", "Roboto-Regular.ttf", 24, { 0, 0, 0 } );

    _textures[ ObjectID::GrapplingHook ] = new Texture( "Objets/Grapin.png" );
    _names[ ObjectID::GrapplingHook ] = new Texture( "Grappling Hook", "Roboto-Regular.ttf", 24, { 0, 0, 0 } );
    _numbers[ ObjectID::GrapplingHook ] = new Texture( "x 1", "Roboto-Regular.ttf", 24, { 0, 0, 0 } );
    _descriptions[ ObjectID::GrapplingHook ] = new Texture( "A surprisingly useful tool. Used to escape from an oblivion room.", "Roboto-Regular.ttf", 24, { 0, 0, 0 } );

    _textures[ ObjectID::Egg ] = new Texture( "Objets/Oeuf.png" );
    _textures[ ObjectID::Egg ]->SetScale( Vector2f( 0.25f, 0.25f ) );
    _names[ ObjectID::Egg ] = new Texture( "Egg", "Roboto-Regular.ttf", 24, { 0, 0, 0 } );
    _numbers[ ObjectID::Egg ] = new Texture( "x 1", "Roboto-Regular.ttf", 24, { 0, 0, 0 } );
    _descriptions[ ObjectID::Egg ] = new Texture( "An egg of a roaming phoenix. You thief!", "Roboto-Regular.ttf", 24, { 0, 0, 0 } );

    _textures[ ObjectID::Hint1 ] = new Texture( "Objets/Parchemin.png" );
    _names[ ObjectID::Hint1 ] = new Texture( "Hint #1", "Roboto-Regular.ttf", 24, { 0, 0, 0 } );
    _numbers[ ObjectID::Hint1 ] = new Texture( "x 1", "Roboto-Regular.ttf", 24, { 0, 0, 0 } );
    _descriptions[ ObjectID::Hint1 ] = new Texture( "A hint! It says : ", "Roboto-Regular.ttf", 24, { 0, 0, 0 } );

    _textures[ ObjectID::Hint2 ] = new Texture( "Objets/Parchemin.png" );
    _names[ ObjectID::Hint2 ] = new Texture( "Hint #2", "Roboto-Regular.ttf", 24, { 0, 0, 0 } );
    _numbers[ ObjectID::Hint2 ] = new Texture( "x 1", "Roboto-Regular.ttf", 24, { 0, 0, 0 } );
    _descriptions[ ObjectID::Hint2 ] = new Texture( "A hint! It says : ", "Roboto-Regular.ttf", 24, { 0, 0, 0 } );

    _textures[ ObjectID::Hint3 ] = new Texture( "Objets/Parchemin.png" );
    _names[ ObjectID::Hint3 ] = new Texture( "Hint #3", "Roboto-Regular.ttf", 24, { 0, 0, 0 } );
    _numbers[ ObjectID::Hint3 ] = new Texture( "x 1", "Roboto-Regular.ttf", 24, { 0, 0, 0 } );
    _descriptions[ ObjectID::Hint3 ] = new Texture( "A hint! It says : ", "Roboto-Regular.ttf", 24, { 0, 0, 0 } );

    _textures[ ObjectID::Crowbar ] = new Texture( "Objets/Pied de biche.png" );
    _names[ ObjectID::Crowbar ] = new Texture( "Crowbar", "Roboto-Regular.ttf", 24, { 0, 0, 0 } );
    _numbers[ ObjectID::Crowbar ] = new Texture( "x 1", "Roboto-Regular.ttf", 24, { 0, 0, 0 } );
    _descriptions[ ObjectID::Crowbar ] = new Texture( "A rusted crowbar. Can open doors", "Roboto-Regular.ttf", 24, { 0, 0, 0 } );

    _textures[ ObjectID::Torch ] = new Texture( "Objets/Torche.png" );
    _names[ ObjectID::Torch ] = new Texture( "Torch", "Roboto-Regular.ttf", 24, { 0, 0, 0 } );
    _numbers[ ObjectID::Torch ] = new Texture( "x 1", "Roboto-Regular.ttf", 24, { 0, 0, 0 } );
    _descriptions[ ObjectID::Torch ] = new Texture( "A self-made torch. Used to light room torches", "Roboto-Regular.ttf", 24, { 0, 0, 0 } );

    _score = new Texture( "Score : ", "Roboto-Regular.ttf", 24, { 0, 0, 0 } );
    _money = new Texture( "Money : ", "Roboto-Regular.ttf", 24, { 0, 0, 0 } );

    for (auto& texture : _textures)
        texture.second->SetScale( Vector2f( 0.1f, 0.1f ) );
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

    delete _score;
    _score = new Texture( "Score : " + std::to_string( _castle->GetScore() ), "Roboto-Regular.ttf", 24, { 0, 0, 0 } );
    _score->SetPosition( Vector2i( Graphics::SCREEN_WIDTH*0.07f, Graphics::SCREEN_HEIGHT*0.05f ) );

    delete _money;
    _money = new Texture( "Money : " + std::to_string( _castle->GetPlayer()->GetMoney() ), "Roboto-Regular.ttf", 24, { 0, 0, 0 } );
    _money->SetPosition( Vector2i( Graphics::SCREEN_WIDTH*0.9f, Graphics::SCREEN_HEIGHT*0.05f ));

    for (auto& texture : _textures)
        texture.second->SetActive( false );
    for (auto& name : _names)
        name.second->SetActive( false );
    for (auto& number : _numbers)
        number.second->SetActive( false );
    for (auto& description : _descriptions)
        description.second->SetActive( false );

    const int offset = 75; // in pixels
    static const int WIDTH = Graphics::SCREEN_WIDTH - 2*offset; // in pixels
    static const Vector2i coordinates[] = {
            Vector2i( WIDTH/5, 1.5f*offset ), Vector2i( 2*WIDTH/5, 1.5f*offset ), Vector2i( 3*WIDTH/5, 1.5f*offset ), Vector2i( 4*WIDTH/5, 1.5f*offset ),
            Vector2i( WIDTH/5, 2.5f*offset ), Vector2i( 2*WIDTH/5, 2.5f*offset ), Vector2i( 3*WIDTH/5, 2.5f*offset ), Vector2i( 4*WIDTH/5, 2.5f*offset )
    };

    for (int i=0 ; i<_castle->GetPlayer()->GetItems().size() ; ++i)
    {
        const ItemStack& item = _castle->GetPlayer()->GetItems()[ i ];
        const Object& obj = item.GetObject();
        if (obj.GetID() == ObjectID::Nothing)
            continue;

        _textures.at( obj.GetID() )->SetActive( true );
        _textures.at( obj.GetID() )->SetPosition( coordinates[ i ] );

        _names.at( obj.GetID() )->SetActive( true );
        _names.at( obj.GetID() )->SetPosition( coordinates[ i ] + Vector2i( 0, _textures.at( obj.GetID() )->GetHeight()/2 ) );

        _numbers.at( obj.GetID() )->SetActive( true );
        _numbers.at( obj.GetID() )->SetPosition( coordinates[ i ] + Vector2i( _textures.at( obj.GetID() )->GetWidth()/2, 0 ) );

        _descriptions.at( obj.GetID() )->SetActive( true );
        _descriptions.at( obj.GetID() )->SetPosition( Vector2i( Graphics::SCREEN_WIDTH*0.5f, Graphics::SCREEN_HEIGHT*0.8f ) );
    }
}

void InventoryScreen::Render()
{
    _score->Render();
    _money->Render();

    for (const auto& texture : _textures)
        if (texture.second->GetActive())
            texture.second->Render();

    for (const auto& name : _names)
        if (name.second->GetActive())
            name.second->Render();

    for (const auto& number : _numbers)
        if (number.second->GetActive())
            number.second->Render();

    for (const auto& description : _descriptions)
        if (description.second->GetActive())
            description.second->Render();
}