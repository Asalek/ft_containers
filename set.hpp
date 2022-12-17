#pragma once

#include <functional>
#include "iterators.hpp"
#include "pair.hpp"
class redBlackTree;

//   << less<int>{}(5, 5.6)    // false: 5 < 5 (warn: implicit conversion)
//   << less<double>{}(5, 5.6) // true: 5.0 < 5.6
//   << less<int>{}(5.6, 5.7)  // false: 5 < 5 (warn: implicit conversion)
//   << less{}(5, 5.6)         // true: less<void>: 5.0 < 5.6

namespace ft
{
	template <class Key,
				class Compare = std::less<Key>,
				class Alloc = std::allocator<Key >
			>
	class set
	{
		public:
			typedef Key									key_type;
			typedef Key									value_type;
			typedef Compare								key_compare;
			// class	value_compare
			// {
			// 	friend class set;
			// 	protected:
			// 		Compare comp;
			// 		value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
			// 	public:
			// 		typedef bool result_type;
			// 		typedef value_type first_argument_type;
			// 		typedef value_type second_argument_type;
			// 		bool operator() (const value_type& x, const value_type& y) const
			// 		{
			// 			return comp(x, y);
			// 		}
			// };
			typedef Alloc																allocator_type;
			typedef typename allocator_type::reference									reference;
			typedef typename allocator_type::const_reference							const_reference;
			typedef typename allocator_type::pointer									pointer;
			typedef typename allocator_type::const_pointer								const_pointer;
			typedef typename ft::RedBlackTree<value_type, key_compare>					tree;
			typedef typename ft::node<value_type>										node;
			typedef node*																node_pointer;
			typedef ft::tree_iterator<node_pointer, value_type>							iterator;
			typedef ft::tree_iterator<node_pointer, const value_type>					citerator;
			typedef std::ptrdiff_t														difference_type;
			typedef size_t																size_type;
			typedef typename ft::reverse_iterator<iterator>								reverse_iterator;
			typedef typename ft::reverse_iterator<citerator>							const_reverse_iterator;

		private:
			tree			_tree;
			allocator_type	_alloc;
			key_compare		_comp;
		public:

			explicit set (const key_compare& comp = key_compare(), 
				const allocator_type& alloc = allocator_type())
				: _tree(key_compare(comp), alloc), _alloc(alloc), _comp(comp)
			{ //explicit : dont cast the parametre.
			}

			template <class InputIterator>
			set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
						const allocator_type& alloc = allocator_type()): _tree(key_compare(comp), alloc), _alloc(alloc), _comp(comp)
			{
				// this->insert(first, last);
				while (first != last && first != this->_tree.nil())
				{
					this->insert(*first);
					first++;
				}
			}
			set (const set& x):_tree(key_compare(x._comp), x._alloc),  _alloc(x._alloc), _comp(x._comp)
			{
				*this = x;
			}
			~set(){}

			set	&operator=(const set& m)
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
			void	clear() { this->_tree.clear(); }
			
			iterator begin() { return iterator(_tree.begin_node(), _tree.nil()); }
			
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
				node_pointer _x = this->_tree.find(x);
				if (_x == _tree.nil())
					return this->end();
				return iterator(_x);
			}
			citerator	find(const key_type &x) const
			{
				node_pointer _x = this->_tree.find(x);
				if (_x == _tree.nil())
					return this->end();
				return citerator(_x);
			}
			pair<iterator, bool> insert (const value_type& val)
			{
				iterator _find = this->find(val);
				// if (_find == this->_tree.nil())
				if (_find == this->end())
				{
					this->_tree.insert(val);
					_find = this->find(val);
					// _tree.printTree();
					return pair<iterator, bool>(_find, true);
				}
				return pair<iterator, bool>(_find, false);
			}
			iterator insert (iterator position, const value_type& val)
			{
				position = this->find(val);
				if (position != this->end())
					return (position);
				this->insert(val);
				return (this->find(val));
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
			void swap (set &x)
			{
				_tree.swap(x._tree);
				std::swap(this->_alloc, x._alloc);
				std::swap(this->_comp, x._comp);
			}
			key_compare value_comp() const
			{
				return key_compare(this->_comp);
			}
			key_compare	key_comp() const
			{
				return this->_comp;
			}
			size_type count (const key_type& k) const
			{
				if (this->find(k) != this->end())
					return 1;
				return 0;
			}
			allocator_type get_allocator() const
			{
				return this->_alloc;
			}
			iterator upper_bound (const key_type& k)
			{
				return _tree.upper_bound(k);
			}

			citerator upper_bound (const key_type& k) const
			{
				return _tree.upper_bound(k);
			}
			iterator	lower_bound (const key_type &k)
			{
				return _tree.lower_bound(k);
			}
			citerator	lower_bound (const key_type &k) const
			{
				return _tree.lower_bound(k);
			}
			pair<citerator,citerator> equal_range (const key_type& k) const
			{
				return pair<citerator,citerator>(lower_bound(k), upper_bound(k));
			}
			pair<iterator,iterator> equal_range (const key_type& k)
			{
				iterator low = lower_bound(k);
				iterator up = upper_bound(k);
				return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
			}
			void print()
			{
				_tree.printSetTree();
			}
	};
}
