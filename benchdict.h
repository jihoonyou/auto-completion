#ifndef BENCH_DICT_H
#define BENCH_DICT_H
#include <string>
using namespace std;
class benchdict
{
	public:
	/*Constructor*/
	benchdict();

	unsigned int getMin();
	void setMin(unsigned int n);

	unsigned int getStep();
	void setStep(unsigned int s);

	unsigned int getIter();
	void setIter(unsigned int i);

	string getDict();
	void setDict(string d);

	void benchAlgo();


	private:
	unsigned int min_size;
	unsigned int step_size;
	unsigned int num_iterations;
	string dictfile;

};
#endif
