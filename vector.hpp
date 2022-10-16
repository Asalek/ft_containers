/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalek <asalek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:50:30 by asalek            #+#    #+#             */
/*   Updated: 2022/10/16 15:28:25 by asalek           ###   ########.fr       */
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
	template <typename T, class Allocator=allocator<T> >
	class Vector
	{
		typedef	T	value_type;
		typedef allocator<T>	alloc;
		typedef	T*	pointer;

		public:
		//member types
			int	size;
			Vector()
			{
				pointer = alloc.allocate(3);
				// alloc.deallocate(pointer, 3);
				size = 3;
			};
			~Vector(){};
	};
};

#endif
