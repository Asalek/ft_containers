#include "vector.hpp"
#include <vector>

using namespace ft;

int main()
{
	Vector<int> vec(5, 77);
	Vector<int> vec2;
	vec2 = vec;
	ft::Vector<int>::iterator iter;
	iter = vec2.begin();
	cout << *iter << "  <---\n";
	vec[5] = 9999;		//if you passing or -1 value of vector size a reference to the end returned
	cout <<"0__" << vec[0] << endl;
	// cout <<"1__" << vec[1] << endl;
	// cout <<"2__" << vec[2] << endl;
	// cout <<"3__" << vec[3] << endl;
	// cout <<"4__" << vec[4] << endl;

	// cout << vec.front() << endl;
	// cout << vec.back() << endl;

	// try
	// {
	// 	vec.resize(87945632549863);
	// }
	// catch (std::bad_alloc &allocation)
	// {
	// 	std::cerr << "bad_alloc caught: " << allocation.what() << '\n';
	// }
	cout << vec.size() << endl;
	return 0;
}