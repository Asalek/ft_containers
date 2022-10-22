/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalek <asalek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:50:30 by asalek            #+#    #+#             */
/*   Updated: 2022/10/22 22:39:00 by asalek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
#define VECTOR_H

#include "iterators.hpp"

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
			typedef	ft::random_Iter<T>		iterator;
			size_t							size_type;

			//Connstructors & Destructor
			Vector():size_type(0), _capacity(0)
			{
				vectr = _alloc.allocate(0);
			};
			Vector(Vector &ve){*this = ve;}
			Vector(size_t size, unsigned long value)
			{
				_capacity = 987;//change when reserve is implemented
				if (size > _alloc.max_size())
					throw std::length_error("allocator type T failed to allocate, max size reached");
				vectr = _alloc.allocate(size);
				size_type = size;
				while (--size)
					vectr[size] = value;
				vectr[0] = value;
			}
			
			//Member Functions
			iterator		begin() { return iterator (vectr); };
			iterator		end() { return iterator(vectr + size_type - 1); }
			reference		front() {return vectr[0]; }
			reference		back() {return vectr[size_type - 1]; }
			unsigned long	size() {return this->size_type; }
			size_t			capacity() {return this->_capacity; }
			size_t			max_size() {return _alloc.max_size(); }
			bool			empty() {return this->size_type > 0 ? false : true; }

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
				// if (this->size_type > 0)
				// 	_alloc.deallocate(this->vectr, this->size_type);
				this->size_type = ve.size_type;
				this->vectr = _alloc.allocate(this->size_type);
				while (i < this->size_type)
				{
					this->vectr[i] = ve[i];
					i++;
				}
				this->_capacity = ve._capacity;
				return *this;
			}
			
			//Data Types
			private:
				allocator_type							_alloc;
				T*										vectr;
				unsigned	long						i;
				size_t						_capacity;
	};
}

#endif