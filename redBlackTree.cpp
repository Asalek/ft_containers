// #pragma once

#define BLACK 1
#define RED 0
#include <iostream>
#include "iterators.hpp"
using std::cout;
using std::endl;
using std::string;

// namespace ft
// {
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
		RedBlackTree(): root(nullptr), end(nullptr), size(0), _comp()
		{
			end = this->makenode();
		}
		RedBlackTree(value_compare _comp, allocator_type _alloc): root(nullptr), end(), _alloc(_alloc), _comp(_comp), size(0)
		{
			end = this->makenode();
		}

		RedBlackTree(const RedBlackTree& _tr) : root(nullptr), end(), _alloc(_tr._alloc), _comp(), size(0)
		{
			*this = _tr;
		}
			void printHelper(node_pointer root, std::string indent, bool last) {
        	// print the tree structure on the screen
            if (root != nullptr) {
                std::cout << indent;
                if (last) {
                    std::cout<<"R----";
                    indent += "     ";
                } else {
                    std::cout<<"L----";
                    indent += "|    ";
                }

                std::cout<<root->data<<"( C = "<<root->color<<")"<<std::endl;

                printHelper(root->left, indent, false);
                printHelper(root->right, indent, true);
            }
        }
					void printTree() {
				if (root) {
				printHelper(this->root, "", true);
				}
			}
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
				if (_comp(new_node->data, parent->data)) //  newNode goes left or right
					parent->left = new_node;
				else
					parent->right = new_node;
				new_node->color = RED;
				this->size++;
				this->end->left = this->root;
				this->root->parent = this->end;
				//fixAfterInsert(new_node);
			}
			void	fixAfterInsert(node_pointer f)
			{
				while (f->parent && f->parent->color == RED)
				{
					/*If f parent is the left child of grandParent , do the following.*/
					if (f->parent == f->parent->parent->left)
					{
						node_pointer annt = f->parent->parent->right;
						//CASE I

						/*	If the color of the right child of gP of newNode is RED, 
						set the color of both the children of gP as BLACK and the color of gP as RED.	*/
						if (annt != nullptr && annt->color == RED)
						{
							f->parent->color = BLACK;
							annt->color = BLACK;
							f->parent->parent->color = RED;
							f = f->parent->parent;			// point to the grand parent to fix it
						}
						//CASE II

						/*	if newNode is the right child of p then assign p to newNode (f)
						and left rotate newNode (f)	*/
						else
						{
							if (f == f->parent->right)
							{
								f = f->parent;
								leftRotate(f);
							}
							//Set color of p as BLACK and color of gP as RED and right rotate gP
							f->parent->color = BLACK;
							f->parent->parent->color = RED;
							rightRotate(f->parent->parent);
							break ;
						}
					}
					else
					{
						node_pointer annt = f->parent->parent->left;
						/*If the color of the left child of gP of z is RED,
						set the color of both the children of gP as BLACK and the color of gP as RED,
						and assign gP to newNode*/
						if (annt != nullptr && annt->color == RED)
						{
							f->parent->color = BLACK;
							annt->color = BLACK;
							f->parent->parent->color = RED;
							f = f->parent->parent;
						}
						else
						{
							/*Else if newNode is the left child of p then,
							assign p to newNode and Right-Rotate newNode.
							then Set color of p as BLACK and color of gP as RED
							and left rotate gP*/
							if (f == f->parent->left)
							{
								f = f->parent;
								rightRotate(f);
							}
							f->parent->color = BLACK;
							f->parent->parent->color = RED;
							leftRotate(f->parent->parent);
							break ;
						}
					}
				}
				this->root->color = BLACK;
			}
			void	leftRotate(node_pointer x)
			{
				node_pointer y = x->right;
				x->right = y->left;
				if (y->left != nullptr)
					y->left->parent = x;
				y->parent = x->parent;
				if (x->parent == nullptr)
					this->root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->left = x;
				x->parent = y;
			}
			void rightRotate(node_pointer x)
			{
				node_pointer y = x->left;
				x->left = y->right;
				if (y->right != nullptr)
					y->right->parent = x;
				y->parent = x->parent;
				if (x->parent == nullptr)
					this->root = y;
				else if (x == x->parent->right)
					x->parent->right = y;
				else
					x->parent->left = y;
				y->right = x;
				x->parent = y; 
			}
			void	transplant(node_pointer del, node_pointer child) // emplace nodeToBeDeleted with it's children's
			{
				if (del->parent == nullptr)
					this->root = child;
				else if (del == del->parent->left)
					del->parent->left = child;
				else
					del->parent->right = child;
				if (child != nullptr)
					child->parent = del->parent;
			}

			void	deleteNode(value_type value)
			{
				node_pointer Del;
				node_pointer x;

				if (!root || (Del = find(value)) == nullptr)
					return ;
				//Save the color of nodeToBeDeleted in origrinalColor
				bool originalColor = Del->color;
				//If the left child of Deleted is NULL, Assign the right child of Deleted to x
				if (Del->left == nullptr)
				{
					x = Del->right;
					transplant(Del, Del->right);
					_alloc.destroy(Del);
					_alloc.deallocate(Del, 1);
				}
				else if (Del->right == nullptr)
				{
					x = Del->left;
					transplant(Del, Del->left);
					_alloc.destroy(Del);
					_alloc.deallocate(Del, 1);
				}
				else
				{
					
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
		return 0;
	}
// }