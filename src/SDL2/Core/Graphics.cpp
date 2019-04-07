//
// Created by serdok on 07/03/19.
//

#include "Graphics.h"

Graphics* Graphics::sInstance = nullptr;

Graphics* Graphics::GetInstance()
{
    if (!sInstance)
        sInstance = new Graphics();

    return sInstance;
}

void Graphics::Quit()
{
    delete sInstance;
}


Graphics::Graphics() : _window( nullptr ), _renderer( nullptr )
{
    try
    {
        Init();
    }
    catch (Exception& e)
    {
        Rethrow( "Game graphics engine failed to initialize!", __FILE__, __LINE__ );
    }
}

Graphics::~Graphics()
{
    Cleanup( _renderer, _window );

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Graphics::Init()
{
    // SDL2 initialization
    if (SDL_Init( SDL_INIT_VIDEO ) < 0)
        throw Exception( "SDL2 failed to initialize : " + std::string( SDL_GetError()), __FILE__, __LINE__ );

    // Window creation
    _window = SDL_CreateWindow( "L'oeuf du Phénix", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if (!_window)
        throw Exception( "Window failed to create : " + std::string( SDL_GetError()), __FILE__, __LINE__ );

    // Renderer creation
    _renderer = SDL_CreateRenderer( _window, -1, SDL_RENDERER_ACCELERATED );
    if (!_renderer)
        throw Exception( "Renderer failed to create : " + std::string( SDL_GetError()), __FILE__, __LINE__ );

    // Set default background color
    SDL_SetRenderDrawColor( _renderer, 0x0F, 0x0F, 0xFF, 0xFF );

    // SDL2_image initialization
    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
    if (!( IMG_Init( imgFlags ) & imgFlags ))
        throw Exception( "SDL2_image failed to initialize : " + std::string( SDL_GetError()), __FILE__, __LINE__ );

    // SDL2_ttf initialization
    if (TTF_Init() < 0)
        throw Exception( "SDL2_ttf failed to initialize : " + std::string( SDL_GetError()), __FILE__, __LINE__ );
}

void Graphics::Render()
{
    SDL_RenderPresent( _renderer );
}

void Graphics::Clear()
{
    SDL_RenderClear( _renderer );
}

SDL_Texture* Graphics::LoadTexture( const std::string& imagepath )
{
    // Load image from file
    SDL_Surface* surface = IMG_Load( imagepath.c_str());
    if (!surface)
    {
        std::cerr << "Failed to load image from " + imagepath + " : " + std::string( SDL_GetError()) << std::endl;
        return nullptr;
    }

    // Convert loaded image to a texture to be drawn
    SDL_Texture* texture = SDL_CreateTextureFromSurface( _renderer, surface );
    SDL_FreeSurface( surface );
    if (!texture)
    {
        std::cerr << "Failed to load image from " + imagepath + " : " << SDL_GetError() << std::endl;
        return nullptr;
    }

    return texture;
}

SDL_Texture* Graphics::CreateTextTexture( TTF_Font* font, const std::string& text, const SDL_Color& color )
{
    // Load text with font and color
    SDL_Surface* surface = TTF_RenderText_Solid( font, text.c_str(), color );
    if (!surface)
    {
        std::cerr << "Failed to convert " + text + " to a texture : " << SDL_GetError() << std::endl;
        return nullptr;
    }

    // Convert loaded message to a texture to be drawn
    SDL_Texture* texture = SDL_CreateTextureFromSurface( _renderer, surface );
    SDL_FreeSurface( surface );
    if (!texture)
    {
        std::cerr << "Failed to convert " + text + " to a texture : " << SDL_GetError() << std::endl;
        return nullptr;
    }

    return texture;
}

void Graphics::DrawTexture( SDL_Texture* texture, const SDL_Rect* clip, const SDL_Rect* destination, const float angle, const SDL_RendererFlip flip )
{
    SDL_RenderCopyEx( _renderer, texture, clip, destination, angle, nullptr, flip );
}

void Graphics::SetBackgroundColor( unsigned char r, unsigned char g, unsigned char b )
{
    SDL_SetRenderDrawColor( _renderer, r, g, b, 0xFF );
}

void Graphics::DrawPoint( const Vector2i& center, const SDL_Color& color )
{
    Uint8 r, g, b, a;
    SDL_GetRenderDrawColor( _renderer, &r, &g, &b, &a );
    SDL_SetRenderDrawColor( _renderer, color.r, color.g, color.b, color.a );
    SDL_RenderDrawPoint( _renderer, center.x, center.y );
    SDL_SetRenderDrawColor( _renderer, r, g, b, a );
}

void Graphics::DrawLine( const Vector2i& min, const Vector2i& max, const SDL_Color& color )
{
    Uint8 r, g, b, a;
    SDL_GetRenderDrawColor( _renderer, &r, &g, &b, &a );
    SDL_SetRenderDrawColor( _renderer, color.r, color.g, color.b, color.a );
    SDL_RenderDrawLine( _renderer, min.x, min.y, max.x, max.y );
    SDL_SetRenderDrawColor( _renderer, r, g, b, a );
}

void Graphics::DrawRectangle( const Vector2i& min, const Vector2i& max, const SDL_Color& color )
{
    SDL_Rect rect = { min.x, min.y, max.x - min.x, max.y - min.y };

    Uint8 r, g, b, a;
    SDL_GetRenderDrawColor( _renderer, &r, &g, &b, &a );
    SDL_SetRenderDrawColor( _renderer, color.r, color.g, color.b, color.a );
    SDL_RenderDrawRect( _renderer, &rect );
    SDL_SetRenderDrawColor( _renderer, r, g, b, a );
}

void Graphics::DrawRectangleFill( const Vector2i& min, const Vector2i& max, const SDL_Color& color )
{
    SDL_Rect rect = { min.x, min.y, max.x - min.x, max.y - min.y };

    Uint8 r, g, b, a;
    SDL_GetRenderDrawColor( _renderer, &r, &g, &b, &a );
    SDL_SetRenderDrawColor( _renderer, color.r, color.g, color.b, color.a );
    SDL_RenderFillRect( _renderer, &rect );
    SDL_SetRenderDrawColor( _renderer, r, g, b, a );
}

void Graphics::DrawEllipse( const Vector2i& center, int radiusX, int radiusY, const SDL_Color& color )
{
    aaellipseRGBA( _renderer, center.x, center.y, radiusX, radiusY, color.r, color.g, color.b, color.a );
}

void Graphics::DrawEllipseFill( const Vector2i& center, int radiusX, int radiusY, const SDL_Color& color )
{
    filledEllipseRGBA( _renderer, center.x, center.y, radiusX, radiusY, color.r, color.g, color.b, color.a );
}

int Graphics::filledEllipseRGBA( SDL_Renderer* m_renderer, Sint16 x, Sint16 y, Sint16 rx, Sint16 ry, Uint8 r, Uint8 g, Uint8 b, Uint8 a )
{
    int result;
    int ix, iy;
    int h, i, j, k;
    int oh, oi, oj, ok;
    int xmh, xph;
    int xmi, xpi;
    int xmj, xpj;
    int xmk, xpk;

    /*
    * Sanity check radii
    */
    if (( rx < 0 ) || ( ry < 0 ))
    {
        return ( -1 );
    }

    /*
    * Special case for rx=0 - draw a vline
    */
    if (rx == 0)
    {
        return SDL_RenderDrawLine( m_renderer, x, y - ry, x, y + ry );
        //return (vlineRGBA(renderer, x, y - ry, y + ry, r, g, b, a));
    }
    /*
    * Special case for ry=0 - draw a hline
    */
    if (ry == 0)
    {
        return SDL_RenderDrawLine( m_renderer, x - rx, y, x + rx, y );
        //		return (hlineRGBA(renderer, x - rx, x + rx, y, r, g, b, a));
    }

    /*
    * Set color
    */
    result = 0;
    result |= SDL_SetRenderDrawBlendMode( m_renderer, ( a == 255 ) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND );
    result |= SDL_SetRenderDrawColor( m_renderer, r, g, b, a );

    /*
    * Init vars
    */
    oh = oi = oj = ok = 0xFFFF;

    /*
    * Draw
    */
    if (rx > ry)
    {
        ix = 0;
        iy = rx*64;

        do
        {
            h = ( ix + 32 ) >> 6;
            i = ( iy + 32 ) >> 6;
            j = ( h*ry )/rx;
            k = ( i*ry )/rx;

            if (( ok != k ) && ( oj != k ))
            {
                xph = x + h;
                xmh = x - h;
                if (k > 0)
                {
                    result |= SDL_RenderDrawLine( m_renderer, xmh, y + k, xph,
                                                  y + k ); //hline(renderer, xmh, xph, y + k);
                    result |= SDL_RenderDrawLine( m_renderer, xmh, y - k, xph,
                                                  y - k ); //hline(renderer, xmh, xph, y - k);
                }
                else
                {
                    result |= SDL_RenderDrawLine( m_renderer, xmh, y, xph, y ); // hline(renderer, xmh, xph, y);
                }
                ok = k;
            }
            if (( oj != j ) && ( ok != j ) && ( k != j ))
            {
                xmi = x - i;
                xpi = x + i;
                if (j > 0)
                {
                    result |= SDL_RenderDrawLine( m_renderer, xmi, y + j, xpi,
                                                  y + j );  //hline(renderer, xmi, xpi, y + j);
                    result |= SDL_RenderDrawLine( m_renderer, xmi, y - j, xpi,
                                                  y - j ); //hline(renderer, xmi, xpi, y - j);
                }
                else
                {
                    result |= SDL_RenderDrawLine( m_renderer, xmi, y, xpi, y ); //hline(renderer, xmi, xpi, y);
                }
                oj = j;
            }

            ix = ix + iy/rx;
            iy = iy - ix/rx;

        } while (i > h);
    }
    else
    {
        ix = 0;
        iy = ry*64;

        do
        {
            h = ( ix + 32 ) >> 6;
            i = ( iy + 32 ) >> 6;
            j = ( h*rx )/ry;
            k = ( i*rx )/ry;

            if (( oi != i ) && ( oh != i ))
            {
                xmj = x - j;
                xpj = x + j;
                if (i > 0)
                {
                    result |= SDL_RenderDrawLine( m_renderer, xmj, y + i, xpj,
                                                  y + i ); //hline(renderer, xmj, xpj, y + i);
                    result |= SDL_RenderDrawLine( m_renderer, xmj, y - i, xpj,
                                                  y - i ); //hline(renderer, xmj, xpj, y - i);
                }
                else
                {
                    result |= SDL_RenderDrawLine( m_renderer, xmj, y, xpj, y ); //hline(renderer, xmj, xpj, y);
                }
                oi = i;
            }
            if (( oh != h ) && ( oi != h ) && ( i != h ))
            {
                xmk = x - k;
                xpk = x + k;
                if (h > 0)
                {
                    result |= SDL_RenderDrawLine( m_renderer, xmk, y + h, xpk,
                                                  y + h ); //hline(renderer, xmk, xpk, y + h);
                    result |= SDL_RenderDrawLine( m_renderer, xmk, y - h, xpk,
                                                  y - h ); //hline(renderer, xmk, xpk, y - h);
                }
                else
                {
                    result |= SDL_RenderDrawLine( m_renderer, xmk, y, xpk, y ); //hline(renderer, xmk, xpk, y);
                }
                oh = h;
            }

            ix = ix + iy/ry;
            iy = iy - ix/ry;

        } while (i > h);
    }

    return ( result );
}

int Graphics::aaellipseRGBA( SDL_Renderer* renderer, Sint16 x, Sint16 y, Sint16 rx, Sint16 ry, Uint8 r, Uint8 g, Uint8 b, Uint8 a )
{
    int result;
    int i;
    int a2, b2, ds, dt, dxt, t, s, d;
    Sint16 xp, yp, xs, ys, dyt, od, xx, yy, xc2, yc2;
    float cp;
    double sab;
    Uint8 weight, iweight;

    /*
    * Sanity check radii
    */
    if (( rx < 0 ) || ( ry < 0 ))
    {
        return ( -1 );
    }

    /*
    * Special case for rx=0 - draw a vline
    */
    if (rx == 0)
    {
        return SDL_RenderDrawLine( renderer, x, y - ry, x,
                                   y + ry ); //(vlineRGBA(renderer, x, y - ry, y + ry, r, g, b, a));
    }
    /*
    * Special case for ry=0 - draw an hline
    */
    if (ry == 0)
    {
        return SDL_RenderDrawLine( renderer, x - rx, y, x + rx,
                                   y ); //(hlineRGBA(renderer, x - rx, x + rx, y, r, g, b, a));
    }

    /* Variable setup */
    a2 = rx*rx;
    b2 = ry*ry;

    ds = 2*a2;
    dt = 2*b2;

    xc2 = 2*x;
    yc2 = 2*y;

    sab = sqrt((double) ( a2 + b2 ));
    od = (Sint16) lrint( sab*0.01 ) + 1; /* introduce some overdraw */
    dxt = (Sint16) lrint((double) a2/sab ) + od;

    t = 0;
    s = -2*a2*ry;
    d = 0;

    xp = x;
    yp = y - ry;

    /* Draw */
    result = 0;
    result |= SDL_SetRenderDrawBlendMode( renderer, ( a == 255 ) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND );

    /* "End points" */
    result |= pixelRGBA( renderer, xp, yp, r, g, b, a );
    result |= pixelRGBA( renderer, xc2 - xp, yp, r, g, b, a );
    result |= pixelRGBA( renderer, xp, yc2 - yp, r, g, b, a );
    result |= pixelRGBA( renderer, xc2 - xp, yc2 - yp, r, g, b, a );

    for (i = 1 ; i <= dxt ; i++)
    {
        xp--;
        d += t - b2;

        if (d >= 0)
            ys = yp - 1;
        else if (( d - s - a2 ) > 0)
        {
            if (( 2*d - s - a2 ) >= 0)
                ys = yp + 1;
            else
            {
                ys = yp;
                yp++;
                d -= s + a2;
                s += ds;
            }
        }
        else
        {
            yp++;
            ys = yp + 1;
            d -= s + a2;
            s += ds;
        }

        t -= dt;

        /* Calculate alpha */
        if (s != 0)
        {
            cp = (float) abs( d )/(float) abs( s );
            if (cp > 1.0)
            {
                cp = 1.0;
            }
        }
        else
        {
            cp = 1.0;
        }

        /* Calculate weights */
        weight = (Uint8) ( cp*255 );
        iweight = 255 - weight;

        /* Upper half */
        xx = xc2 - xp;
        result |= pixelRGBAWeight( renderer, xp, yp, r, g, b, a, iweight );
        result |= pixelRGBAWeight( renderer, xx, yp, r, g, b, a, iweight );

        result |= pixelRGBAWeight( renderer, xp, ys, r, g, b, a, weight );
        result |= pixelRGBAWeight( renderer, xx, ys, r, g, b, a, weight );

        /* Lower half */
        yy = yc2 - yp;
        result |= pixelRGBAWeight( renderer, xp, yy, r, g, b, a, iweight );
        result |= pixelRGBAWeight( renderer, xx, yy, r, g, b, a, iweight );

        yy = yc2 - ys;
        result |= pixelRGBAWeight( renderer, xp, yy, r, g, b, a, weight );
        result |= pixelRGBAWeight( renderer, xx, yy, r, g, b, a, weight );
    }

    /* Replaces original approximation code dyt = abs(yp - yc); */
    dyt = (Sint16) lrint((double) b2/sab ) + od;

    for (i = 1 ; i <= dyt ; i++)
    {
        yp++;
        d -= s + a2;

        if (d <= 0)
            xs = xp + 1;
        else if (( d + t - b2 ) < 0)
        {
            if (( 2*d + t - b2 ) <= 0)
                xs = xp - 1;
            else
            {
                xs = xp;
                xp--;
                d += t - b2;
                t -= dt;
            }
        }
        else
        {
            xp--;
            xs = xp - 1;
            d += t - b2;
            t -= dt;
        }

        s += ds;

        /* Calculate alpha */
        if (t != 0)
        {
            cp = (float) abs( d )/(float) abs( t );
            if (cp > 1.0)
            {
                cp = 1.0;
            }
        }
        else
        {
            cp = 1.0;
        }

        /* Calculate weight */
        weight = (Uint8) ( cp*255 );
        iweight = 255 - weight;

        /* Left half */
        xx = xc2 - xp;
        yy = yc2 - yp;
        result |= pixelRGBAWeight( renderer, xp, yp, r, g, b, a, iweight );
        result |= pixelRGBAWeight( renderer, xx, yp, r, g, b, a, iweight );

        result |= pixelRGBAWeight( renderer, xp, yy, r, g, b, a, iweight );
        result |= pixelRGBAWeight( renderer, xx, yy, r, g, b, a, iweight );

        /* Right half */
        xx = xc2 - xs;
        result |= pixelRGBAWeight( renderer, xs, yp, r, g, b, a, weight );
        result |= pixelRGBAWeight( renderer, xx, yp, r, g, b, a, weight );

        result |= pixelRGBAWeight( renderer, xs, yy, r, g, b, a, weight );
        result |= pixelRGBAWeight( renderer, xx, yy, r, g, b, a, weight );
    }

    return ( result );
}

int Graphics::pixelRGBA( SDL_Renderer* renderer, Sint16 x, Sint16 y, Uint8 r, Uint8 g, Uint8 b, Uint8 a )
{
    int result = 0;
    result |= SDL_SetRenderDrawBlendMode( renderer, ( a == 255 ) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND );
    result |= SDL_SetRenderDrawColor( renderer, r, g, b, a );
    result |= SDL_RenderDrawPoint( renderer, x, y );
    return result;
}


int Graphics::pixelRGBAWeight( SDL_Renderer* renderer, Sint16 x, Sint16 y, Uint8 r, Uint8 g, Uint8 b, Uint8 a, Uint32 weight )
{
    /*
    * Modify Alpha by weight
    */
    Uint32 ax = a;
    ax = (( ax*weight ) >> 8 );
    if (ax > 255)
    {
        a = 255;
    }
    else
    {
        a = (Uint8) ( ax & 0x000000ff );
    }

    return pixelRGBA( renderer, x, y, r, g, b, a );
}