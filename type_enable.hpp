#pragma once

namespace ft
{
	template<bool, class T>
	struct enable_if
	{};

	template <class T>
	struct enable_if<true, T>
	{
		typedef T value;
	};

	template <class T, T v>
	struct integral_constant
	{
		typedef T value_type;
		typedef integral_constant<T,v> type;
		static const T value = v;
		operator T() { return value; }
	};

	typedef integral_constant<bool,true> true_type;
	typedef integral_constant<bool,false> false_type;

	template<typename T>
	struct is_integral : public false_type{};
	
	template<>
	struct is_integral<bool> : public true_type{};
	template<>
	struct is_integral<char> : public true_type{};
	template<>
	struct is_integral<char16_t> : public true_type{};
	template<>
	struct is_integral<char32_t> : public true_type{};
	template<>
	struct is_integral<wchar_t> : public true_type{};
	template<>
	struct is_integral<signed char> : public true_type{};
	template<>
	struct is_integral<short int> : public true_type{};
	template<>
	struct is_integral<int> : public true_type{};
	template<>
	struct is_integral<long int> : public true_type{};
	template<>
	struct is_integral<long long int> : public true_type{};
	template<>
	struct is_integral<unsigned char> : public true_type{};
	template<>
	struct is_integral<unsigned short int> : public true_type{};
	template<>
	struct is_integral<unsigned int> : public true_type{};
	template<>
	struct is_integral<unsigned long int> : public true_type{};
	template<>
	struct is_integral<unsigned long long int> : public true_type{};
}
