//
// Created by ggeof
//

#ifndef GOLDEN_PHOENIX_TRANSLATION_H
#define GOLDEN_PHOENIX_TRANSLATION_H

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

    char _defaultLangage; // Langage : "F" -> Frenche ; "E" -> English

	protected :


	public :

	Translation();

	Translation(char langage);

	~Translation();

    // Return _defaultLangage
    char GetDefaultLangage();

    // Change _defaultLangage
    void SetDefaultLangage(char _newLangage);

    // Return the _nbWord of the _word -1 if the _word not exist
    int SearchWord(std::string _word, char _langage);

    // Return the word
    std::string GetTranslation(int _numWord);
};


#endif
	