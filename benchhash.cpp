#include "util.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

/*source: http://www.cse.yorku.ca/~oz/hash.html */
unsigned int hFunc1(string text, unsigned int size)
{
	unsigned long hash = 5381;
	unsigned long c;
	unsigned long output;

	for (unsigned int i= 0; i < text.length(); i++)
	{
		c = (long) text[i];
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}
	output = (unsigned int)hash % size;
	return output;
}

/*source: http://www.cse.yorku.ca/~oz/hash.html */
int hFunc2(string text, unsigned int size)
{
	unsigned long hash = 0;
	unsigned long output;

	for (unsigned int i = 0; i < text.length(); i++)
	{
		hash = text[i] + (hash << 6) + (hash << 16) - hash;
	}
	output = (unsigned int)hash % size;
	return output;
}

int main (int argc, char* argv[])
{

	if(argc != 3)
	{
		cout << "Invalid number of arguments" <<endl;
	}

	string dictfile = argv[1];
	unsigned int num_words = atoi(argv[2]);
	unsigned int size = 2*num_words;
	vector<string> hashTable;
	unsigned int worst1 = 0;
	unsigned int worst2 = 0;
  double aver1 = 0;
	double aver2 = 0;
	double temp1 = 0;
	double temp2 = 0;


	Utils tt;
	ifstream dictionary;
	dictionary.open(dictfile);
	tt.load_vector(hashTable, dictionary, num_words);

	//Testing hFunc1
	cout << endl;
	cout << "Printing the statistics for hashFunction1 with hash table size " <<size << endl;

	vector<int> htL(size);
	vector<int> htR(size);
	const int checkL = -1;
	const int checkR = 0;


	for(unsigned int i = 0; i < size; i++)
	{
		htL[i] = checkL;
		htR[i] = checkR;
	}


	/*Hash value*/
	for(unsigned int i = 0; i < num_words; i++)
	{
		htL[hFunc1(hashTable[i], size)]++;
	}

	/*hit slots*/
	for(unsigned int i = 0; i < size; i++)
	{
		if(htL[i] == checkL)
		{
			continue;
		}
		else
		{
			htR[htL[i]]++;
		}
	}

	/*results*/
	cout << "#hits\tslots receiving the #hits" << endl;
	for(unsigned int i = 0; i < size; i++)
	{
		if(htR[i] == checkR)
		{
			continue;
		}
		else
		{
			cout << i << "\t" << htR[i] << endl;
		}
		worst1++; 
	}
	/*average number of steps*/
	for(unsigned int i = size; 0 < i; i--)
	{
		if(htR[i] == checkR)
		{
			continue;
		}
		else
		{
			temp1 += htR[i];
			aver1 += i*temp1;	
		
		}
		 
	}
	cout << "The average number of steps for a successful search for hash function 1 would be " << aver1/num_words << endl;
	cout << "The worst case steps that would be needed to find worst is " << worst1 - 1  << endl;

	//Testing hFunc2
	cout << endl;
	cout << "Printing the statistics for hashFunction2" << endl;

	vector<int> htU(size);
	vector<int> htD(size);
	const int checkU = -1;
	const int checkD = 0;


	for(unsigned int i = 0; i < size; i++)
	{
		htU[i] = checkU;
		htD[i] = checkD;
	}


	/*Hash value*/
	for(unsigned int i = 0; i < num_words; i++)
	{
		htU[hFunc2(hashTable[i], size)]++;
	}

	/*hit slots*/
	for(unsigned int i = 0; i < size; i++)
	{
		if(htU[i] == checkU)
		{
			continue;
		}
		else
		{
			htD[htU[i]]++;
		}
	}

	/*results*/
	cout << "#hits\tslots receiving the #hits" << endl;
	for(unsigned int i = 0; i < size; i++)
	{
		if(htD[i] == checkD)
		{
			continue;
		}
		else
		{
			cout << i << "\t" << htD[i] << endl;
		}
		worst2++;	
	}
	/*average number of steps*/
	for(unsigned int i = size; 0 < i; i--)
	{
		if(htD[i] == checkD)
		{
			continue;
		}
		else
		{
			temp2 += htD[i];
			aver2 += i*temp2;	
		}
		 
	}
	cout << "The average number of steps for a successful search  for hash function 2 would be " << aver2/num_words << endl;
	cout << "The worst case steps that would be needed to find worst is " << worst2 - 1  << endl;



		cout << endl;
		cout << "First Test " <<endl;
    cout << "hash function 1 of 'say' is " << hFunc1("say", size) << endl;
    cout << "hash function 2 of 'say' is " << hFunc2("say", size) << endl;

		cout << "Second Test" <<endl;
		cout << "hash function 1 of 'hi' is " << hFunc1("hi", size) << endl;
		cout << "hash function 2 of 'hi' is " << hFunc2("hi", size) << endl;

		cout << "Thrid Test" <<endl;
	  cout << "hash function 1 of 'bye' is " << hFunc1("bye", size) << endl;
    cout << "hash function 2 of 'bye' is " << hFunc2("bye", size) << endl;
}

