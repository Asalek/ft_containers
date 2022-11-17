#pragma once

#include <iostream>
using std::cout;
using std::endl;
using std::string;

namespace ft
{
	// Implementing Red-Black Tree in C++
	template<class T>
	struct Node {
		T data;
		Node *parent;
		Node *left;
		Node *right;
		int color;
		Node():data(nullptr), parent(nullptr), left(nullptr), right(nullptr), color(0){}
		Node(T _data):data(_data), parent(nullptr), left(nullptr), right(nullptr), color(0){}
	};
}