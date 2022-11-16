#pragma once

#include "pair.hpp"
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
			typedef Compare	key_compare;
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
			}
			typedef Alloc	allocator_type;
			typedef allocator_type::reference reference;
			typedef allocator_type::const_reference const_reference;
			typedef allocator_type::pointer pointer;
			typedef allocator_type::const_pointer const_pointer;

	};
}

//1_ Every node is red or black
//2_ Root is always black
//3_ New insertions are always red
//4_ Every path from root-leaf has the same number of black nodes
//5_ No path can have two consecutive red nodes
//6_ Nulls are black

//rebalance based on :
		// black annt rotate			__root black children red
		// red annt color-flip			__ parent become red children be black