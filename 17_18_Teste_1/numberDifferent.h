#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include <string>
using namespace std;

template <class T>
unsigned int numberDifferent (const vector<T> & v1)
{
	vector<T> tmp = v1;
/*
	for (std::vector<int>::size_type i = 0; i != tmp.size(); i++)
	{
		for (std::vector<int>::size_type j = i + 1; j != tmp.size(); j++)
		{
			if (tmp[i] == tmp[j])
			{
				tmp.erase(tmp.begin() + j);
				j--;
			}
		}
	}
*/
	sort( tmp.begin(), tmp.end() );
	tmp.erase( unique( tmp.begin(), tmp.end() ), tmp.end() );

	return tmp.size();
}
