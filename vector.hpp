/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalek <asalek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:50:30 by asalek            #+#    #+#             */
/*   Updated: 2022/10/18 07:42:28 by asalek           ###   ########.fr       */
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
			T*								vectr;
		//member types
//vectr = _alloc.allocate(3);
// alloc.deallocate(pointer, 3);
			Vector():size_type(0)
			{
				vectr = _alloc.allocate(0);
			};
			Vector(int size, int value)
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
			void	resize(int	new_size)
			{
				if (new_size <= _alloc.max_size())
				{
					vectr = _alloc.allocate(new_size);
				}
				else
					throw length_error();
			}
			class length_error : public std::logic_error
			{
				public:
					explicit length_error (const string& what_arg);
			};
			private:
				allocator_type							_alloc;
	};
};

#endif