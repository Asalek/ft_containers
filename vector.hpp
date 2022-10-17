/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalek <asalek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:50:30 by asalek            #+#    #+#             */
/*   Updated: 2022/10/17 22:23:29 by asalek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

using	std::cout;
using	std::endl;
using	std::allocator;

namespace ft
{	
	template <typename T, class Allocator = allocator<T> >
	class Vector
	{
		public:
			typedef	T						value_type;
			typedef Allocator				alloc;
			typedef	T*						pointer;
			const T*						const_pointer;
			size_t							size_type;
			// value_type						&reference;
			// const	value_type				&const_reference;
			T*								vectr;
		//member types
			int	size;
			Vector()
			{
				vectr = _alloc.allocate(3);
				// alloc.deallocate(pointer, 3);
				size = 3;
			};
			~Vector(){};
			private:
				alloc							_alloc;
	};
};

#endif
