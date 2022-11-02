/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalek <asalek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:50:30 by asalek            #+#    #+#             */
/*   Updated: 2022/11/02 13:41:52 by asalek           ###   ########.fr       */
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
		size_t							size_type;
		public:
			typedef	T						value_type;
			typedef Allocator				allocator_type;
			typedef	T&						reference;
			typedef	const T&				const_reference;
			typedef	T*						pointer;
			typedef	const T*				const_pointer;
			typedef	ft::random_Iter<T>		iterator;
			typedef	ft::random_Iter<const T>citerator; //const iterator
			
			//Connstructors & Destructor
			Vector(const allocator_type& alloc = allocator_type()):size_type(0), _capacity(0)
			{
				this->_alloc = alloc;
			};
			Vector(const Vector &ve){*this = ve; }
			Vector(size_t size, const value_type& value = value_type(), const allocator_type& alloc = allocator_type()):size_type(0), _capacity(0)
			{
				this->_alloc = alloc;
				if (size > _alloc.max_size())
					throw std::length_error("allocator type T failed to allocate, max size reached");
				this->vectr = _alloc.allocate(size);
				for (size_t i = 0; i < size; i++)
					_alloc.construct(&(vectr[i]), value); //put value in vectr[size] (vectr + size) || &(vectr[size])
				this->size_type = size;
				this->_capacity = size;
			}
			~Vector() throw()
			{
				for (size_t i = 0; i < this->size_type; i++)
					_alloc.destroy(vectr + i);
				if(_capacity)
					_alloc.deallocate(vectr, _capacity);
			}
			//Member Functions
			iterator		begin() { return iterator (vectr); };
			citerator		cbegin() const { return (citerator (vectr)); };
			iterator		end() { return iterator(vectr + size_type - 1); };
			citerator		cend() const { return citerator(vectr + size_type - 1); };
			reference		front() {return vectr[0]; };
			reference		back() {return vectr[size_type - 1]; };
			unsigned long	size() {return this->size_type; };
			size_t			capacity() {return this->_capacity; };
			size_t			max_size() {return _alloc.max_size(); };
			bool			empty() {return this->size_type > 0 ? false : true; };
			reference		at(size_t n) {return (n < size_type && n >= 0) ? (vectr[n]) : throw std::length_error("std::out_of_range\n"); };
			const_reference	at(size_t n) const {return (n < size_type && n >= 0) ? (vectr[n]) : throw std::length_error("std::out_of_range\n"); };
			void			shrink_to_fit()
			{
				if (_capacity > this->size_type)
					reduceContainerSize(size_type);
				else
					return ;
			}
			void			resize(size_t n, value_type val = value_type())
			{
				if (n > this->max_size() || n < 0)
					throw std::length_error("allocator failed to allocate, max/min size reached");
				if (n < size_type)
				{
					for (size_t	i = n; i < size_type; i++)
						_alloc.destroy(vectr + i);
					this->size_type = n;
				}				
				else if (n > this->size_type)
				{
					reserve(n);
					for (; size_type < n; size_type++)
						_alloc.construct(this->vectr + this->size_type, val);					
				}
			}
			void			reserve(size_t n)
			{
				if (n < 0 || n > this->max_size())
					throw std::length_error("allocator failed to allocate, max/min size reached");
				if (n <= this->_capacity)
					return ;
				if (_capacity > 0)
					_alloc.deallocate(vectr, _capacity);
				if (_capacity == 0 || (n > _capacity * 2))
					_capacity = n;
				else if (n > _capacity)
					_capacity *= 2;
				Vector vec(*this);
				try	{ vectr = _alloc.allocate(_capacity); }
				catch (const std::exception &e)
				{
					*this = vec;
					cout << e.what() << '\n';
					throw std::bad_alloc();
				}
				for (size_t i = 0; i < size_type; i++)
					_alloc.construct(vectr + i, vec[i]);
			}
			allocator_type	get_allocator() { return this->_alloc; }
			void			clear()
			{
				for (size_t i = 0; i < size_type; i++)
					_alloc.destroy(vectr + i);
				size_type = 0;
			}
			//Operators
			reference operator[] (size_t n)
			{
				if (n < 0 || n >= this->size_type)
					return vectr[size_type - 1];
				else
					return vectr[n];
			}
			const_reference operator[] (size_t n) const
			{
				if (n < 0 || n >= this->size_type)
					return vectr[size_type - 1];
				else
					return vectr[n];
			}
			Vector	&operator=(const Vector &ve)
			{
				i = 0;
				if (this == &ve)
					return *this;
				this->size_type = ve.size_type;
				this->vectr = _alloc.allocate(this->size_type);
				while (i < this->size_type)
				{
					_alloc.construct(vectr + i, ve[i]);
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
			
			//extra methods
				void	reduceContainerSize(size_t n)
				{
					Vector new_p(*this);
					for (size_t i = 0; i < size_type; i++)
						_alloc.destroy(vectr + i);
					_alloc.deallocate(vectr, size_type);
					try	{ vectr = _alloc.allocate(n); }
					catch (const std::exception &e)
					{
						*this = new_p;//in case of failed to allocate, data got stored
						cout << e.what() << '\n';
						throw std::bad_alloc();
					}
					for (size_t i = 0; i < size_type; i++)
						_alloc.construct(vectr + i, new_p[i]);
					_capacity = n;
					size_type = n;
				}
	};
}

#endif
