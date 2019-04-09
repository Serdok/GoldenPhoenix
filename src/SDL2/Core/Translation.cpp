//
// Created by ggeof
//

#include "Translation.h"

Translation::Translation( char language )
{
    _fileFr = new std::ifstream( GetResourcePath("Translation/Fr.lang") );
    _fileEn = new std::ifstream( GetResourcePath("Translation/En.lang") );
    _defaultLanguage = language;

    if (!_fileFr->good() || !_fileEn->good())
        throw Exception( "A translation file failed to load!", __FILE__, __LINE__ );

    _file = _fileFr;
}

Translation::~Translation()
{
    _fileEn->close();
    _fileFr->close();

    _file = nullptr;
    delete _fileFr;
    delete _fileEn;

}

char Translation::GetCurrentLanguage()
{
    return _defaultLanguage;
}

void Translation::Translation::SetCurrentLanguage( char newLanguage )
{
    _defaultLanguage = newLanguage;

    if (newLanguage == 'F')
        _file = _fileFr;
    else if (newLanguage == 'E')
        _file = _fileEn;

}

int Translation::SearchWord( const std::string& word, char language )
{
    if (language == 'F')
        _file = _fileFr;
    else if (language == 'E')
        _file = _fileEn;
    else
        return -1;

    int numWord = 0;
    std::string wordb;
    bool trouve = false;

    _file->seekg( 0, std::ios::beg );

    while (!( _file->eof()) && !trouve)
    {
        getline( *_file, wordb );
        numWord++;
        if (wordb == word)
            trouve = true;
    }


    if (_defaultLanguage == 'F')
        _file = _fileFr;
    else if (_defaultLanguage == 'E')
        _file = _fileEn;

    if (!trouve)
        return -1;

    return numWord;
}

std::string Translation::GetTranslation( int numWord )
{
    _file->seekg( 0, std::ios::beg );
    std::string trans;
    if(numWord == -1)
    	return " ";
    for (size_t i = 1 ; i <= numWord ; i++)
        getline( *_file, trans );
    return trans;
}