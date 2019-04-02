//
// Created by ggeof
//

#include "Translation.h"

#include "Exceptions.h"


Translation::Translation(){
	_nameFileFr="./data/Translation/Fr";
	_nameFileEn="./data/Translation/En";
	_fileFr =  new 	std::ifstream(_nameFileFr, std::ios::in);
	_fileEn =  new 	std::ifstream(_nameFileEn, std::ios::in);
	_defaultLangage = 'F';

	if(!_fileFr || !_fileEn){
        throw Exception( "A file translation failed to load!", __FILE__, __LINE__ );
	}
	_file = _fileFr;
}


Translation::Translation(char _langage){
	_nameFileFr="./data/Translation/Fr";
	_nameFileEn="./data/Translation/En";
	_fileFr =  new 	std::ifstream(_nameFileFr, std::ios::in);
	_fileEn =  new 	std::ifstream(_nameFileEn, std::ios::in);
	_defaultLangage = _langage;

	if(!_fileFr || !_fileEn){
        throw Exception( "A file translation failed to load!", __FILE__, __LINE__ );
	}
	_file = _fileFr;
}

Translation::~Translation(){
	_fileEn->close();
	_fileFr->close();

	delete _file;
	delete _fileFr;
	delete _fileEn;

}

char Translation::GetDefaultLangage(){
	return _defaultLangage;
}

void Translation::Translation::SetDefaultLangage(char _newLangage){
	if(_newLangage=='F'){
		_defaultLangage = _newLangage;
		_file = _fileFr;
	}
	else if(_newLangage=='E'){
		_defaultLangage = _newLangage;
		_file = _fileEn;
	}

}

int Translation::SearchWord(std::string _word, char _langage){
	if(_langage=='F')
		_file=_fileFr;
	else if(_langage=='E')
		_file=_fileEn;
	else
		return -1;

	int _numWord = 0;
	std::string _wordb;
	bool _trouve=false;

	_file->seekg(0,std::ios::beg);

	while(!(_file->eof()) && !_trouve)
	{
		getline(*_file,_wordb);
		_numWord++;
		if(_wordb==_word)
			_trouve=true;
	}
	

	if(_trouve==false)
		return -1;

	if(_defaultLangage=='F')
		_file=_fileFr;
	else if(_defaultLangage=='E')
		_file=_fileEn;
	return _numWord;
}

std::string Translation::GetTranslation(int _numWord){
	_file->seekg(0,std::ios::beg);
	std::string trans;
	for(size_t i = 1; i <= _numWord; i++)
		getline(*_file,trans);
	return trans;
}