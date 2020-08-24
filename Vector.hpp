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
				typedef std::ptrdiff_t		difference_type;
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

	template <typename T, typename Alloc = std::allocator<T> >
	class Vector
	{
		private:
				T			*arr_;
				size_t		len_;
				size_t		capa_;
				Alloc		alloc_;
		public:
				typedef T 								value_type;
				typedef Alloc							allocator_type;
				typedef size_t							size_type;
				typedef std::ptrdiff_t					difference_type;
				typedef typename Alloc::reference		reference;
				typedef typename Alloc::const_reference	const_reference;
				typedef typename Alloc::pointer			pointer;
				typedef typename Alloc::const_pointer	const_pointer;
				typedef IteratorVector<T> 				iterator;
				typedef IteratorVector<const T>			const_iterator;
				typedef ReverseIterator<iterator>		reverse_iterator;
				typedef ReverseIterator<const iterator>	const_reverse_iterator;

				explicit Vector(const allocator_type& alloc = allocator_type()) : arr_(nullptr), len_(0), capa_(0), alloc_(alloc)
				{}
				explicit Vector(size_type n, const value_type&val = value_type(), const allocator_type& alloc = allocator_type())
					: arr_(nullptr), len_(0), capa_(0), alloc_(alloc)
				{
					insert(begin(), n, val);
				}

				template <class InputIterator>
         		Vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
					: arr_(nullptr), len_(0), capa_(0), alloc_(alloc)
				{
					insert(begin(), first, last);
				}

				Vector(const Vector<T>& copy) : arr_(nullptr), len_(0), capa_(0) 
				{
					*this = copy;
				}

				~Vector()
				{
					for (unsigned int i = 0; i < len_; ++i)
						alloc_.destroy(&arr_[i]);
					alloc_.deallocate(arr_, capa_);
				};

				Vector<T>& operator=(const Vector<T> &vector)
				{
					if (this == &vector)
						return (*this);

					clear();

					insert(begin(), vector.begin(), vector.end());

					return (*this);
				}

				/*
				**	iterators
				*/

				iterator 		begin(void)
				{
					return (iterator(arr_));
				}

				const_iterator	begin(void) const
				{
					return (const_iterator(arr_));
				}

				iterator 		end(void)
				{
					return (iterator(arr_ + len_));
				}

				const_iterator	end(void) const
				{
					return (const_iterator(arr_ + len_));
				}

				reverse_iterator 		rbegin(void)
				{
					return (reverse_iterator(end()));
				}

				const_reverse_iterator	rbegin(void) const
				{
					return (const_reverse_iterator(end()));
				}

				reverse_iterator 		rend(void)
				{
					return (reverse_iterator(begin()));			
				}

				const_reverse_iterator	rend(void) const
				{
					return (const_reverse_iterator(begin()));
				}

				/*
				**	capacity
				*/

				size_type	size() const
				{
					return (this->len_);
				}

				size_type	max_size() const
				{
					return (std::numeric_limits<size_type>::max() / sizeof(value_type));
				}
				
				void		resize (size_type n, value_type val = value_type())
				{
					if (n < this->len_)
						erase(begin() + n, end());
					else
						insert(end(), n - this->len_, end(), val);
				}

				size_type	capacity() const
				{
					return (this->capa_);
				}
				
				bool		empty() const
				{
					return (this->len_ == 0);
				}

				void		reserve (size_type n)
				{
					if (n > max_size())
						throw std::length_error("ft::vector : You can't reserve this much!");
					if (n > this->capa_)
					{
						T	*new_arr_ = alloc_.allocate(n);

						for (unsigned int i = 0; i < len_; ++i)
							alloc_.construct(&new_arr_[i], arr_[i]);
						alloc_.deallocate(arr_, capa_);
						
						arr_ = new_arr_;
						capa_ = n;
					}
				}

				/*
				**	Element access
				*/

				reference operator[] (size_type n)
				{
					return (arr_[n]);
				}
				const_reference operator[] (size_type n) const
				{
					return (arr_[n]);
				}

				reference at (size_type n)
				{
					if (n >= len_)
						throw std::out_of_range("ft::vector : The index is out of range!");
					return (arr_[n]);
				}
				const_reference at (size_type n) const
				{
					if (n >= len_)
						throw std::out_of_range("ft::vector : The index is out of range!");
					return (arr_[n]);
				}
				reference			front(void)
				{
					return (arr_[0]);
				}

				const_reference		front(void) const
				{
					return (arr_[0]);
				}

				reference			back(void)
				{
					return (arr_[len_ - 1]);
				}

				const_reference		back(void) const
				{
					return (arr_[len_ - 1]);
				}

				/*
				**	modifiers
				*/

				template <typename InputIt>
				void assign(InputIt first, InputIt last)
				{
					clear();
					insert(begin(), first, last);
				}
				void assign(size_type n, const value_type& val)
				{
					clear();
					insert(begin(), n, val);
				}

				void push_back (const value_type& val)
				{
					insert(end(), val);
				}

				void pop_back ()
				{
					erase(end() - 1);
				}

				iterator insert(iterator position, const value_type& val)
				{
					insert(position, (std::size_t)1, val);
					return (position);
				}

				void insert(iterator position, size_type n, const value_type& val)
				{
					if (n == 0)
						return ;
					if (len_ + n + 1 > capa_)
						reserve(len_ + n + 1);

					iterator 	iter = position;
					iterator 	end = this->end();
					int			idx = len_;

					while (iter != end)
					{
						arr_[idx + n] = arr_[idx + n - 1];
						--idx;
						++iter;
					}
					for (unsigned int i = 0; i < n; ++i)
						*(position + i) = val;
					
					this->len_ += n;
					return (iterator(&arr_[position]));
				}

				template <class InputIterator>
				void insert (iterator position, InputIterator first, InputIterator last)
				{
					int n = 0;
					InputIterator save = first;
		
					while (first != last)
					{
						++n;
						++first;
					}

					if (n == 0)
						return ;

					first = save;
					if (len_ + n + 1 > capa_)
						reserve(len_ + n + 1);

					iterator 	iter = position;
					iterator 	end = this->end();
					int			idx = len_;

					while (iter != end)
					{
						arr_[idx + n] = arr_[idx + n - 1];
						--idx;
						++iter;
					}
					for (int i = 0; i < n; ++i)
						*(position + i) = *first++;
					
					this->len_ += n;
					return (iterator(position - n));
				}

				iterator erase (iterator position)
				{
					erase(position, position + 1);
				}

				iterator erase (iterator first, iterator last)
				{
					if (len_ <= 0)
						return first;

					iterator 	end = this->end();

					iterator	iter = first;
					iterator	save_last = last;
					while (last != end)
					{
						*iter = *last;
						++last;
						++iter;
					}
					last = save_last;
					iter = first;
					while (iter != last)
					{
						iter++;
						--this->len_;
					}

					return (first);
				}
				void swap(Vector<T>& other)
				{
					std::swap(arr_, other.arr_);
					std::swap(len_, other.len_);
					std::swap(capa_, other.cap_);
					std::swap(alloc_, other.alloc_);
				}

				void clear()
				{
					erase(begin(), end());
				}
	};

	/*
	**	non-member function overloads
	*/
	template <class T, class Alloc>
	bool operator== (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (0);

		for (unsigned int i = 0; i < lhs.size(); ++i)
		{
			if (lhs[i] != rhs[i])
				return (0);
		}

		return (1);
	}
	
	template <class T, class Alloc>
	bool operator!= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator<  (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
	{
		unsigned int n;
		
		if (lhs.size() < rhs.size())
			n = lhs.size();
		else
			n = rhs.size();

		for (unsigned int i = 0; i < n; ++i)
		{
			if (lhs.at(i) != rhs.at(i))
				return (lhs.at(i) < rhs.at(i));
		}

		return (lhs.size() < rhs.size());
	}

	template <class T, class Alloc>
	bool operator>  (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator<=  (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool operator>=  (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
 	void swap (Vector<T,Alloc>& x, Vector<T,Alloc>& y)
	{
		x.swap(y);
	}

};


#endif