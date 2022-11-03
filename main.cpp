#include "vector.hpp"
#include <vector>

using namespace ft;

int main()
{
	//test constructors and fill container
	Vector<string> vec0(5, "asalek");
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
	
	//fill container and display, and test the [] operator
	vec[5] = 9999;		//if you over pass or set a negative value a reference to the end of container is returned
	cout <<"vec[0]__" << vec[0] << endl;
	cout <<"vec[1]__" << vec[1] << endl;
	cout <<"vec[2]__" << vec[2] << endl;
	cout <<"vec[3]__" << vec[3] << endl;
	cout <<"vec[4]__" << vec[4] << endl;

	//iterator
	const Vector<int> vec3(4,33);
	ft::Vector<int>::iterator iter;
	ft::Vector<int>::citerator citer;
	iter = vec.begin();			//begin
	cout << *iter << "  <---  begin iterator value\n";
	iter = vec.end();			//end
	cout << *iter << "  <---  end iterator value\n";
	citer = vec3.cbegin();
	cout << *citer << "  <---  cbegin iterator value\n";
	citer = vec3.cend();
	cout << *citer << "  <---  cend iterator value\n";

	//methods

	cout << "front() :    " << vec.front() << endl;
	cout << "back() :     " << vec.back() << endl;
	cout << "size() :     " << vec.size() << endl;
	cout << "capacity() : " << vec.capacity() << endl;
	cout << "max_size() : " << vec.max_size() << endl;
	cout << "empty() :    " << vec.empty() << endl;
	try{cout << "at() :       " << vec.at(4) << endl;} catch(std::exception &e){cout << e.what(); }
	vec.reserve(990);
	cout << "reserve() the new capacity : " << vec.capacity() << endl;
	vec.shrink_to_fit();
	cout << "shrink_to_fit() new capacity : " << vec.capacity() << ", size : " << vec.size() << endl;
	cout << "resize() : ";
	try {vec.resize(2); cout << "Done\n";} catch(std::exception &e){cout << e.what(); }
	
	//test get_allocator
	{
		Vector<int> myvector;
		int *p;
		p = myvector.get_allocator().allocate(5);
		for (size_t i = 0; i < 5; i++)
			myvector.get_allocator().construct(&p[i], i);
		//display the vector content 0 1 2 3 4
		cout << "The allocated array contains : \n";
		for (size_t i = 0; i < 5; i++)
			cout << p[i] << endl;
		// destroy and deallocate
		for (size_t i = 0; i < 5; i++)
			myvector.get_allocator().destroy(&p[i]);
		myvector.get_allocator().deallocate(p, 5);				
	}

	//test relational operators
	{
		Vector<int> foo (3,100);   // three ints with a value of 100
		Vector<int> bar (2,200);   // two ints with a value of 200

		if (foo==bar) std::cout << "foo and bar are equal\n";
		if (foo!=bar) std::cout << "foo and bar are not equal\n";
		if (foo< bar) std::cout << "foo is less than bar\n";
		if (foo> bar) std::cout << "foo is greater than bar\n";
  		if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
		if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
	}
	vec.clear();

	//test swap function
	{
		Vector<int> vec(5, 200);
		Vector<int> vec2(6, 999);

		vec.swap(vec2);
		cout << "the first swap\n";
		for (size_t i = 0; i < 5; i++)
			cout << "vec :" << vec[i] << ",";
		cout << endl;
		for (size_t i = 0; i < 6; i++)
			cout << "vec2 :" << vec2[i] <<  ",";
		ft::swap(vec, vec2);
	}
	return 0;
}