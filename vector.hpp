/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalek <asalek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:50:30 by asalek            #+#    #+#             */
/*   Updated: 2022/10/18 08:31:57 by asalek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
#define VECTOR_H

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
			Vector():size_type(0)
			{
				vectr = _alloc.allocate(0);
			};
			Vector(unsigned long size, unsigned long value)
			{
				vectr = _alloc.allocate(size);
				size_type = size;
				while (size)
				{
					vectr[size] = value;
					size--;
				}
			}
			//Member Functions
			void	resize(unsigned long	new_size)
			{
				if (new_size <= _alloc.max_size())
					vectr = _alloc.allocate(new_size); // allocate in case of bad allocation it throws bad allocation exception
			}
			
			//Operators
			reference operator[] (unsigned long n)
			{
				if (n < 0 || n > this->size_type)
					return vectr[size_type + 1];
				else
					return vectr[n];
			}
			private:
				allocator_type							_alloc;
				T*										vectr;
	};
};

#endif