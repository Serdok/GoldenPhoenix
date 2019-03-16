//
// Created by serdok on 05/03/19.
//

#include "Castle.h"

Castle::Castle( const std::string& filename )
{
    std::ifstream file( filename.c_str(), std::ios::binary );
    if (!file.good())
        throw Exception( "Failed to open " + filename + '!', __FILE__, __LINE__ );

    while (!file.eof())
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
        std::queue< std::string > contentQUEUE; // Put everything in a queue (better data processing)
        for (const auto& i : contentVECTOR)
            contentQUEUE.push( i );

        _rooms.emplace_back( new Room( contentQUEUE ) );
        contentVECTOR.clear();
    }
    file.close();
    std::cout << _rooms.size() << " rooms loaded!" << std::endl;

    _player = new Player( _rooms[ 5 ] );
    _bat = new Bat();
}

Castle::~Castle()
{
    for (auto room : _rooms)
        delete room;

    delete _player;
    delete _bat;
}

void Castle::Update()
{
    if (_thereIsABat)
    {
        if (_bat->GetPosition().x == 0)
            _bat->SetDirection( VEC2_RIGHT );
        else if (_bat->GetPosition().x == ROOM_WIDTH - 1)
            _bat->SetDirection( VEC2_LEFT );
        else
            _bat->Translate( _bat->GetDirection());
        if (_bat->GetPosition() == _player->GetPosition())
            _bat->Attack( _player );
    }

    _player->AddLife( -1 );

    if (_player->GetLife() == 0)
    {
        _deaths += 1;
        //return to the beginning
        _player->SetLife( 100 );
        setScore( 0 );
        setMoney( 400 );
    }
}

void Castle::movePRight()
{
    if (_player->GetDirection() != VEC2_RIGHT)
    {
        _player->SetDirection( VEC2_RIGHT );
        return;
    }
    if (_player->GetCurrentRoom()->GetSquare( _player->GetPosition() + VEC2_RIGHT ) == 0)
        _player->Translate( _player->GetDirection());
}

void Castle::movePLeft()
{
    if (_player->GetDirection() != VEC2_LEFT)
    {
        _player->SetDirection( VEC2_LEFT );
        return;
    }

    if (_player->GetCurrentRoom()->GetSquare( _player->GetPosition() + VEC2_LEFT ) == 0)
        _player->Translate( _player->GetDirection());
}

void Castle::movePUp()
{
    if (_player->GetDirection() != VEC2_UP)
    {
        _player->SetDirection( VEC2_UP );
        return;
    }
    if (_player->GetCurrentRoom()->GetSquare( _player->GetPosition() + VEC2_UP ) == 0)
        _player->Translate( _player->GetDirection());
}

void Castle::movePDown()
{
    if (_player->GetDirection() != VEC2_DOWN)
    {
        _player->SetDirection( VEC2_DOWN );
        return;
    }
    if (_player->GetCurrentRoom()->GetSquare( _player->GetPosition() + VEC2_DOWN ) == 0)
        _player->Translate( _player->GetDirection());
}

void Castle::PickUp()
{
    if (_player->Crouched())
    {
        for (int i = 3 ; i < 12 ; ++i)
        {
            if (_player->GetCurrentRoom()->GetSquare( _player->GetPosition() + _player->GetDirection()) == i)
                _player->AddItem( Object::ToObject((ObjectID) i ));

        }
    }
    else
    {
        if (_player->GetCurrentRoom()->GetSquare( _player->GetPosition() + _player->GetDirection()) == 1)
            _player->AddItem( Object::ToObject((ObjectID) 1 ));
    }
}

int Castle::getScore()
{
    return _score;
}

int Castle::getMoney()
{
    return _money;
}

void Castle::setScore( int s )
{
    _score = s;
}

void Castle::setMoney( int m )
{
    _money = m;
}