/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalek <asalek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:50:30 by asalek            #+#    #+#             */
/*   Updated: 2022/11/12 15:39:28 by asalek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
#define VECTOR_H

#include "iterators.hpp"
#include "extra_algos.hpp"
#include "type_enable.hpp"

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
		typedef	T									value_type;
		typedef Allocator							allocator_type;
		typedef	T&									reference;
		typedef	const T&							const_reference;
		typedef	T*									pointer;
		typedef	const T*							const_pointer;
		typedef	ft::random_Iter<T>					iterator;
		typedef	ft::random_Iter<const T>			citerator; //const iterator
		typedef ft::reverse_iterator<T> 			r_iterator;
		typedef ft::reverse_iterator<const T>		cr_iterator;
		typedef std::ptrdiff_t						difference_type;
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
			iterator		begin() const { return iterator (vectr); };
			citerator		cbegin() const { return (citerator (vectr)); };
			r_iterator		rbegin() const {return r_iterator(vectr + size_type - 1); }
			r_iterator		rend() const {return r_iterator(vectr); }
			iterator		end() const { return iterator(vectr + size_type - 1); };
			citerator		cend() const { return citerator(vectr + size_type - 1); };
			reference		front() {return vectr[0]; };
			reference		back() {return vectr[size_type - 1]; };
			size_t			size() const {return this->size_type; };
			size_t			capacity() {return this->_capacity; };
			size_t			max_size() {return _alloc.max_size(); };
			bool			empty() const {return this->size_type > 0 ? false : true; };
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
				if (n > this->max_size())
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
			void	swap(Vector &ve)
			{
				std::swap(this->size_type, ve.size_type);
				std::swap(this->_capacity, ve._capacity);
				std::swap(this->_alloc, ve._alloc);
				std::swap(this->vectr, ve.vectr);
			}
			iterator	erase(iterator pos)
			{
				difference_type index = pos - this->begin();
				if (index < 0 || (size_t)index > size_type)
					throw std::out_of_range("out_of_range");
				size_t j = 0;
				for (size_t i = 0; i < size(); i++)
				{
					if (i == (size_t)index)
						_alloc.destroy(&vectr[i++]);
					_alloc.construct(&vectr[j++], vectr[i]);
				}
				size_type--;
				return (iterator(this->vectr + index));
			}
			iterator	erase(iterator from, iterator to)
			{
				difference_type index = from - begin();
				if (((to - from) <= 0) || index < 0)
					throw std::out_of_range("out_of_range");
				size_t	len = 0, j = 0;
				for (size_t i = 0; i < size_type; i++)
				{
					if (i == (size_t)index)
					{
						for (; from != to; from++)
						{
							this->_alloc.destroy(&this->vectr[i++]);
							len++;
						}
					}
					this->_alloc.construct(&vectr[j++], vectr[i]);
				}
				size_type -= len;
				return (iterator(vectr + index));
			}
			void	assign(size_t n, const value_type &val)
			{
				this->resize(n, val);
			}
			void	assign(iterator begin, iterator end)
			{
				difference_type size = end - begin;
				this->resize(size);
				size_t i = 0;
				while (begin != end)
				{
					_alloc.construct(vectr + i, *begin);
					i++;
					begin++;
				}
				size_type = size;
				_capacity = size;
			}
			void	push_back(const value_type &val)
			{
				if (size_type < 10)
					reserve(size_type + 1);
				else if (size_type > (_capacity / 4 * 3))
					reserve(_capacity + (this->_capacity / 4));
				_alloc.construct(vectr + size_type, val);
				size_type++;
			}
			void	pop_back()
			{
				if (size_type < 1)
					return ;
				_alloc.destroy(&vectr[size_type - 1]);
				size_type--;
			}
			iterator insert (iterator position, const value_type& val)
			{
				difference_type index = position - begin();
				if (index < 0)
					throw std::out_of_range("out_of_rang insert()\n");
				reserve(size_type + 1);
				size_type += 1;
				difference_type i = size_type;
				while (--i >= 0)
				{
					if (i == index)
					{
						_alloc.construct(&vectr[i], val);
						return iterator(begin() + index);
					}
					else
						_alloc.construct(&vectr[i], vectr[i - 1]);
				}
				// for (size_t i = 0; i < size_type; i++)
    			// 	cout << vectr[i] << ' ' << endl;
    				cout << size_type << ' ' << endl;
				return iterator(begin() + index);
			}
			void insert (iterator position, size_t n, const value_type& val)
			{
				if (n < 0)
					throw std::out_of_range("out_of_range insert many\n");
				while (n)
				{
					insert(position, val);
					n--;
				}
			}
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::value* = nullptr)
			{
				difference_type len = last - first;
				difference_type index = position - begin();
				Vector<T> tmp(size_type + len + 1, 0);
				
				difference_type ii = 0;
				for (; ii < index; ii++)
					_alloc.construct(&tmp[ii], vectr[ii]);

				for (difference_type i = index; i <= index + len; i++)
					_alloc.construct(&tmp[i], *first++);
				
				for (size_t i = index + len + 1; i < tmp.size(); i++)
				{
					_alloc.construct(&tmp[i], vectr[ii]);
					ii++;
				}
				*this = tmp;
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

	//comparision operators 
	template <class T, class Alloc>
	bool operator== (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
	{
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	};

	template <class T, class Alloc>
	bool operator!= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
	{
		return !(lhs == rhs);
	};

	template <class T, class Alloc>
	bool operator< (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	};

	template <class T, class Alloc>
	bool operator> (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	};

	template <class T, class Alloc>
	bool operator>= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
	{
		return (lhs > rhs || rhs == lhs);
	};

	template <class T, class Alloc>
	bool operator<= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
	{
		return (lhs < rhs || rhs == lhs);
	};
	
	//methods
	template<class T, class allocator>
	void	swap(Vector<T, allocator> &ve, Vector<T, allocator> &ve2)
	{
		ve.swap(ve2);
	}
}

#endif
