#ifndef VECTOR_HPP
# define VECTOR_HPP
# include "Iterator.hpp"
# include <memory>
# include <limits>

namespace ft
{
	template <typename T, typename Category = random_access_iterator_tag>
	class IteratorVector
	{
		private:
				T							*ptr_;
		public:
				typedef T					value_type;
				typedef std::ptr_diff_t		difference_type;
				typedef T*					pointer;
				typedef T&					reference;
				typedef Category			iterator_category;

				IteratorVector() : ptr_(nullptr) {};
				~IteratorVector() {};
				IteratorVector(T *ptr_) : ptr_(ptr_) {};

				IteratorVector(const IteratorVector<T> &copy) : ptr_(nullptr)
				{
					*this = copy;
				}

				IteratorVector<T>& operator=(const IteratorVector<T> &rhs)
				{
					if (this == &rhs)
						return (*this);

					this->ptr_ = rhs.ptr_;

					return (*this);
				}

				IteratorVector<T> &operator++(void)
				{
					++this->ptr_;
					return (*this);
				}

				IteratorVector<T> operator++ (int)
				{
					IteratorVector<T> tmp(*this);
					this->operator++();
					return (tmp);
				}
				
				IteratorVector<T> &operator--(void)
				{
					--this->ptr_;
					return (*this);
				}

				IteratorVector<T> operator-- (int)
				{
					IteratorVector<T> tmp(*this);
					this->operator--();
					return (tmp);
				}

				// 클래스 밖에서 구현된다면? 클래스 밖 주석 참고!
				bool operator==(const IteratorVector<T> &rhs) const
				{
					return (this->ptr_ == rhs.ptr_);
				}

				bool operator!=(const IteratorVector<T> &rhs) const
				{
					return (this->ptr_ != rhs.ptr_);
				}

				bool operator<(const IteratorVector<T> &rhs) const
				{
					return (this->ptr_ < rhs.ptr_);
				}

				bool operator>(const IteratorVector<T> &rhs) const
				{
					return (this->ptr_ > rhs.ptr_);
				}

				bool operator<=(const IteratorVector<T> &rhs) const
				{
					return (!(this->ptr_ > rhs.ptr_));
				}

				bool operator>=(const IteratorVector<T> &rhs) const
				{
					return (!(this->ptr_ > rhs.ptr_));
				}

				T& operator*(void)
				{
					return (*this->ptr_);
				}

				T* operator->(void)
				{
					return (this->ptr_);
				}

				T& operator[](int n)
				{
					return (*(this->ptr_ + n));
				}

				T	*getptr_(void)
				{
					return (this->ptr_);
				}

				IteratorVector<T> &operator+=(int n)
				{
					while (n-- > 0)
						++ptr_;
					while (n++ > 0)
						--ptr_;
					return (*this);
				}

				IteratorVector<T> &operator-=(int n)
				{
					while (n-- > 0)
						--ptr_;
					while (n++ > 0)
						++ptr_;
					return (*this);
				}

				difference_type operator-(const IteratorVector<T> &rhs) const
				{
					return (this->ptr() - rhs.ptr());
				}

	};

	// +, - 이항 연산자는 클래스 밖에서도 구현할 수 있다.
	// 밖에서 구현할 때 클래스 안 private member를 접근해야 한다면,
	// 클래스 안에서 해당 연산자를 friend 함수로 선언해야 한다.
	// 그러나 밖에서 구현할 때 클래스 안의private member를 사용하지 않아도 된다면,
	// friend 함수로 선언하지 않아도 된다.

	template <typename T>
	IteratorVector<T> operator+(const IteratorVector<T> &iter , int n)
	{
		return (iter.getPtr() + n);
	}

	// 위 함수는 IteratorVector 내에서 오버로딩해도 되지만
	// 같은 + 연산자라도 아래 함수는 오버로딩 할 수 없기 때문에
	// 그냥 밖에서 구현했다. 둘 다 IteratorVector의 public function인 getPtr()만 사용하기 때문에
	// IteratorVector안에서 friend로 선언할 필요가 없다.
	template <typename T>
	IteratorVector<T> operator+(int n, const IteratorVector<T> &iter)
	{
		return (n + iter.getPtr());
	}

	template <typename T>
	IteratorVector<T> operator-(const IteratorVector<T> &iter , int n)
	{
		return (iter.getPtr() - n);
	}

	// IteratorVector 안 == 연산자를 밖에서 구현한다면?
	// template <typename T>
	// bool operator==(const IteratorVector<T> &lhs , const IteratorVector<T> &rhs)
	// {
	// 	return (lhs.getPtr() - rhs.getPtr());
	// }

};


#endif