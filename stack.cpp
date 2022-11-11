#include "stack.hpp"

using namespace ft;

int main()
{
	ft::Vector<int> myvector (2,200);        // vector with 2 elements

	ft::stack<int> first;                    // empty stack
	ft::stack<int> second (myvector);         // stack initialized to copy of deque
	
	//empty test
	cout << "Stack Second empty ? :";
	if(second.empty())
		cout <<"YES\n";
	else
		cout <<"NO\n";
	//size test
	cout << "size of second Stack : " << second.size() << endl;
}