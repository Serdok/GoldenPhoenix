//
// Created by serdok on 05/03/19.
//

#include "Castle.h"

Castle::Castle( const std::string& filename )
{
    std::ifstream file( filename.c_str() );
    if (!file.good())
        throw Exception( "Failed to open " + filename + '!', __FILE__, __LINE__ );

    for (int room = 0 ; room < NUM_ROOMS ; ++room)
    {
        int line = 1;
        std::vector< std::string > content;
        std::string data;
        while (line < 11 && std::getline( file, data ))
        {
            if (data.empty()) // Skip empty lines
                continue;

            content.emplace_back( data );
            ++line;
        }
        _rooms[ room ] = new Room( content );
        content.clear();
    }

    file.close();
}

Castle::~Castle()
{
    for (auto& room : _rooms)
        delete room;
}

void Castle::Update()
{
    if(_thereIsABat)
    {
        if(bat.getPosition().x == 0)
            bat.setDirection(VEC2_RIGHT);
        else if(bat.getPosition().x == ROOM_WIDTH-1)
            bat.setDirection(VEC2_LEFT);
        else
            bat.Move(getDirection()); 
        if(bat.getPosition() == player.getPosition())
            bat.Attack(player);
    }

    player.AddLife(-1);
}

void Castle::movePRight()
{
    if(player.getDirection() != VEC2_RIGHT)
    {
        player.setDirection(VEC2_RIGHT);
        return;
    }

    int x = player.getPosition().x + 1;
    if(x != 7)
    {
        if(getSquare(x,y) == 0)
            player.Move(getDirection());
    }
}
void Castle::movePLeft()
{
    if(player.getDirection() != VEC2_LEFT)
    {
        player.setDirection(VEC2_LEFT);
        return;
    }

    int x = player.getPosition().x - 1;
    if(x != -1)
    {
        if(getSquare(x,y) == 0)
            player.Move(getDirection());
    }
}

void Castle::movePUp()
{
    if(player.getDirection() != VEC2_UP)
    {
        player.setDirection(VEC2_UP);
        return;
    }

    int y = player.getPosition().y + 1;
    if(y != 6)
    {
        if(getSquare(x,y) == 0)
            player.Move(getDirection());
    }
}

void Castle::movePUp()
{
    if(player.getDirection() != VEC2_DOWN)
    {
        player.setDirection(VEC2_DOWN);
        return;
    }

    int y = player.getPosition().y - 1;
    if(y != -1)
    {
        if(getSquare(x,y) == 0)
            player.Move(getDirection());
    }
}

void Castle::PickUp()
{
    if(player._crouch)
    {
        for (int i = 3; i < 12; ++i)
        {
            if(getSquare((player.getPosition()+player.getDirection()).x,(player.getPosition()+player.getDirection()).y) == i)
                player.AddItem(i);
        }
    }
    else if(!player._crouch)
    {
        if(getSquare((player.getPosition()+player.getDirection()).x,(player.getPosition()+player.getDirection()).y) == 1)
            player.AddItem(1);
    }
}