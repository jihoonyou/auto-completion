/**
 *  CSE 100 PA3 C++ Autocomplete
 *  Authors: Jor-el Briones, Christine Alvarado
 */

#ifndef DICTIONARY_TRIE_H
#define DICTIONARY_TRIE_H

#include <vector>
#include <string>
#include <queue>
#include <set>

class TSTNode
{
	public:
	/*Constructor*/
	TSTNode();

	//refactor function
	void setAtOnce(unsigned int num, bool b, std::string s);

	//getter and setter methods for the private members
  char getLetter();
	void setLetter(char a);

	unsigned int getFreq();
	void setFreq(unsigned int num);

	TSTNode* getRight();
	void setRight(TSTNode* n);

	TSTNode* getLeft();
	void setLeft(TSTNode* n);

	TSTNode* getMiddle();
	void setMiddle(TSTNode* n);	
	
	bool getKeyNode();
	void setKeyNode(bool b);

	std::string getText();
	void setText(std::string s);

	/*Destructor*/
	~TSTNode();

	private:
	//each node in the trie holds a letter
	char letter;

	//enables tracking of frequencies for keynodes.
	unsigned int freq;

	//pointers to enable travel down the trie
  TSTNode* right;
	TSTNode* left;
	TSTNode* middle;

	//checks to see if the node is a keynode or not
	bool keyNode;

	std::string text;
};

/**
 *  The class for a dictionary ADT, implemented as a trie
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie, but you must use one or the other.
 *
 */
class DictionaryTrie
{
public:

  /* Create a new Dictionary that uses a Trie back end */
  DictionaryTrie();

  /* Insert a word with its frequency into the dictionary.
   * Return true if the word was inserted, and false if it
   * was not (i.e. it was already in the dictionary or it was
   * invalid (empty string) */
  bool insert(std::string word, unsigned int freq);

  /* Return true if word is in the dictionary, and false otherwise */
  bool find(std::string word) const;

  /* Return up to num_completions of the most frequent completions
   * of the prefix, such that the completions are words in the dictionary.
   * These completions should be listed from most frequent to least.
   * If there are fewer than num_completions legal completions, this
   * function returns a vector with as many completions as possible.
   * If no completions exist, then the function returns a vector of size 0.
   * The prefix itself might be included in the returned words if the prefix
   * is a word (and is among the num_completions most frequent completions
   * of the prefix)
   */
  std::vector<std::string>
  predictCompletions(std::string prefix, unsigned int num_completions);

	//Getter and seeter for the private member root
	TSTNode* getRoot();
	void setRoot(TSTNode* n);

  /* Destructor */
  ~DictionaryTrie();

private:
  // Add your own data members and methods here 
  // TSTNode pointer object for the root of the trie 
	TSTNode* root; 
 };
#endif // DICTIONARY_TRIE_H
