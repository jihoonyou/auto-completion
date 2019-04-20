#include "util.h"
#include "DictionaryHashtable.h"

/* Create a new Dictionary that uses a Hashset back end */
DictionaryHashtable::DictionaryHashtable(){}

/* Insert a word into the dictionary. */
bool DictionaryHashtable::insert(std::string word)
{
	auto check = myHash.insert(word);
	return check.second;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryHashtable::find(std::string word) const
{
	if(myHash.find(word) != myHash.end()){
		return true;
	}
	return false;
}

/* Destructor */
DictionaryHashtable::~DictionaryHashtable(){
	myHash.clear();
}
