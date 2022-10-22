/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalek <asalek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:50:30 by asalek            #+#    #+#             */
/*   Updated: 2022/10/22 00:17:21 by asalek           ###   ########.fr       */
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
			Vector():size_type(0), capacity(0)
			{
				vectr = _alloc.allocate(0);
			};
			Vector(Vector &ve){*this = ve;}
			Vector(unsigned long size, unsigned long value)
			{
				vectr = _alloc.allocate(size);//check that size is less than max_size
				size_type = size;
				while (--size)
					vectr[size] = value;
				vectr[0] = value;
			}
			
			//Member Functions
			iterator	begin()
			{
				iterator t(vectr);
				return t;
			};
			// iterator	*end(){return this->vectr[size_type - 1];}
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
				// if (this->size_type > 0)
				// 	_alloc.deallocate(this->vectr, this->size_type);
				this->size_type = ve.size_type;
				this->vectr = _alloc.allocate(this->size_type);
				while (i < this->size_type)
				{
					this->vectr[i] = ve[i];
					i++;
				}
				this->capacity = ve.capacity;
				return *this;
			}
			
			//Data Types
			private:
				allocator_type							_alloc;
				T*										vectr;
				unsigned	long						i;
				unsigned	long						capacity;
	};
}

#endif