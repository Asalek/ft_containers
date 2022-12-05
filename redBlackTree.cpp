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
		node():data(), parent(nullptr), left(nullptr), right(nullptr), color(0){}
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
		  void printHelper(node_pointer nodee, string indent, bool last) {
		    if (nodee != nullptr)
			{
				cout << indent;
				if (last) {
					cout << "R----";
					indent += "   ";
				} else {
					cout << "L----";
					indent += "|  ";
				}

				string sColor;
				//  = nodee->color ? "RED" : "BLACK";
				if (nodee->color == RED)
					sColor = "RED";
				else
					sColor = "BLACK";
				cout << nodee->data << "(" << sColor << ")" << endl;
				printHelper(nodee->left, indent, false);
				printHelper(nodee->right, indent, true);
        	}
		}
		void printTree()
		{
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
					this->size++;
					this->root->color = BLACK;
					return ;
				}
				if (find(data) != nullptr) // if data exist don't insert it
					return ;
				this->end->left = nullptr;//remove it later
				root->parent = nullptr;
				node_pointer new_node = makenode(data);
				node_pointer parent = nullptr;
				node_pointer node_root = this->root;
				new_node->color = RED;
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
				fixAfterInsert(new_node);
				this->size++;
				this->end->left = this->root;
				this->root->parent = this->end;
			}
			void	fixAfterInsert(node_pointer f)
			{
				while (f->parent != nullptr && f->parent->color == RED)
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
			node_pointer	minimum(node_pointer node) const		//return the left node in the tree
			{
				while (node->left != nullptr)
					node = node->left;
				return (node);
			}
			node_pointer	maximum(node_pointer node) const		//return the right node in the tree
			{
				while (node->right != nullptr)
					node = node->right;
				return (node);
			}
			node_pointer	successor(node_pointer node)
			{
				if (node->right != nullptr)
					return (minimum(node->right));
				node_pointer x = node->parent;
				while (x != nullptr && node == x->right)
				{
					node = x;
					x = x->parent;
				}
				return (x);
			}
			node_pointer	predecessor(node_pointer node)
			{
				if (node->left != nullptr)
					return (maximum(node->left));
				node_pointer x = node->parent;
				while (x != nullptr && node == x->left)
				{
					node = x;
					x = x->parent;
				}
				return (x);
			}
			// transplant : help us move subtrees within the tree
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
				node_pointer y;

				if (!root || (Del = find(value)) == nullptr)
					return ;
				this->end->left = nullptr;
				this->root->parent = nullptr;
				size--;
				//Save the color of nodeToBeDeleted in origrinalColor
				bool originalColor = Del->color;
				//If the left child of Deleted is NIL
				if (Del->left == nullptr)
				{
					cout << "DEL__1\n";
					x = Del->right;
					// if (x == nullptr)
					// {
					// 	x = this->end;
					// 	x->left = nullptr;
					// 	x->right = nullptr;
					// 	x->color = BLACK;
					// 	x->parent = Del->parent;
					// }
					transplant(Del, x);
					_alloc.destroy(Del);
					_alloc.deallocate(Del, 1);
				}
				else if (Del->right == nullptr)// right child is NIL
				{
					cout << "DEL__2\n";
					x = Del->left;
					transplant(Del, x);
					_alloc.destroy(Del);
					_alloc.deallocate(Del, 1);
				}
				else //neither child is NIL
				{
					cout << "DEL__3\n";
					y = minimum(Del->right);
					originalColor = y->color;
					x = y->right;
					if (y->parent != nullptr && y->parent != Del)
					{
						transplant(y, y->right);//(y, x);
						y->right = Del->right;
						y->right->parent = y;
					}
					transplant(Del, y);
					y->left = Del->left;
					y->left->parent = y;
					y->color = Del->color;
					_alloc.destroy(Del);
					_alloc.deallocate(Del, 1);
				}
				if (originalColor == BLACK && x != nullptr)
				{
				 	cout <<"**\n";
					erase_fixup(x);
				}
				if (root != nullptr)
				{
					end->left = root;
					root->parent = end;
				}
			}
			/*
				types of fixUp(x) :				(w is x annt)
					1_ w is red
					2_ w is black, and (w->left && w->right) are black
					3_ w is black, and w->left is red and w->right is black
					4_ w is black, and w->right is red
			*/
			void	erase_fixup(node_pointer x)
			{
				node_pointer w;
				cout << "XX\n";
				cout << x->color <<"<===color\n";
				while (x != this->root && x->color == BLACK)
				{
					if (x != nullptr && x == x->parent->left)
					{
						w = x->parent->right;
						//case 1
						if (w != nullptr && w->color == RED)
						{
							w->color = BLACK;
							x->parent->color = RED;
							this->leftRotate(x->parent);
							w = x->parent->right;
						}
						//case 2
						if (w != nullptr &&
							w->color == BLACK
							&& w->left->color == BLACK
							&& w->right->color == BLACK)
						{
							cout << "XX\n";
							w->color = RED;
							x = x->parent;
						}
						//case 3
						else
						{
							if (w->right->color == BLACK)
							{
								w->left->color = BLACK;
								w->color = RED;
								this->rightRotate(w);
								w = x->parent->right;
							}
							//case 4
							w->color = x->parent->color;
							x->parent->color = BLACK;
							w->right->color = BLACK;
							this->leftRotate(x->parent);
							x = this->root;
						}
					}
					else
					{
						w = x->parent->left;
						//case 1
						if (w && w->color == RED)
						{
							w->color = BLACK;
							x->parent->color = RED;
							this->rightRotate(x->parent);
							w = x->parent->left;
						}
						//case 2
						if (w->left->color == BLACK && w->right->color == BLACK)
						{
							w->color = RED;
							x = x->parent;
						}
						//case 3
						else
						{
							if (w->left->color == BLACK)
							{
								w->right->color = BLACK;
								w->color = RED;
								this->leftRotate(w);
								w = x->parent->left;
							}
							//case 4
							w->color = x->parent->color;
							x->parent->color = BLACK;
							w->left->color = BLACK;
							this->rightRotate(x->parent);
							x = this->root;
						}
					}
				}
				x->color = BLACK;
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