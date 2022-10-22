/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalek <asalek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 23:35:27 by asalek            #+#    #+#             */
/*   Updated: 2022/10/22 00:20:16 by asalek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

namespace ft
{
	template<typename Type>
	class random_Iter : public std::iterator<std::random_access_iterator_tag, Type>
	{
		private:
			Type *_ptr;
		public:
			typedef typename std::iterator<std::random_access_iterator_tag, Type>::difference_type difference_type;

			random_Iter() : _ptr(nullptr) {std::cout << "A";}
			random_Iter(Type* rhs) : _ptr(rhs) {std::cout << "B";}
			// random_Iter(Type rhs) : _ptr(rhs) {std::cout << "C";}
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
			friend inline random_Iter operator+(difference_type lhs, const random_Iter& rhs) {return random_Iter(lhs+rhs._ptr);}
			friend inline random_Iter operator-(difference_type lhs, const random_Iter& rhs) {return random_Iter(lhs-rhs._ptr);}
	};
}
