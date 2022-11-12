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
		cout << "get_allocator allocated array contains : \n";
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
		std::swap(vec, vec2);
	}

	{
		Vector<int> myvector(10);

		// set some values (from 1 to 10)
		for (int i=0; i<=10; i++)
			myvector[i] = i+1;

		// erase the 6th element
		myvector.erase (myvector.begin()+5);

		// erase the first 3 elements:
		myvector.erase (myvector.begin(),myvector.begin()+3);

		std::cout << "\nmyvector after erase() contains:";
		for (unsigned i=0; i<myvector.size(); ++i)
		std::cout << ' ' << myvector[i];
		std::cout << '\n';
	}

	//test assign
	{
		Vector<int> first;
		Vector<int> second;

		first.assign (7,100);             // 7 ints with a value of 100

		Vector<int>::iterator it;
		it=first.begin()+1;
		second.assign (it,first.end()); // the 5 central values of first

		std::cout << "Size of first: " << int (first.size()) << '\n';
		std::cout << "Size of second: " << int (second.size()) << '\n';
	}
	//test push_back
	
	cout << "size() before push_back : " << vec.size() << endl;
	cout << "capacity() before push_back : " << vec.size() << endl;
	for (size_t i = 0; i < 20; i++)
		vec.push_back(i);
	cout << "size() after push_back : " << vec.size() << endl;
	cout << "capacity() after push_back : " << vec.capacity() << endl;
	//test pop_back
	cout << "pop_back() : ";
	for (size_t i = 0; i < 10; i++)
		vec.pop_back();
	for (size_t i = 0; i < 10; i++)
		cout << vec[i] << " ";
	cout << "\n";
	//test insert
	vec.insert(vec.begin() + 2, 1);
	cout << "size() after insert : " << vec.size() << endl;
	cout << "inserted values one : ";
	for (size_t i = 0; i < vec.size(); i++)
		cout << vec[i] << " ";
	cout << "\n";
	//insert many
	cout << "inserted values many : ";
	vec.insert(vec.begin() + 2, 3, 7);
	for (size_t i = 0; i < vec.size(); i++)
		cout << vec[i] << " ";
	cout << "\n";
	//insert many with iterators
	cout << "inserted values with iterators : ";
	Vector<int> v2(4, 144);
	
	vec.insert(vec.begin(), v2.begin(), v2.end());
	for (size_t i = 0; i < vec.size(); i++)
		cout << vec[i] << " ";


	try{vec.erase(vec.begin() , vec.end()); cout<< "\nerase() done successfully\n";}catch(std::exception &e) { cout << e.what(); }
}
