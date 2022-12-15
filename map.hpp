#pragma once

#include <functional>
#include "redBlackTree.hpp"
#include "iterators.hpp"
#include "pair.hpp"

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
			typedef Key									key_type;
			typedef T									mapped_type;
			typedef pair<const key_type, mapped_type>	value_type;
			typedef Compare								key_compare;
			class	value_compare
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
			typedef ft::tree_iterator<node_pointer, value_type>										iterator;
			typedef ft::tree_iterator<const node_pointer, const value_type>								citerator;
			typedef std::ptrdiff_t														difference_type;
			typedef size_t																size_type;
		private:
			tree			_tree;
			allocator_type	_alloc;
			key_compare		_comp;
		public:
			//constructors

			explicit map (const key_compare& comp = key_compare(), 
				const allocator_type& alloc = allocator_type())
				: _tree(value_compare(comp), alloc), _alloc(alloc), _comp(comp)
			{ //explicit : dont cast the parametre.
			}

			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
						const allocator_type& alloc = allocator_type()): _tree(value_compare(comp), alloc),  _alloc(alloc), _comp(comp)
			{
				this->insert(first, last);
			}
			// map (const map& x)
			// {}
			~map(){}

			iterator begin() { return iterator(_tree.begin_node()); }
			iterator end() { return iterator(_tree.end_node(), _tree.nil()); }
			bool	empty() const { return (_tree.is_empty()); }
			size_type size() const {return (_tree.red_black_size()); }
			size_type	max_size() const {return (_tree.max_size()); }
			iterator	find(const key_type &x)
			{
				node_pointer _x = this->_tree.find(ft::make_pair(x, mapped_type()));
				if (_x == _tree.nil())
					return this->end();
				return iterator(_x);
			}
			citerator	find(const key_type &x) const
			{
				node_pointer _x = this->_tree.find(ft::make_pair(x, mapped_type()));
				if (_x == _tree.nil())
					return this->end();
				return citerator(_x);
			}
			pair<iterator, bool> insert (const value_type& val)
			{
				iterator _find = this->find(val.first);
				if (_find == this->end())
				{
					this->_tree.insert(val);
					_find = this->find(val.first);
					// _tree.printTree();
					return pair<iterator, bool>(_find, true);
				}
				return pair<iterator, bool>(_find, false);
			}
			iterator insert (iterator position, const value_type& val)
			{
				position = this->find(val.first);
				if (position != this->end())
					return (position);
				this->insert(val);
				return (this->find(val.first));
			}
			template <class inputIterator>
			void	insert(inputIterator first, inputIterator last)
			{
				--last;
				while (first != last)
				{
					this->insert(*first);
					first++;
				}
			}
	};
}
