#pragma once

#include "pair.hpp"
#include "redBlackTree.hpp"
#include "iterators.hpp"
#include <functional>

//   << less<int>{}(5, 5.6)    // false: 5 < 5 (warn: implicit conversion)
//   << less<double>{}(5, 5.6) // true: 5.0 < 5.6
//   << less<int>{}(5.6, 5.7)  // false: 5 < 5 (warn: implicit conversion)
//   << less{}(5, 5.6)         // true: less<void>: 5.0 < 5.6

namespace ft
{
	template <class Key,
				class T,
				class Compare = std::less<Key>,
				class Alloc = std::allocator<ft::pair<const Key,T> >
			>
	class map
	{
		public:
			typedef Key	key_type;
			typedef T	mapped_type;
			typedef pair<const key_type, mapped_type>	value_type;
			typedef Compare																key_compare;
			class value_compare
			{
				friend class map;
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};
			typedef Alloc																allocator_type;
			typedef typename allocator_type::reference									reference;
			typedef typename allocator_type::const_reference							const_reference;
			typedef typename allocator_type::pointer									pointer;
			typedef typename allocator_type::const_pointer								const_pointer;
			typedef typename ft::RedBlackTree<value_type, value_compare, allocator_type> tree;
			typedef typename ft::node<value_type>										node;
			typedef node*																node_pointer;
			typedef ft::tree_iterator<node_pointer>										iterator;

			//constructors

			explicit map (const key_compare& comp = key_compare(), 
				const allocator_type& alloc = allocator_type())
			{
				//explicit : dont cast the parametre.
			}
			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
						const allocator_type& alloc = allocator_type())
			{}
			map (const map& x)
			{}
			// iterator begin()
			// {
			// 	return ();
			// }
	};
}
