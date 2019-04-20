#include "util.h"
#include "DictionaryTrie.h"

//Constructor for TSTNode
TSTNode::TSTNode()
{
	letter = ' ';
	freq = 0;
	right = 0;
	left = 0;
	middle = 0;
	keyNode = false;
	text = "";
}
//refactor setAtOnce
void TSTNode::setAtOnce(unsigned int num, bool b,std::string s)
{
	freq = num;
	keyNode = true;
	text = s;	
}

//getter method for the letter of the node
char TSTNode::getLetter()
{
	return letter;
} 

//setter method for the letter of the node
void TSTNode::setLetter(char a)
{
	letter = a;
}

//getter method for the frequency of the node
unsigned int TSTNode::getFreq()
{
	return freq;
}

//setter method for the frequency of the node
void TSTNode::setFreq(unsigned int num)
{
	freq = num;
}

//getter method of the pointer to the right of the node
TSTNode* TSTNode::getRight()
{
	return right;
}

//setter method of the pointer to the right of the node
void TSTNode::setRight(TSTNode* n)
{
	right = n;
}

//getter method of the pointer to the left of the node
TSTNode* TSTNode::getLeft()
{
	return left;
}

//setter method of the pointer to the left of the node
void TSTNode::setLeft(TSTNode* n)
{
	left = n;
}

//getter method of the pointer to the middle of the node
TSTNode* TSTNode::getMiddle()
{
	return middle;
}

//setter method of the pointer to the middle of the node
void TSTNode::setMiddle(TSTNode* n)
{
	middle = n;
}

//getter method for the check of whether of not the node is a key node
bool TSTNode::getKeyNode()
{
	return keyNode;
}

//setter method for the check of whether of not the node is a key node
void TSTNode::setKeyNode(bool b)
{
	keyNode = b;
}


std::string TSTNode::getText()
{
	return text;
}

void TSTNode::setText(std::string s)
{
	text = s;
} 

