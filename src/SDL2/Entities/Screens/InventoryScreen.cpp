#include "InventoryScreen.h"

InventoryScreen::InventoryScreen( Castle* const castle, Translation* const trans ) : _castle( castle ), _translation(trans), GameEntity()
{
    _inputs = InputsManager::GetInstance();

    _textures[ ObjectID::IronKey ] = new Texture( "Objets/Clé en Fer.png" );
    _textures[ ObjectID::GoldKey ] = new Texture( "Objets/Clé en Or.png" );
    _textures[ ObjectID::LifePotion ] = new Texture( "Objets/Fiole.png" );
    _textures[ ObjectID::GrapplingHook ] = new Texture( "Objets/Grapin.png" );
    _textures[ ObjectID::Egg ] = new Texture( "Objets/Oeuf.png" );
    _textures[ ObjectID::Hint1 ] = new Texture( "Objets/Hint.png" );
    _textures[ ObjectID::Hint2 ] = new Texture( "Objets/Hint.png" );
    _textures[ ObjectID::Hint3 ] = new Texture( "Objets/Hint.png" );
    _textures[ ObjectID::Crowbar ] = new Texture( "Objets/Pied de biche.png" );
    _textures[ ObjectID::Torch ] = new Texture( "Objets/Torche.png" );
}

InventoryScreen::~InventoryScreen()
{
    _castle = nullptr;
    _inputs = nullptr;

    for (auto texture : _textures)
        delete texture.second;
    _textures.clear();
}

void InventoryScreen::ProcessEvents( SDL_Event* event )
{

}

void InventoryScreen::Update()
{
    _castle->Update();

    for (auto texture : _textures)
        texture.second->SetActive( false );

    const int offset = 75; // in pixels
    static const int WIDTH = Graphics::SCREEN_WIDTH - 2*offset; // in pixels
    static const Vector2i coordinates[] = {
            Vector2i( WIDTH/5, offset ), Vector2i( 2*WIDTH/5, offset ), Vector2i( 3*WIDTH/5, offset ), Vector2i( 4*WIDTH/5, offset ),
            Vector2i( WIDTH/5, 2*offset ), Vector2i( 2*WIDTH/5, 2*offset ), Vector2i( 3*WIDTH/5, 2*offset ), Vector2i( 4*WIDTH/5, 2*offset )
    };

    for (int i=0 ; i<_castle->GetPlayer()->GetItems().size() ; ++i)
    {
        const ItemStack& item = _castle->GetPlayer()->GetItems()[ i ];
        const Object& obj = item.GetObject();
        if (obj.ToObjectID() == ObjectID::Nothing)
            continue;

        _cursor = i;

        _textures.at( obj.ToObjectID() )->SetActive( true );
        _textures.at( obj.ToObjectID() )->SetPosition( coordinates[ i ] );
    }
}

void InventoryScreen::Render()
{
    for (const auto& texture : _textures)
        if (texture.second->GetActive())
            texture.second->Render();
}