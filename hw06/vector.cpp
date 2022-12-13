#include "vector.h"
#include <iterator>

namespace linalg
{
	auto operator<<(std::ostream& ostr, const Vector& x) -> std::ostream& {
		ostr << "[ ";
		std::ranges::copy(x, std::ostream_iterator<float>(ostr, " "));
		ostr << "]";
		return ostr;
	}

	auto min(const Vector& x) -> float
	{
		return *std::ranges::min_element(x);
	}

	auto max(const Vector& x) -> float
	{
		return *std::ranges::max_element(x);
	}

	auto argmin(const Vector& x) -> std::size_t
	{
		
		return std::ranges::min_element(x) - x.begin();
	}

	auto argmax(const Vector& x) -> std::size_t
	{
		
		return std::ranges::max_element(x) - x.begin();
	}

	auto non_zeros(const Vector& x) -> std::size_t
	{
		size_t count{0};
		
		for (const auto& item : x)
		{
			if (item != 0)
			{
				count++;
			}
		}
		return count;
	}

	auto sum(const Vector& x) -> float
	{
		float result{ 0.f };
		for (const auto& item : x)
		{
			result += item;
		}
		return result;
	}

	auto prod(const Vector& x) -> float
	{
		if (x.size() == 0) { return 0; }
		float result{ 1.f };
		for (const auto& item : x)
		{
			result *= item;
		}
		return result;
	}

	auto dot(const Vector& x, const Vector& y) -> float
	{
		if (x.size() != y.size()) { throw std::invalid_argument({ "Argument sizes don't match" }); }
		float sum{ 0.f };
		for (auto i = 0; i < x.size(); i++)
		{
			sum += x[i] * y[i];
		}
		return sum;
	}

	auto norm(const Vector& x) -> float
	{
		float sum{ 0.f };
		for (const auto& item : x) 
		{
			sum += item * item;
		}
		return sum;
	}

	auto normalize(Vector& x) -> void
	{
		float magnitude{0.f};
		for (const auto& item : x)
		{
			magnitude += item * item;
		}
		x /= magnitude;
	}

	auto normalized(const Vector& x) -> Vector
	{
		float magnitude = 0;
		for (const auto& item : x)
		{
			magnitude += item * item;
		}
		Vector newVec(x.size());
		newVec.assign(x);
		newVec /= magnitude;
		return newVec;
	}

	auto floor(const Vector& x) -> Vector
	{
		Vector result(x);

		for (auto& item : result)
		{
			item = std::floor(item);
		}

		return result;
	}

	auto ceil(const Vector& x) -> Vector
	{
		Vector result(x);

		for (auto& item: result)
		{
			item = std::ceil(item);
		}

		return result;
	}

	auto operator+(const Vector& x) -> Vector
	{
		return x;
	}

	auto operator-(const Vector& x) -> Vector
	{
		Vector result(x);

		for (auto& item: result)
		{
			item = -item;
		}
		return result;
	}

	auto operator+(const Vector& x, const Vector& y) -> Vector
	{
		if (x.size() != y.size()) { throw std::invalid_argument({ "Argument sizes don't match" }); }
		Vector result(x);
		result += y;
		return result;
	}

	auto operator-(const Vector& x, const Vector& y) -> Vector
	{
		if (x.size() != y.size()) { throw std::invalid_argument({ "Argument sizes don't match" }); }
		Vector result(x);
		result -= y;
		return result;
	}

	auto operator+(const Vector& x, float val) -> Vector
	{
		Vector result(x);
		result += val;
		return result;
	}

	auto operator-(const Vector& x, float val) -> Vector
	{
		Vector result(x);
		result -= val;
		return result;
	}

	auto operator*(const Vector& x, float val) -> Vector
	{
		Vector result(x);
		result *= val;
		return result;
	}

	auto operator/(const Vector& x, float val) -> Vector
	{
		Vector result(x);
		result /= val;
		return result;
	}