//destructor to prevent memory leaks
TSTNode::~TSTNode()
{
	delete right;
	delete left;
	delete middle;
}

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie()
{
	root = 0;
}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
	unsigned int count = 0;
	TSTNode* curr = root;
	std::vector<char> copy(word.length());

	//check if string is invalid(empty string)
  if(word == "")
	{
			return false;
	}

	//vector that holds each letter
	for(unsigned int i = 0; i < word.length(); i++)
	{
			copy[i] = word.at(i);		
	}

	if(root == nullptr)
	{
		root = new TSTNode();
		root->setLetter(copy[count]);
		curr = root;
	}

	while(curr)
	{
		if(curr->getLetter() == copy[count])
		{
			if(curr->getMiddle() == nullptr)
			{
				if(count == word.length() - 1)
				{	
					if(curr->getFreq() < freq)
					{
									curr->setFreq(freq);
							}
							return false;
				}
				TSTNode* temp = new TSTNode();
				curr->setMiddle(temp);
				curr = curr->getMiddle();
				curr->setLetter(copy[count + 1]);
				++count;

				if(count == word.length()-1)
				{
					/*	curr->setFreq(freq);
							curr->setKeyNode(true);
							curr->setText(word);*/
					curr->setAtOnce(freq,true,word);
					//Checking to make sure the frequency has been changed before returning
					if(curr->getFreq() == freq)
					{
						return true;
					}
				}
			}
			else
			{
				if(count == word.length()-1)
				{
					if(curr->getMiddle() != nullptr && curr->getKeyNode() == false)
					{
					/*		curr->setFreq(freq);
							curr->setKeyNode(true);
							curr->setText(word);*/
							curr->setAtOnce(freq,true,word);	
							//Checking to make sure the frequency has been changed before returning
							if(curr->getFreq() == freq)
							{
								return true;
							}
					}

					if(curr->getFreq() < freq)
					{
						curr->setFreq(freq);
					}
					return false;
					
				}
				else
				{
					curr = curr->getMiddle();
					count++;
				}
			}
		}	
		else if(curr->getLetter() < copy[count])
		{

			if(curr->getRight() == nullptr)
			{
				TSTNode* temp = new TSTNode();
				curr->setRight(temp);
				curr = curr->getRight();
				curr->setLetter(copy[count]);
				
				if(count == word.length() - 1)
				{
				/*curr->setFreq(freq);
					curr->setKeyNode(true);
					curr->setText(word);*/
					curr->setAtOnce(freq,true,word);					
					//Checking to make sure the frequency has been changed before returning
					if(curr->getFreq() == freq)
					{
						return true;
					}
				}
			}
			else
			{
					curr = curr->getRight();			
			}
		}	
		else if(copy[count] < curr->getLetter())
		{
			if(curr->getLeft() == nullptr)
			{
				TSTNode* temp = new TSTNode();
				curr->setLeft(temp);
				curr = curr->getLeft();
				curr->setLetter(copy[count]);

				if(count == word.length() -1)
				{
					/*curr->setFreq(freq);
						curr->setKeyNode(true);
						curr->setText(word);*/
					curr->setAtOnce(freq,true,word);
					//Checking to make sure the frequency has been changed before returning
					if(curr->getFreq() == freq)
					{
						return true;
					}
				}
			}
			else
			{
					curr = curr->getLeft();
			}			
		}
		else
		{
			return false;
		}		
	}
	return false;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
	//Making sure a root exist
	if(!root){
		return false;
	}

	TSTNode* curr = root;
	unsigned int count = 0;
	std::vector<char> copy(word.length());

	for(unsigned int i = 0; i < word.length(); i++)
	{
		copy[i] = word.at(i);
	}

	//traverses down the trie until we find the word. If the word does not exist, return false
	while(curr)
	{
		if(curr->getLetter() == copy[count])
		{
			//two checks for the existence of the word in the trie
			//first check for if the last letter of the word is at the edge of the trie
			//second check for if the last letter of the word is within the trie
			if( curr->getMiddle() == nullptr && curr->getKeyNode() == true)
			{
				return true;
			}
			if(count == word.length()-1 && curr->getKeyNode() == true)
			{
				return true;
			}
			curr = curr->getMiddle();
			//incrementation to indicate the movement to the next letter in the word
			count++;
		}	
		else if(curr->getLetter() < copy[count])
		{
			curr = curr->getRight();
		}	
		else if(copy[count] < curr->getLetter())
		{
			curr = curr->getLeft();
		}
		else
		{
			return false;
		}
	}
  return false;
}

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
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)
{
  std::vector<std::string> words;

	//return empty vector when dictionary is empty.
	if(!root){
		return words;
	}
 	//return empty vector if prefix is empty
 	if(prefix == " ")
	{
			std::cout << "Invalid Input. Please retry with correct input"<< std::endl;
			return words;
	}

	TSTNode* curr = root;
	TSTNode* temp;
	unsigned int count = 0; 
	std::vector<char> copy(prefix.length());

	for(unsigned int i = 0; i < prefix.length(); i++)
	{
		copy[i] = prefix.at(i);
	}

	//Moving to the node that contains the last letter in the prefix
	//this will enable us to begin from the prefix to find words that have it
	while(curr)
	{
		if(curr->getLetter() == copy[count])
		{
			if(count == prefix.length()-1)
			{
				temp = curr;
				break;
			}
			curr = curr->getMiddle();
			count++;
		}	
		else if(curr->getLetter() < copy[count])
		{
			curr = curr->getRight();
		}	
		else if(copy[count] < curr->getLetter())
		{
			curr = curr->getLeft();
		}
		else
		{
			std::cout << "Invalid Input. Please retry with correct input"<< std::endl;
			return words;
		}
	}

	//return empty vector if prefix has character not in the dictionary
	if(curr == nullptr)
	{
		std::cout << "Invalid Input. Please retry with correct input"<< std::endl;
		return words;
	}
	
	//Creating a queue for the storage of words that contain the prefix
	//Also creating an ordered set to sort the words from the queue based on the frequencies
	std::queue<TSTNode*> Q;
	std::set<std::pair<unsigned int, TSTNode*>> oSet;
	

	/**************changes************/
	if(temp->getKeyNode() == true){
		oSet.insert(std::make_pair(temp->getFreq(), temp));
	}
	temp = temp->getMiddle();
	Q.push(temp);

	//doing breath first search through the nodes
	while(!Q.empty()){

		if(temp->getKeyNode() == true){
			oSet.insert(std::make_pair(temp->getFreq(), temp));
		}

		if(temp->getLeft() != nullptr){
			Q.push(temp->getLeft());			
		}
		if(temp->getMiddle() != nullptr){
			Q.push(temp->getMiddle());			
		}
		if(temp->getRight() != nullptr){
			Q.push(temp->getRight());			
		}
		Q.pop();
		temp = Q.front();
	}

	//check to make sure that our words from the queue were successfully insereted into the ordered set
	if(oSet.empty())
	{
		return words;	
	}

	//for loop uses a reverse iterator (for the sake of the words in the words vector to be in the correct order) to go through the ordered set and add the words
	//to the words vector 
	for(std::set<std::pair<unsigned int, TSTNode*>>::reverse_iterator rit=oSet.rbegin() ; rit != oSet.rend(); ++rit )
	{
		if(words.size() == num_completions){
			break;	
		}
		words.push_back(rit->second->getText());
	}
	return words;
}

/* Destructor */
DictionaryTrie::~DictionaryTrie()
{
		delete root;
}


