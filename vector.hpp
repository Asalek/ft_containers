/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalek <asalek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:50:30 by asalek            #+#    #+#             */
/*   Updated: 2022/10/18 11:54:06 by asalek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
#define VECTOR_H

#include <iterator>
#include <cstddef>

#include <iostream>

using	std::cout;
using	std::endl;
using	std::allocator;
using	std::string;

namespace ft
{	
	template <typename T, class Allocator = allocator<T> >
	class Vector
	{
		public:
			typedef	T						value_type;
			typedef Allocator				allocator_type;
			typedef	T&						reference;
			typedef	const T&				const_reference;
			typedef	T*						pointer;
			typedef	const T*				const_pointer;
			size_t							size_type;
		//member types
//vectr = _alloc.allocate(3);
// alloc.deallocate(pointer, 3);

			//Connstructors & Destructor
			Vector():size_type(0)
			{
				vectr = _alloc.allocate(0);
			};
			Vector(Vector &ve)
			{
				*this = ve;
			}
			Vector(unsigned long size, unsigned long value)
			{
				vectr = _alloc.allocate(size);
				size_type = size;
				while (--size)
					vectr[size] = value;
				vectr[0] = value;
			}
			//Member Functions
			void	resize(unsigned long	new_size)
			{
				if (new_size <= _alloc.max_size())
				{
					vectr = _alloc.allocate(new_size); // allocate in case of bad allocation it throws bad allocation exception
					size_type = new_size;
				}
				else{}
			}
			reference	front() {return vectr[0];}
			reference	back() {return vectr[size_type - 1];}
			unsigned long size() {return this->size_type;}
			//Operators
			reference operator[] (unsigned long n)
			{
				if (n < 0 || n >= this->size_type)
					return vectr[size_type - 1];
				else
					return vectr[n];
			}
			Vector	&operator=(Vector &ve)
			{
				i = 0;
				if (this == &ve)
					return *this;
				this->size_type = ve.size_type;
				this->vectr = _alloc.allocate(this->size_type);
				while (i < this->size_type)
				{
					this->vectr[i] = ve[i];
					i++;
				}
				return *this;
			}
			//Data Types
			private:
				allocator_type							_alloc;
				T*										vectr;
				unsigned	long						i;
	};

	struct Iterator{
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = int;
		using pointer = int*;
		using reference = int&;

		// Iterator tags here...
		Iterator(pointer ptr) : m_ptr(ptr) {}
		pointer m_ptr;
		// Iterator constructors here...

		reference operator*() const { return *m_ptr; }
		pointer operator->() { return m_ptr; }

		// Prefix increment
		Iterator& operator++() { m_ptr++; return *this; }  

		// Postfix increment
		Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
		friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
    	friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };
		Iterator begin() { return Iterator(&m_data[0]); }
    	Iterator end()   { return Iterator(&m_data[200]); } // 200 is out of bounds
	};
};

#endif