/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalek <asalek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:50:30 by asalek            #+#    #+#             */
/*   Updated: 2022/10/20 05:51:57 by asalek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
#define VECTOR_H

#include "iterators.hpp"
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
			typedef	ft::Container<T>			iter;

			//Connstructors & Destructor
			Vector():size_type(0)
			{
				vectr = _alloc.allocate(0);
				capacity = 0;
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
				unsigned	long						capacity;
	};
}

#endif