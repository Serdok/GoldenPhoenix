//
// Created by ggeof
//

#include "Trader.h"

Trader::Trader( Player* const player ) : _player( player )
{

}

Trader::~Trader()
{
    _player = nullptr;
}

bool Trader::Purchase( const ObjectID id_Object )
{
    int price = 0;
    switch (id_Object)
    {
        case ObjectID::Crowbar : price = price_Crowbar;
            break;
        case ObjectID::GrapplingHook : price = price_GrapplingHook;
            break;
        case ObjectID::Torch : price = price_Torch;
            break;
        case ObjectID::LifePotion : price = price_LifePotion;
            break;
        default: break;
    }
    if (_player->GetMoney() - price >= 0)
    {
        _player->AddItem( Object::ToObject( id_Object) );
        _player->AddMoney( -price );
        return true;
    }
    else
        return false;
}

int Trader::GetPrice( const ObjectID id_Object )
{
    switch (id_Object)
    {
        case ObjectID::Crowbar : return price_Crowbar;
        case ObjectID::GrapplingHook: return price_GrapplingHook;
        case ObjectID::Torch: return price_Torch;
        case ObjectID::LifePotion: return price_LifePotion;
        default: return 0;
    }

}