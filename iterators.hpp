/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalek <asalek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 23:35:27 by asalek            #+#    #+#             */
/*   Updated: 2022/11/03 12:02:24 by asalek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

namespace ft
{
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

	template<typename Type>
	class random_Iter : public std::iterator<std::random_access_iterator_tag, Type>
	{
		private:
			Type *_ptr;
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
			inline random_Iter operator++(int) const {random_Iter tmp(*this); ++_ptr; return tmp;}
			inline random_Iter operator--(int) const {random_Iter tmp(*this); --_ptr; return tmp;}
			inline random_Iter operator+(const random_Iter& rhs) {return random_Iter(_ptr+rhs.ptr);}
			inline difference_type operator-(const random_Iter& rhs) const {return _ptr-rhs.ptr;}
			inline random_Iter operator+(difference_type rhs) const {return random_Iter(_ptr+rhs);}
			inline random_Iter operator-(difference_type rhs) const {return random_Iter(_ptr-rhs);}
			Type	base() const {return *this->_ptr;}
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
	bool operator>(const random_Iter<Iter> &lhs, const random_Iter<Iter> &rhs)
	{
		return (lhs.base() > rhs.base());
	}
}
