//
// Created by ggeof
//

#include "Trader.h"

Trader::Trader( Player* player ) : _player( player )
{

}

Trader::~Trader()
{
    _player = nullptr;
}

bool Trader::Purchase( const int id_Object )
{
    Object object = Object::ToObject((ObjectID) id_Object );
    int price = 0;
    switch (id_Object)
    {
        case 2 : price = price_Crowbar;
            break;
        case 5 : price = price_GrapplingHook;
            break;
        case 6 : price = price_Torch;
            break;
        case 7 : price = price_LifePotion;
            break;
        default: break;
    }
    if (_player->GetMoney() - price >= 0)
    {
        _player->AddItem( object );
        _player->AddMoney( -price );
        return true;
    }
    else
        return false;
}

int Trader::getPrice( Object object )
{
    switch (object.ToObjectID())
    {
        case ObjectID::Crowbar : return price_Crowbar;
        case ObjectID::GrapplingHook: return price_GrapplingHook;
        case ObjectID::Torch: return price_Torch;
        case ObjectID::LifePotion: return price_LifePotion;
        default: return 0;
    }

}