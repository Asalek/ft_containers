#pragma once
#include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::Vector<T> >
	class stack
	{
		typedef T			value_type;
		typedef Container	container_type;
		size_t				size_type;
		
		public:
			explicit stack (const container_type& ctnr = container_type())
			{
				size_type = 0;
			}
	};
}