#include "util.h"
#include "benchdict.h"
#include "DictionaryTrie.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*Create a new benchdict*/
benchdict::benchdict()
{
min_size = 0;
step_size = 0;
num_iterations = 0;
dictfile = "";
}

//getter method for the minimum size 
unsigned int benchdict::getMin()
{
	return min_size;
}

//setter method for the minimum size
void benchdict::setMin(unsigned int n)
{
	min_size = n;
}

//getter method for the step size
unsigned int benchdict::getStep()
{
	return step_size;
}

//setter method for the step size
void benchdict::setStep(unsigned int s)
{
	step_size = s;
}

//getter method for the number of iterations
unsigned int benchdict::getIter()
{
	return num_iterations;
}

//setter method for the number of iterations
void benchdict::setIter(unsigned int i)
{
	num_iterations = i;
}

//getter method for the name of the dictionary
string benchdict::getDict()
{
	return dictfile;
}

//setter method for the name of the dictionary
void benchdict::setDict(string d)
{
	dictfile = d;
}

//Algorithm function for the benchmarking the dictionaries
void benchdict::benchAlgo()
{
	
	ifstream dictionary;
	dictionary.open(dictfile);
	vector<string> nextWords;
	long long averageTime;
	unsigned int counts = 0;
	string str;
	Timer tt;
	Utils ut;
	DictionaryTrie* dicT = new DictionaryTrie();
	DictionaryBST* dicB = new DictionaryBST();
	DictionaryHashtable* dicH = new DictionaryHashtable();


  //counts the number of lines in the text 
	while(getline(dictionary,str))
	{
		counts++;	
	}

	//resetting the stream
	dictionary.clear();
	dictionary.seekg( 0, std::ios::beg );

	//Beginning Trie algorithm
	cout << endl;
	cout << endl;
	cout << "DictionaryTrie" << endl;

	//We will be running through the algorithm based on the number of iterations given
	for(unsigned int i = 0; i < num_iterations; i++ )
	{
		//error message for number of words
		if(counts < (min_size + i*step_size))
		{
			cout << "Warning: there are less words in the file compared to the dictionary size." << endl;
		}

		//resetting the stream at the beginning of each iteration
		dictionary.clear();
		dictionary.seekg( 0, std::ios::beg );

		//clearing the existing words to make sure this vector does not stack up with words
		nextWords.clear();

		//resetting the average time to 0 before each iteration
		averageTime = 0;
		
		//calling Utils functions in order to load up the dictionary and then loading up a vector to hold the next 100 words
		ut.load_dict(*dicT, dictionary, min_size + i*step_size);
		ut.load_vector(nextWords, dictionary, 100);

		//calculating the time in takes attempting to find the 100 words in the dictionary
		//we do this many times for the process of finding an average time
		for(int k = 0; k < 100; k++)
		{
			tt.begin_timer();
			for(int j = 0; j < 100; j++)
			{
				dicT->find(nextWords[j]);
			}
			averageTime += tt.end_timer();
		}

		//finalizing the average time and printing it out respective to its current size
		averageTime /= 100;		
		cout << min_size + i*step_size << "   " << averageTime << endl;
	}
	
	//resetting the stream before moving onto the next data structure
	dictionary.clear();
	dictionary.seekg( 0, std::ios::beg );

	//Beginning BST algorithm
	//The code below until the next data structure is exactly the same as it was for the Trie
	//Same algorithm, different data structure
	cout << endl;
	cout << endl;
	cout << "DictionaryBST" << endl;

	for(unsigned int i = 0; i < num_iterations; i++ )
	{
		if(counts < (min_size + i*step_size))
		{
			cout << "Warning: there are less words in the file compared to the dictionary size." << endl;
		}
		dictionary.clear();
		dictionary.seekg( 0, std::ios::beg );

		nextWords.clear();

		averageTime = 0;

		ut.load_dict(*dicB, dictionary, min_size + i*step_size);
		ut.load_vector(nextWords, dictionary, 100);

		for(int k = 0; k < 100; k++)
		{
			tt.begin_timer();
			for(int j = 0; j < 100; j++)
			{
				dicB->find(nextWords[j]);
			}
			averageTime += tt.end_timer();
		}
		averageTime /= 100;		
		cout << min_size + i*step_size << "   " << averageTime << endl;
	}

	dictionary.clear();
	dictionary.seekg( 0, std::ios::beg );

	//Beginning Hash Table algorithm
	//Once again, Same algorithm, different data structure
	cout << endl;
	cout << endl;
	cout << "DictionaryHashtable" << endl;

	for(unsigned int i = 0; i < num_iterations; i++ )
	{
		if(counts < (min_size + i*step_size))
		{
			cout << "Warning: there are less words in the file compared to the dictionary size." << endl;
		}

		dictionary.clear();
		dictionary.seekg( 0, std::ios::beg );

		nextWords.clear();

		averageTime = 0;

		ut.load_dict(*dicH, dictionary, min_size + i*step_size);
		ut.load_vector(nextWords, dictionary, 100);

		for(int k = 0; k < 100; k++)
		{
			tt.begin_timer();
			for(int j = 0; j < 100; j++)
			{
				dicH->find(nextWords[j]);
			}
			averageTime += tt.end_timer();
		}
		
		averageTime /= 100;		
		cout << min_size + i*step_size << "   " << averageTime << endl;
	}

	//deleting to prevent memory leaks. Also closing the dictionary file
	delete dicT;
	delete dicB;
	delete dicH;
	dictionary.close();
}

int main (int argc, const char *argv[])
{

	//Making sure that the user inputs all 4 necessary arguments for this program
	if(argc != 5)
	{
		cout << "Incorrect number of inputs.\n";
		return -1;
	}

	//variables to store each argument's value
	unsigned int m,s,n;
	string d;

	m = atoi(argv[1]);
	s = atoi(argv[2]);
	n = atoi(argv[3]);
	d = argv[4];

	//creating a benchdict object and setting its members to the given arguments
	benchdict* bm = new benchdict();

	bm->setMin(m);
	bm->setStep(s);
	bm->setIter(n);
	bm->setDict(d);

	//calling the algorithm function in order to calculate average times for iterations of all 3 structures
	bm->benchAlgo();

	//deleting to prevent memory leak
	delete bm;	
	return 0;	

}
