#include "EndScreen.h"

EndScreen::EndScreen(Castle* const castle) : _castle( castle )
{

    Text = new Texture( text1, "Roboto-Regular.ttf", 40, { 255, 255, 255 } );
    Text->SetPosition(Vector2f(Graphics::SCREEN_WIDTH/2,Graphics::SCREEN_HEIGHT/2));

    _animCredit = !_castle->GetPlayer()->HasObject(Object::ToObject(Egg));

    textScroll[0] = "Crédit : ";
    textScroll[1] = " ";
    textScroll[2] = " ";
    textScroll[3] = "Développeur : ";
    textScroll[4] = "Anass LAHNIN, Julia FFRANCOIS, Geoffroy HEURTEL ";
    textScroll[5] = " ";
    textScroll[6] = "Game Designer ";
    textScroll[7] = "Geoffroy HEURTEL ";
    textScroll[8] = " ";
    textScroll[9] = "Music : ";
    textScroll[10] = "Otto Halmén - Airship Thunderchild";
    textScroll[11] = " ";
    textScroll[12] = "Inspiré librement du jeu : ";
    textScroll[13] = "\"L'Aigle d'or\"";
    textScroll[14] = "Sorti en 1985";
    textScroll[15] = "Développé par Louis-Marie ROCQUES";
    textScroll[16] = " ";
    textScroll[17] = "2019 © Copyright : ";
    textScroll[18] = "Julia FRANCOIS";
    textScroll[19] = "Geoffroy HEURTEL";
    textScroll[20] = "Anass LAHNIN";
    textScroll[21] = " ";


    for(int i = 0; i < NBTEXTINSCREEN; i++)
    { 
        _textscroll[i] = new Texture(  " " , "Pasatona.ttf", 60, { 61, 86, 189 } );
        _textscroll[i]->SetPosition(Vector2f(Graphics::SCREEN_WIDTH/2,Graphics::SCREEN_HEIGHT/NBTEXTINSCREEN*i));
    
    }
}

EndScreen::~EndScreen()
{
    delete Text;

    delete [] _textscroll ;
}

void EndScreen::ProcessEvents( SDL_Event* event )
{
}

void EndScreen::Update()
{
    if(!_animCredit)
    {
        _temps++;
    
        int step = _temps/90;
        int tmp = _temps%90;

        switch (step)
        {
            case 0:
                Text->SetAlpha(float(tmp)/90*float(255));
                std::cout << float(tmp)/90*float(255) << std::endl;
                break;
            case 1:
                Text->SetAlpha(255);
                break;
            case 4:
                Text->SetAlpha(255*float(1-float(tmp)/90));
                if(tmp == 89)
                {
                    delete Text;
                    stepAnimFirst++;
                    switch (stepAnimFirst)
                    {  
                        case 1:
                            Text = new Texture( text2 + std::to_string(_castle->GetScore()), "Roboto-Regular.ttf", 40, { 255, 255, 255 } );
                            break;
                        case 2:
                            Text = new Texture( text3, "Roboto-Regular.ttf", 40, { 255, 255, 255 } );
                            break;
                        case 3:
                            Text = new Texture( text4 + std::to_string(_castle->GetPlayer()->GetDeaths()), "Roboto-Regular.ttf", 40, { 255, 255, 255 } );
                            break;
                    }
                    if(stepAnimFirst == 4)
                        _animCredit = true;
                    else
                    {
                        Text->SetAlpha(0);
                        Text->SetPosition(Vector2f(Graphics::SCREEN_WIDTH/2,Graphics::SCREEN_HEIGHT/2));
                    }
                    _temps = 0;
                }
                break;
        
            default:
                break;
        }
    } 
    //Animation des crédits
    else
    {
        if(StepScroll < MAXSCROLL)
        {
            int i = StepScroll%NBTEXTINSCREEN;
            if(_textscroll[i]->GetPosition().y == 0){
                delete _textscroll[i];
                _textscroll[i] = new Texture(  textScroll[StepScroll] , "Roboto-Regular.ttf", 30, { 61, 86, 189 } );
                _textscroll[i]->SetPosition(Vector2f(Graphics::SCREEN_WIDTH/2,Graphics::SCREEN_HEIGHT));
                StepScroll++;
            }

        }

        for(int i = 0; i < NBTEXTINSCREEN; i++)
        { 
            _textscroll[i] ->SetPosition(_textscroll[i]->GetPosition()-Vector2f(0,1.0f));
        }
        if(StepScroll == MAXSCROLL)
            if(_textscroll[NBTEXTINSCREEN-1]->GetPosition().y <= 0)
                _quit = true;
    }
}

void EndScreen::Render()
{
    if(!_animCredit)
    {
        Text->Render();
    }
    else
    {
        for(int i = 0; i < NBTEXTINSCREEN; i++)
        { 
            _textscroll[i] -> Render();
        
        }
    }
}

bool EndScreen::GetQuit() const
{
    return _quit;
}