/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalek <asalek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 23:35:27 by asalek            #+#    #+#             */
/*   Updated: 2022/12/16 22:28:24 by asalek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "pair.hpp"

namespace ft
{
	//iterator Traits 
	
	template <class T>
    struct iterator_traits
	{
        typedef typename T::value_type            value_type;
        typedef typename T::difference_type       difference_type;
        typedef typename T::iterator_category     iterator_category;
        typedef typename T::pointer               pointer;
        typedef typename T::reference             reference;
    };

    template <class T>
    struct iterator_traits<T*>
	{
        typedef T                          value_type;
        typedef ptrdiff_t                  difference_type;
        typedef std::random_access_iterator_tag iterator_category;
        typedef T*                         pointer;
        typedef T&                         reference;
    };

    template <class T>
    struct iterator_traits<const T*>
	{
        typedef T                          value_type;
        typedef ptrdiff_t                  difference_type;
        typedef std::random_access_iterator_tag iterator_category;
        typedef const T*                         pointer;
        typedef const T&                         reference;
    };

	//Random Access Iterator
	
	template<typename Type>
	class random_Iter : public std::iterator<std::random_access_iterator_tag, Type>
	{
		private:
			Type *_ptr;
			// Typee _ptr;
		public:
			typedef typename std::iterator<std::random_access_iterator_tag, Type>::difference_type difference_type;

			random_Iter() : _ptr(nullptr) {}
			random_Iter(Type* rhs) : _ptr(rhs) {}
			random_Iter(const random_Iter &rhs) : _ptr(rhs._ptr) {}

			inline random_Iter& operator=(Type* rhs) {_ptr = rhs; return *this;}
			inline random_Iter& operator=(const random_Iter &rhs) {_ptr = rhs._ptr; return *this;}
			inline random_Iter& operator+=(difference_type rhs) {_ptr += rhs; return *this;}
			inline random_Iter& operator-=(difference_type rhs) {_ptr -= rhs; return *this;}
			inline Type& operator*() const {return *_ptr;}
			inline Type* operator->() const {return _ptr;}
			inline Type& operator[](difference_type rhs) const {return _ptr[rhs];}
			inline random_Iter& operator++() {++_ptr; return *this;}
			inline random_Iter& operator--() {--_ptr; return *this;}
			inline random_Iter operator++(int) {random_Iter tmp(*this); ++_ptr; return tmp;}
			inline random_Iter operator--(int) {random_Iter tmp(*this); --_ptr; return tmp;}
			inline random_Iter operator+(const random_Iter& rhs) {return random_Iter(_ptr+rhs.ptr);}
			inline difference_type operator-(const random_Iter& rhs) const {return _ptr-rhs._ptr;}
			inline random_Iter operator+(difference_type rhs) const {return random_Iter(_ptr+rhs);}
			inline random_Iter operator-(difference_type rhs) const {return random_Iter(_ptr-rhs);}
			Type	*base() const {return _ptr;}
			// friend inline random_Iter operator+(difference_type lhs, const random_Iter& rhs) {return random_Iter(lhs+rhs._ptr);}
			// friend inline random_Iter operator-(difference_type lhs, const random_Iter& rhs) {return random_Iter(lhs-rhs._ptr);}
	};

	template <class Iter>
	bool operator!=(const random_Iter<Iter> &lhs, const random_Iter<Iter> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class Iter>
	bool operator==(const random_Iter<Iter> &lhs, const random_Iter<Iter> &rhs)
	{
		return (lhs.base() == rhs.base());
		
	}

	template <class Iter>
	bool operator<(const random_Iter<Iter> &lhs, const random_Iter<Iter> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iter>
	bool operator<=(const random_Iter<Iter>& lhs, const random_Iter<Iter>& rhs)
	{
		return (lhs.base() < rhs.base() || lhs.base() == rhs.base());
	}

	template <class Iter>
	bool operator>(const random_Iter<Iter> &lhs, const random_Iter<Iter> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iter>
	bool operator>=(const random_Iter<Iter> &lhs, const random_Iter<Iter> &rhs)
	{
		return (lhs.base() > rhs.base() || lhs.base() == rhs.base());
	}
	
	template <class Iter>
	typename random_Iter<Iter>::difference_type operator-(const random_Iter<Iter> &lhs, const random_Iter<Iter> &rhs)
	{
		return (lhs.base() - rhs.base());
	}

	//Reverse Iterator

	template<typename Type>
	class reverse_iterator : public std::iterator<std::bidirectional_iterator_tag, Type>, iterator_traits<Type>
	{
		private:
			Type *_ptr;
		public:
			typedef typename std::iterator<std::random_access_iterator_tag, Type>::difference_type difference_type;
			
			reverse_iterator() : _ptr(nullptr) {}
			reverse_iterator(Type* rhs) : _ptr(rhs) {}
			reverse_iterator(const reverse_iterator &rhs) : _ptr(rhs._ptr) {}

			inline reverse_iterator& operator+=(difference_type rhs) {_ptr += rhs; return *this;}
			inline reverse_iterator& operator-=(difference_type rhs) {_ptr -= rhs; return *this;}
			inline Type& operator*() const {return *_ptr;}
			inline Type* operator->() const {return _ptr;}
			inline Type& operator[](difference_type rhs) const {return _ptr[rhs];}
			inline reverse_iterator& operator++() {--_ptr; return *this;}
			inline reverse_iterator& operator--() {++_ptr; return *this;}
			inline reverse_iterator operator++(int) {reverse_iterator tmp(*this); --_ptr; return tmp;}
			inline reverse_iterator operator--(int) {reverse_iterator tmp(*this); ++_ptr; return tmp;}
			inline reverse_iterator operator+(const reverse_iterator& rhs) {return reverse_iterator(_ptr-rhs.ptr);}
			inline difference_type operator-(const reverse_iterator& rhs) const {return _ptr+rhs._ptr;}
			inline reverse_iterator operator+(difference_type rhs) const {return reverse_iterator(_ptr-rhs);}
			inline reverse_iterator operator-(difference_type rhs) const {return reverse_iterator(_ptr+rhs);}
			Type	base() const {return *this->_ptr;}
			// friend inline reverse_iterator operator+(difference_type lhs, const reverse_iterator& rhs) {return reverse_iterator(lhs+rhs._ptr);}
			// friend inline reverse_iterator operator-(difference_type lhs, const reverse_iterator& rhs) {return reverse_iterator(lhs-rhs._ptr);}
	};
	
	template <class Iter>
	bool operator!=(const reverse_iterator<Iter> &lhs, const reverse_iterator<Iter> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class Iter>
	bool operator==(const reverse_iterator<Iter> &lhs, const reverse_iterator<Iter> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iter>
	bool operator<(const reverse_iterator<Iter> &lhs, const reverse_iterator<Iter> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iter>
	bool operator<=(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
	{
		return (lhs.base() < rhs.base() || lhs.base() == rhs.base());
	}

	template <class Iter>
	bool operator>(const reverse_iterator<Iter> &lhs, const reverse_iterator<Iter> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iter>
	bool operator>=(const reverse_iterator<Iter> &lhs, const reverse_iterator<Iter> &rhs)
	{
		return (lhs.base() > rhs.base() || lhs.base() == rhs.base());
	}
	
	template <class Iter>
	typename reverse_iterator<Iter>::difference_type operator-(const reverse_iterator<Iter> &lhs, const reverse_iterator<Iter> &rhs)
	{
		return (lhs.base() - rhs.base());
	}
	
	//tree iterator
	template<class Iter, class P_T>
	class tree_iterator : public std::iterator<std::bidirectional_iterator_tag,
					typename ft::iterator_traits<Iter>::value_type>
	{
		Iter	_current;	//pointer that iterat on key not the value
		Iter	_nil;
		public:
			tree_iterator():_current(nullptr) {}
			tree_iterator(Iter x) : _current(x){}
			tree_iterator(Iter c, Iter n) : _current(c), _nil(n){}
			tree_iterator(const tree_iterator &other) : _current(other._current) {}
			tree_iterator &operator=(const tree_iterator &other)
			{
				this->_current = other.base();
				return *this;
			}
			bool	operator==(const tree_iterator &other) { return (_current == other.base()); }
			// bool	operator!=(const tree_iterator &other) { return !(_current == other.base()); }
			bool	operator!=(const tree_iterator &other)
			{
				if (_current == other.base())
					return false;
				if (_current == _nil || _current == nullptr)
					return false;
				return true;
			}
			Iter	base() const { return this->_current; }
			P_T&	operator*() const { return _current->data; }
			P_T*	operator->() const { return &(_current->data); }
			tree_iterator operator++(int)
			{
				tree_iterator tmp(*this);
				this->_current = successor(this->_current);
				return (tmp);
			}
			tree_iterator & operator++()
			{
				this->_current = successor(this->_current);
				return (*this);
			}
			tree_iterator operator--(int)
			{
				tree_iterator tmp(*this);
				this->_current = predecessor(this->_current);
				return tmp;
			}
			tree_iterator & operator--()
			{
				this->_current = predecessor(this->_current);
				return *this;
			}
		private:
			Iter	minimum(Iter node) const		//return the left node in the tree
			{
				while (node->left)//(node->left->left != nullptr)
					node = node->left;
				return (node);
			}
			Iter	maximum(Iter node) const		//return the right node in the tree
			{
				while (node->right)//(node->right->right != nullptr)
					node = node->right;
				return (node);
			}
			Iter	successor(Iter node)
			{
				if (node->right)//(node->right->right != nullptr)
					return (minimum(node->right));
				Iter x = node->parent;
				while (x != nullptr && node == x->right)
				{
					node = x;
					x = x->parent;
				}
				return (x);
			}
			Iter	predecessor(Iter node)
			{
				if (node->left != nullptr)//(node->left->left != nullptr)
					return (maximum(node->left));
				Iter x = node->parent;
				while (x != nullptr && node == x->left)
				{
					node = x;
					x = x->parent;
				}
				return (x);
			}
	};
}

//    int a = 12;
//    int *b = &a;
//    int &c = *b;
//    cout <<c<<endl;   //12