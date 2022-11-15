#pragma once

namespace ft
{
    template <class k, class v>
    class redBlackTree
    {
	public:
		size_t	size;
		Node<k, v>	root;

		class Node <k, v>
        {
            k			key;
            v			value;
            Node<k, v>	left, right, parent;
            bool		isLeftChild, black;
			Node (k key, v value)
			{
				this->key = key;
				this->value = value;
				left = right = parent = nullptr;	//if parent null mean node is root
				black = false;		//new nodes are red
				isLeftChild = false;
			}
        };
		void add(k key, v value)
		{
			Node<k, v> node = new Node<k, v>(key, value);
			if (root == nullptr)  //if !root make it root
			{
				root = node;
				root.black = true;
				size++;
				return ;
			}
			add(root, node);//if root, we passed it with the new node to place it properly
			size++;
		}
	private:
		void add (Node<k, v>root, Node<k, v> newNode)
		{
		}
    };
}