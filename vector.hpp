/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalek <asalek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:50:30 by asalek            #+#    #+#             */
/*   Updated: 2022/10/31 11:06:34 by asalek           ###   ########.fr       */
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
			typedef	ft::random_Iter<const T>citerator; //const iterator
			size_t							size_type;

			//Connstructors & Destructor
			Vector():size_type(0), _capacity(0)
			{
				vectr = _alloc.allocate(0);
			};
			Vector(Vector &ve){*this = ve; }
			Vector(size_t size, unsigned long value)
			{
				_capacity = 987;//change when reserve is implemented
				if (size > _alloc.max_size())
					throw std::length_error("allocator type T failed to allocate, max size reached");
				vectr = _alloc.allocate(size);
				size_type = size;
				while (--size)
					_alloc.construct(&(vectr[size]), value); //put value in vectr[size] (vectr + size) || &(vectr[size])
				// 	vectr[size] = value;
				vectr[0] = value;
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
			void			resize(size_t n)
			{
				if (n > this->max_size() || n < 0)
					throw std::length_error("allocator failed to allocate, max/min size reached");
				if (n < this->size_type || n > this->size_type)
					reduceContainerSize(n);
				else
					return ;
			}
			void			reserve(size_t n)
			{
				if (n < 0 || n > this->max_size())
					throw std::length_error("allocator failed to allocate, max/min size reached");
				if (n <= this->_capacity)
					return ;
				if (_capacity == 0 || (n > _capacity * 2))
					_capacity = n;
				else if (n > _capacity)
					_capacity *= 2;
				Vector vec(*this);
				_alloc.deallocate(vectr, size_type);
				try	{ vectr = _alloc.allocate(_capacity); }
				catch (const std::exception &e)
				{
					cout << e.what() << '\n';
					throw std::bad_alloc();
				}
				for (size_t i = 0; i < size_type; i++)
					_alloc.construct(vectr + i, vec[i]);
				_alloc.deallocate(vec.vectr, vec.size_type);
			}
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
						cout << e.what() << '\n';
						throw std::bad_alloc();
					}
					for (size_t i = 0; i < n; i++)
					{
						if (i <= new_p.size_type)
							vectr[i] = new_p.vectr[i];
						else
							vectr[i] = 0;
					}
					_alloc.deallocate(new_p.vectr, n);
					_capacity = n;
					size_type = n;
				}
	};
}

#endif