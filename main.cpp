#include "vector.hpp"
#include <vector>

using namespace ft;

int main()
{
	//test constructors and fill container
	Vector<int> vec(5, 77);
	Vector<int> vec2;
	vec2 = vec;

	//test errors
	try{
		Vector<int> vec(5, 77);
		}
	catch(std::exception &e){
		cout << e.what();
	}

	//iterator
	ft::Vector<int>::iterator iter;
	iter = vec2.begin();			//begin
	cout << *iter << "  <---  iterator value\n";
	
	//fill container and display
	vec[5] = 9999;		//if you over pass or set -1 as a value a reference to the end of container is returned
	cout <<"0__" << vec[0] << endl;
	cout <<"1__" << vec[1] << endl;
	cout <<"2__" << vec[2] << endl;
	cout <<"3__" << vec[3] << endl;
	cout <<"4__" << vec[4] << endl;

	//methods
	cout << "front() : " << vec.front() << endl;
	cout << "back() : " << vec.back() << endl;
	cout << "size() : " << vec.size() << endl;
	return 0;
}