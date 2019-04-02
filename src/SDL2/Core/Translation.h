//
// Created by ggeof
//

#ifndef GOLDEN_PHOENIX_TRANSLATION_H
#define GOLDEN_PHOENIX_TRANSLATION_H

// Custom headers
#include "Exceptions.h"
#include "GetResourcePath.h"

// C++ headers
#include <fstream>
#include <iostream>


class Translation
{
private :

    std::string _nameFileFr;
    std::string _nameFileEn;

    std::ifstream* _fileFr;
    std::ifstream* _fileEn;
    std::ifstream* _file;

    char _defaultLanguage; // Language : "F" -> French ; "E" -> English


public :
    Translation( char language = 'F' );

    ~Translation();

    //! Get the current language of the game
    char GetCurrentLanguage();

    //! Set the game to a new language
    void SetCurrentLanguage( char newLanguage );

    //! Return the _nbWord of the _word -1 if the _word not exist
    int SearchWord( const std::string& word, char language );

    //! Return the word
    std::string GetTranslation( int numWord );
};


#endif
	