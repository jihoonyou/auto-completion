#include "util.h"
#include "DictionaryBST.h"

/* Create a new Dictionary that uses a BST back end */
DictionaryBST::DictionaryBST(){}

/* Insert a word into the dictionary. */
bool DictionaryBST::insert(std::string word)
{
	auto check = DictSet.insert(word);
	return check.second;
	/*
	unsigned int psize = DictSet.size();
	DictSet.insert(word);
	if(DictSet.size() == psize + 1){
	return true;
	}
	return false;*/
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryBST::find(std::string word) const
{
	if(DictSet.find(word) != DictSet.end()){
		return true;
	}
	return false;
}

/* Destructor */
DictionaryBST::~DictionaryBST(){
	DictSet.clear();
}
