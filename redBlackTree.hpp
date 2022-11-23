#pragma once

#include <iostream>
using std::cout;
using std::endl;
using std::string;

namespace ft
{
	// Implementing Red-Black Tree in C++
	template<class T>
	struct node {
		T data;
		node *parent;
		node *left;
		node *right;
		int color;
		node():data(nullptr), parent(nullptr), left(nullptr), right(nullptr), color(0){}
		node(T _data):data(_data), parent(nullptr), left(nullptr), right(nullptr), color(0){}
	};
	template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class RedBlackTree
	{
		public:
			typedef ft::node*	node_pointer;
			typedef T		value_type;
		private:
			node_pointer	root;
			node_pointer	end;
			size_t			size;

			//	insertion
			void	insert(value_type data = value_type())
			{
				if (this->root == nullptr)
				{
					this->size++;
				}
			}
	};

	int main()
	{
		RedBlackTree<int> bst;
		bst.insert(55);
		bst.insert(40);
		bst.insert(65);
		bst.insert(60);
		bst.insert(75);
		bst.insert(57);

		bst.printTree();
		cout << endl
			<< "After deleting" << endl;
		bst.deleteNode(40);
		bst.printTree();
	}
}