	auto operator+(float val, const Vector& x) -> Vector
	{
		Vector result(x);
		result += val;
		return result;
	}

	auto operator-(float val, const Vector& x) -> Vector
	{
		Vector result(x);
		result -= val;
		return result;
	}

	auto operator*(float val, const Vector& x) -> Vector
	{
		Vector result(x);
		result *= val;
		return result;
	}

	Vector::Vector(std::size_t n)
	{
		data_.resize(n);
	}

	Vector::Vector(std::size_t n, float val)
	{
		for (auto i = 0; i < n; i++)
		{
			data_.push_back(val);
		}
	}

	Vector::Vector(std::initializer_list<float> list)
	{
		data_.assign( list );
	}

	auto Vector::operator=(float val) -> Vector&
	{
		for (auto& item : data_)
		{
			item = val;
		}
		return *this;
	}

	auto linalg::Vector::assign(float val) -> void
	{
		for (auto& item : data_)
		{
			item = val;
		}
	}

	auto linalg::Vector::assign(Vector v) -> void
	{
		for (const auto& item : v)
		{
			data_.push_back(item);
		}
	}

	auto linalg::Vector::size() const -> std::size_t
	{
		return std::size(data_);
	}

	auto linalg::Vector::begin() -> iterator
	{
		return std::begin(data_);
	}

	auto linalg::Vector::end() -> iterator
	{
		return std::end(data_);
	}

	auto linalg::Vector::begin() const -> const_iterator
	{
		return std::begin(data_);
	}

	auto linalg::Vector::end() const -> const_iterator
	{
		return  std::end(data_);
	}

	auto linalg::Vector::cbegin() const -> const_iterator
	{
		return  std::cbegin(data_);
	}

	auto linalg::Vector::cend() const -> const_iterator
	{
		return  std::cend(data_);
	}

	auto linalg::Vector::operator[](int idx) -> float&
	{
		if (idx < 0) { idx = data_.size() + idx;}
		return data_[idx];
	}

	auto linalg::Vector::operator[](int idx) const -> const float&
	{
		if (idx < 0) { idx = data_.size() + idx; }
		return data_[idx];
	}

	auto linalg::Vector::coeff(int idx) -> float&
	{
		if (idx >= data_.size()) { throw std::out_of_range({ "Index argument out of range" }); }
		return data_.at(idx);
	}

	auto linalg::Vector::coeff(int idx) const -> const float&
	{
		if (idx >= data_.size()) { throw std::out_of_range({ "Index argument out of range" }); }
		return data_.at(idx);
	}

	auto linalg::Vector::operator+=(float val) -> Vector&
	{
		for(auto& item : data_)
		{
			item += val;
		}
		return *this;
	}

	auto linalg::Vector::operator-=(float val) -> Vector&
	{
		for (auto& item : data_)
		{
			item -= val;
		}
		return *this;
	}

	auto linalg::Vector::operator*=(float val) -> Vector&
	{
		for (auto& item : data_)
		{
			item *= val;
		}
		return *this;
	}

	auto linalg::Vector::operator/=(float val) -> Vector&
	{
		for (auto& item : data_)
		{
			item /= val;
		}
		return *this;
	}

	auto linalg::Vector::operator+=(const Vector& y) -> Vector&
	{
		if (data_.size() != y.size()) { throw std::invalid_argument({ "Argument sizes don't match" }); }
		for (auto i = 0; i < data_.size(); i++)
		{
			data_[i] += y[i];
		}
		return *this;
	}

	auto linalg::Vector::operator-=(const Vector& y) -> Vector&
	{
		if (data_.size() != y.size()) { throw std::invalid_argument({ "Argument sizes don't match" }); }
		for (auto i = 0; i < data_.size(); i++)
		{
			data_[i] -= y[i];
		}
		return *this;
	}

}

/*
 * Please Implement all functions from the header file here!#
 * Have fun! :-) And don't forget maybe you can use standard algorithms ;-)
 */
