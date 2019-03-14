//
// Created by serdok on 05/03/19.
//

#include "Castle.h"

Castle::Castle( const std::string& filename )
{
    std::ifstream file( filename.c_str(), std::ios::binary );
    if (!file.good())
        throw Exception( "Failed to open " + filename + '!', __FILE__, __LINE__ );

    for (int room = 0 ; room < NUM_ROOMS ; ++room)
    {
        int lineNB = 1;
        std::vector< std::string > contentVECTOR;
        std::string line;
        while (lineNB < 11 && std::getline( file, line ))
        {
            if (line.empty()) // Skip empty lines
                continue;

            contentVECTOR.emplace_back( line );
            ++lineNB;
        }
        std::queue< std::string > contentQUEUE; // Put everything in a queue
        for (const auto& i : contentVECTOR)
            contentQUEUE.push( i );

        _rooms[ room ] = new Room( contentQUEUE );
        contentVECTOR.clear();
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

    if(player.getLife() == 0)
    {
        nbDeath += 1;
        //return to the beginning
        player.setLife(100);
        setScore(0);
        setMoney(400);
    }
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

int Castle::getScore()
{
    return score;
}

int Castle::getMoney()
{
    return money;
}

void Castle::setScore(int s)
{
    score = s;
}

void Castle::setMoney(int m)
{
    money = m;
}