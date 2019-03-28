#include "InventoryScreen.h"

InventoryScreen::InventoryScreen( Castle* const castle ) : _castle( castle ), GameEntity()
{
    _inputs = InputsManager::GetInstance();

    _ironKey = new Texture( "Objets/Clé en Fer.png" );
    _goldKey = new Texture( "Objets/Clé en Or.png" );
    _lifePotion = new Texture( "Objets/Fiole.png" );
    _grapplingHook = new Texture( "Objets/Grapin.png" );
    _egg = new Texture( "Objets/Oeuf.png" );
    _hint = new Texture( "Objets/Hint.png" );
    _crowbar = new Texture( "Objets/Pied de biche.png" );
    _torch = new Texture( "Objets/Torche.png" );

    _select = new Texture( "Selection.png" );
    _select->SetScale( Vector2i( 7.5f, 7.5f ) );
    _select->SetPosition( Vector2f( 7.5f, 7.5f )*Vector2f( _select->GetWidth()*0.5f, _select->GetHeight()*0.5f ) );

    _position = Vector2i( 0, 0 );
}

InventoryScreen::~InventoryScreen()
{
    _castle = nullptr;
    _inputs = nullptr;

    delete [] _itemIDs;

    delete _ironKey;
    delete _goldKey;
    delete _lifePotion;
    delete _grapplingHook;
    delete _egg;
    delete _hint;
    delete _crowbar;
    delete _torch;

    delete _select;
}

void InventoryScreen::ProcessEvents( SDL_Event* event )
{
    const Vector2f movement = (float) _select->GetHeight()*_select->GetScale();

    if (_inputs->KeyPressed( SDL_SCANCODE_D ))
    {
        _select->Translate( movement*VEC2_RIGHT );
        _position += VEC2_RIGHT;
    }
    if (_inputs->KeyPressed( SDL_SCANCODE_A ))
    {
        _select->Translate( movement*VEC2_LEFT );
        _position += VEC2_LEFT;
    }
    if (_inputs->KeyPressed( SDL_SCANCODE_S ))
    {
        _select->Translate( movement*VEC2_UP ); // SDL2 coordinates
        _position += VEC2_UP;
    }
    if (_inputs->KeyPressed( SDL_SCANCODE_W ))
    {
        _select->Translate( movement*VEC2_DOWN ); // SDL2 coordinates
        _position += VEC2_DOWN;
    }
}

void InventoryScreen::Update()
{
    _castle->Update();

    _items = (int) _castle->GetPlayer()->GetItems().size();
    delete [] _itemIDs;
    _itemIDs = new int [ _items ];

    for (unsigned long i=0 ; i<_items ; ++i)
        _itemIDs[ i ] = _castle->GetPlayer()->GetItems().at( i ).GetObject().ToObjectID();

    for (int id=0 ; id<_items ; ++id)
    {
        switch (_itemIDs[ id ])
        {
            case ObjectID::IronKey:
                _ironKey->SetActive( true );
                _ironKey->SetPosition( _select->GetPosition() );
                break;
            default:
                break;
        }
    }
}

void InventoryScreen::Render()
{
    Graphics::GetInstance()->SetBackgroundColor( 217, 207, 141 );

    _select->Render();

    if (_ironKey->GetActive())
        _ironKey->Render();
}