#pragma once

#define BLACK 1
#define RED 0
#include <iostream>
using std::cout;
using std::endl;
using std::string;

namespace ft
{
	// Implementing Red-Black Tree in C++
	template<class T>
	struct node {
		typedef T	value_type;
		value_type data;
		node *parent;
		node *left;
		node *right;
		bool color;
		node():data(nullptr), parent(nullptr), left(nullptr), right(nullptr), color(0){}
		node(T _data):data(_data), parent(nullptr), left(nullptr), right(nullptr), color(0){}
	};
	template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class RedBlackTree
	{
		public:
			typedef T		value_type;
			typedef Compare value_compare;
			typedef struct node<value_type> node;
			typedef node*	node_pointer;
			typedef typename Alloc::template rebind<node>::other	allocator_type;	//switch allocater type from T to node
			// Without the template keyword the < would be considered to be the less-than operator
		private:
			allocator_type _alloc;
			node_pointer	root;
			node_pointer	end;
			value_compare	_comp;
			size_t			size;

			node_pointer	makenode(value_type data = value_type())
			{
				node_pointer nodeCreated = _alloc.allocate(1);
				_alloc.construct(nodeCreated, data);
				return nodeCreated;
			}
		public:

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