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
			node_pointer	find(const value_type &data) const
			{
				node_pointer current = this->root;
				while (current != nullptr)
				{
					if (!_comp(current->data, data) && !_comp(data, current->data))
						break ; //!(data < c.data) && !(c.data < data) => data = c.data
					current = _comp(current->data, data) ? current->right : current->left;
				}
				return current;
			}
			//	insertion
			void	insert(value_type data = value_type())
			{
				if (this->root == nullptr) //if !root make it
				{
					this->root = makenode(data);
					root->parent = this->end;
					this->end->left = this->root;
					// this->end->right = this->root;
					this->size++;
					return ;
				}
				if (find(data) != nullptr) // if data exist don't insert it
					return ;
				this->end->left = nullptr;//remove it later
				root->parent = nullptr;
				node_pointer new_node = makenode(data);
				node_pointer parent = nullptr;
				node_pointer node_root = this->root;
				while (node_root != nullptr) // go to data position
				{
					parent = node_root;
					node_root = (_comp(new_node->data, node_root->data)) ? node_root->left : node_root->right;
					new_node->parent = parent;
				}
				if (_comp(new_node->data, node_root->data)) //  newNode goes left or right
					parent->left = new_node;
				else
					parent->right = new_node;
				new_node->color = RED;
				this->size++;
				this->end->left = this->root;
				this->root->parent = this->end;
				//fixAfterInsert(new_node);
			}
	};

	int main()
	{
		RedBlackTree<int> bst;
		// bst.insert(55);
		// bst.insert(40);
		// bst.insert(65);
		// bst.insert(60);
		// bst.insert(75);
		// bst.insert(57);

		// bst.printTree();
		// cout << endl
		// 	<< "After deleting" << endl;
		// bst.deleteNode(40);
		// bst.printTree();
	}
}