#include<iostream>
#include<string>
#include<algorithm>
#include<set>
#include<cstdlib>
#include "util.h"
#include "DictionaryTrie.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"
#define LETTERS 26
using namespace std;


int main(int argc, char** argv)
{
//	int test = 1;
  //Initialize words
  vector<std::string> words;
  vector<string>::iterator wit;
  vector<string>::iterator wen;
  //initialize nonwords
  set<string> nope;
  set<string>::iterator nit;
  set<string>::iterator nen;

  //Initialize data structures
  DictionaryBST d_bst;
  DictionaryHashtable d_ht;
  DictionaryTrie dt;
  int t_bst, t_ht, tt;

  words.push_back("harry");
  words.push_back("sriram");
  words.push_back("cse");
  words.push_back("crucio");
  words.push_back("autocomplete");
  words.push_back("harr");
  words.push_back("srirat");
 
  
  
  cout << "Inserting into Dictionaries..." << endl;

  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Inserting: \"" << *wit << "\"... ";
      t_bst = d_bst.insert(*wit);
      t_ht = d_ht.insert(*wit);
      tt = dt.insert(*wit, 1);
      //cout << t_bst << " " << t_ht << " "<< tt << "... ";
      if(!t_bst)
				{
	  			cout << "failed for DictionaryBST... ";
				}
      if(!t_ht)
				{
	  			cout << "failed for DictionaryHashset... ";
				}
      if(!tt)
				{
	  			cout << "failed for DictionaryTrie... ";
				}
      if(t_bst && t_ht && tt)
				{
	  			cout << "PASSED! :D ";
				}
      cout << endl;
    }

  cout << endl << "Re-inserting elements that were just inserted into Dictionaries..." << endl;

  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Inserting: \"" << *wit << "\"... ";
      t_bst = d_bst.insert(*wit);
      t_ht = d_ht.insert(*wit);
      tt = dt.insert(*wit, 1);
      if(t_bst)
        {
          cout << "failed for DictionaryBST... ";
        }
      if(t_ht)
        {
          cout << "failed for DictionaryHashset... ";
        }
      if(tt)
        {
          cout << "failed for DictionaryTrie... ";
        }
      if(!t_bst && !t_ht && !tt)
        {
          cout << "PASSED! :D ";
        }
      cout << endl;
    }

  cout << endl;

  
/*You are supposed to add more test cases in this file */
  
	cout << "Finding elements in the Dictionaries..." << endl;

	wit = words.begin();
	wen = words.end();
	for(; wit != wen; ++wit)
		{
				cout << "Finding: \"" << *wit << "\"... ";
				t_bst = d_bst.find(*wit);
      	t_ht = d_ht.find(*wit);
      	tt = dt.find(*wit);

      	if(!t_bst)
        	{
          	cout << "failed for DictionaryBST... ";
        	}	
      	if(!t_ht)
        	{
          	cout << "failed for DictionaryHashset... ";
        	}
      	if(!tt)
        	{
          	cout << "failed for DictionaryTrie... ";
        	}
      	if(t_bst && t_ht && tt)
        	{
          	cout << "PASSED! :D ";
        	}
      cout << endl;
    }


	//Testing to see if find fails for a word that does not exist in the trie
	//"har" is an arbitrary choice in consideration of the already existing word "harry"

	cout << endl;	
	cout << "Attempting to find an element in Dictionaries that doesn't exist..." << endl;	

	cout << "Finding: \"" << "har" << "\"... ";	

	t_bst = d_bst.find("har");
	t_ht = d_ht.find("har");
	tt = dt.find("har");

	if(!t_bst && !t_ht && !tt)
		{
			cout << "Not found (PASSED! :D) ";
		}
	cout << endl;

	//For the testing for correctly updated frequencies, we have already added checks within the cpp code to make sure that the frequencies 
	//do change before returning. Comments for those have been placed in the cpp file



	//predict completion test
	vector<string> predictTester;
	predictTester =	dt.predictCompletions("sri", 2);
	for(unsigned int i = 0; i < predictTester.size(); i++)
	{
		cout << predictTester[i] << endl;
	}

	//If num_completions is less than the number of legal completions
	vector<string> predictTester1;
	predictTester1 =	dt.predictCompletions("har", 1);
	for(unsigned int i = 0; i < predictTester1.size(); i++)
	{
		cout << predictTester1[i] << endl;
	}
	//If the number of legal completions is less than that specified by num_completions	
	vector<string> predictTester2;
	predictTester2 =	dt.predictCompletions("sri", 5);
	for(unsigned int i = 0; i < predictTester2.size(); i++)
	{
		cout << predictTester2[i] << endl;
	}
	
	//If there are no legal completions
	vector<string> predictTester3;
	predictTester3 =	dt.predictCompletions("tttt", 5);
	for(unsigned int i = 0; i < predictTester3.size(); i++)
	{
		cout << predictTester3[i] << endl;
	}
	
	//in case prefix itself is a word
	vector<string> predictTester4;
	predictTester4 =	dt.predictCompletions("sriram", 5);
	for(unsigned int i = 0; i < predictTester4.size(); i++)
	{
		cout << predictTester4[i] << endl;
	}

	//If inputs is non dicinotary character	
	vector<string> predictTester5;
	predictTester5 =	dt.predictCompletions("asdwqds", 5);
	for(unsigned int i = 0; i < predictTester5.size(); i++)
	{
		cout << predictTester5[i] << endl;
	}
	
	

  return 0;




}
