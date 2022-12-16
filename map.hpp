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
			typedef ft::tree_iterator<node_pointer, value_type>							iterator;
			typedef ft::tree_iterator<node_pointer, const value_type>					citerator;
			typedef std::ptrdiff_t														difference_type;
			typedef size_t																size_type;
			typedef typename ft::reverse_iterator<iterator>								reverse_iterator;
			typedef typename ft::reverse_iterator<citerator>							const_reverse_iterator;
			typedef std::allocator<tree>								allocator_typee;

		private:
			tree			_tree;
			allocator_typee		_tree_allocator;
			allocator_type	_alloc;
			key_compare		_comp;
		public:

			explicit map (const key_compare& comp = key_compare(), 
				const allocator_type& alloc = allocator_type())
				: _tree(value_compare(comp), alloc), _alloc(alloc), _comp(comp)
			{ //explicit : dont cast the parametre.
			}

			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
						const allocator_type& alloc = allocator_type()): _tree(value_compare(comp), alloc), _alloc(alloc), _comp(comp)
			{
				// this->insert(first, last);
				while (first != last && first != this->_tree.nil())
				{
					this->insert(*first);
					first++;
				}
			}
			map (const map& x):_tree(value_compare(x._comp), x._alloc),  _alloc(x._alloc), _comp(x._comp)
			{
				*this = x;
			}
			~map(){}

			map	&operator=(const map& m)
			{
				if (this != &m)
				{
					this->clear();
					this->_alloc = m._alloc;
					this->_comp = m._comp;
					iterator first = m._tree.begin_node();
					iterator last = m._tree.end_node();
					while (first != last && first != this->_tree.nil())
					{
						this->insert(*first);
						first++;
					}
				}
				return *this;
			}
			mapped_type	&operator[](const key_type &k)
			{
				iterator found = this->find(k);
				if (found != _tree.nil())
					return ((*found).second);
				return (*((this->insert(ft::make_pair(k,mapped_type()))).first)).second;
			}
			void	clear() { this->_tree.clear(); }
			
			iterator begin() { return iterator(_tree.begin_node()); }
			
			citerator begin() const { return citerator(_tree.begin_node()); }
			
			iterator end() { return iterator(_tree.end_node(), _tree.nil()); }
			
			citerator end() const { return citerator(_tree.end_node(), _tree.nil()); }
			
			reverse_iterator rbegin() { return reverse_iterator(this->end()); }
			
			const_reverse_iterator rbegin() const { return (const_reverse_iterator(this->end())); }

			reverse_iterator rend() { return (reverse_iterator(this->begin())); }
			
			const_reverse_iterator rend() const { return (const_reverse_iterator(this->begin())); }
			
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
				// if (_find == this->_tree.nil())
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
				while (first != last)// && first != this->_tree.nil())
				{
					this->insert(*first);
					first++;
				}
			}
			void	erase(iterator position)
			{
				// if (this->find((*position).first) != this->_tree.nil())
				this->_tree.deleteNode(*position);
				// _tree.printTree();
			}
			size_type erase (const key_type& k)
			{
				iterator found = this->find(k);
				if (found != this->_tree.nil())
				{
					this->erase(found);
					return (1);
				}
				return (0);
			}
			void erase (iterator first, iterator last)
			{
				while (first != last && first != this->_tree.nil())
						this->erase(first++);
			}
			void swap (map &x)
			{
				_tree.swap(x._tree);
				std::swap(this->_alloc, x._alloc);
				std::swap(this->_comp, x._comp);
			}
			value_compare value_comp() const
			{
				return value_compare(this->_comp);
			}
			key_compare	key_comp() const
			{
				return this->_comp;
			}
	};
}
