/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalek <asalek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 23:35:27 by asalek            #+#    #+#             */
/*   Updated: 2022/10/20 05:57:15 by asalek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
	template<typename Type>
	class rand_acc_ite_tag : public std::iterator<std::random_access_iterator_tag, Type>
	{
	public:
		using difference_type = typename std::iterator<std::random_access_iterator_tag, Type>::difference_type;
		
		Iterator() : _ptr(nullptr) {}
		Iterator(Type* rhs) : _ptr(rhs) {}
		Iterator(const Iterator &rhs) : _ptr(rhs._ptr) {}
		/* inline Iterator& operator=(Type* rhs) {_ptr = rhs; return *this;} */
		/* inline Iterator& operator=(const Iterator &rhs) {_ptr = rhs._ptr; return *this;} */
		inline Iterator& operator+=(difference_type rhs) {_ptr += rhs; return *this;}
		inline Iterator& operator-=(difference_type rhs) {_ptr -= rhs; return *this;}
		inline Type& operator*() const {return *_ptr;}
		inline Type* operator->() const {return _ptr;}
		inline Type& operator[](difference_type rhs) const {return _ptr[rhs];}
		
		inline Iterator& operator++() {++_ptr; return *this;}
		inline Iterator& operator--() {--_ptr; return *this;}
		inline Iterator operator++(int) const {Iterator tmp(*this); ++_ptr; return tmp;}
		inline Iterator operator--(int) const {Iterator tmp(*this); --_ptr; return tmp;}
		/* inline Iterator operator+(const Iterator& rhs) {return Iterator(_ptr+rhs.ptr);} */
		inline difference_type operator-(const Iterator& rhs) const {return _ptr-rhs.ptr;}
		inline Iterator operator+(difference_type rhs) const {return Iterator(_ptr+rhs);}
		inline Iterator operator-(difference_type rhs) const {return Iterator(_ptr-rhs);}
		friend inline Iterator operator+(difference_type lhs, const Iterator& rhs) {return Iterator(lhs+rhs._ptr);}
		friend inline Iterator operator-(difference_type lhs, const Iterator& rhs) {return Iterator(lhs-rhs._ptr);}
	private:
		Type* _ptr;
	};
}