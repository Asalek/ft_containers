#include "vector.hpp"
using namespace ft;

int main()
{
	Vector<string> tupf;

	tupf[-1] = "9999";
	cout << tupf[-1] << endl;
	try
	{
		tupf.resize(87945632549863);
	}
	catch (std::bad_alloc &allocation)
	{
		std::cerr << "bad_alloc caught: " << allocation.what() << '\n';
	}
}