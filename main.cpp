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
	
	//fill container and display
	vec[5] = 9999;		//if you over pass or set -1 as a value a reference to the end of container is returned
	cout <<"vec[0]__" << vec[0] << endl;
	cout <<"vec[1]__" << vec[1] << endl;
	cout <<"vec[2]__" << vec[2] << endl;
	cout <<"vec[3]__" << vec[3] << endl;
	cout <<"vec[4]__" << vec[4] << endl;

	//iterator
	ft::Vector<int>::iterator iter;
	iter = vec.begin();			//begin
	cout << *iter << "  <---  begin iterator value\n";
	iter = vec.end();				//end
	cout << *iter << "  <---  end iterator value\n";


	//methods
	cout << "front() :    " << vec.front() << endl;
	cout << "back() :     " << vec.back() << endl;
	cout << "size() :     " << vec.size() << endl;
	cout << "capacity() : " << vec.capacity() << endl;
	cout << "max_size() : " << vec.max_size() << endl;
	cout << "empty() :    " << vec.empty() << endl;
	try{cout << "at() :       " << vec.at(4) << endl;} catch(std::exception &e){cout << e.what(); }
	return 0;
}