#include "stack.hpp"

using namespace ft;

int main()
{
	ft::Vector<int> myvector (2,200);        // vector with 2 elements

	ft::stack<int> first;                    // empty stack
	if(first.empty())
		cout <<"YES\n";
	else
		cout <<"NO\n";
	// ft::stack<int> second (myvector);         // stack initialized to copy of deque
}