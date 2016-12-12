#pragma once

#include <type_traits>
#include <stdexcept>

template <int low, int high, typename value_p = int>
class bounded_int {
	friend class bounded_int;

	value_p value;
	void on_error(value_p val);
public:
	using value_t = value_p;
	static const value_t min = low;
	static const value_t max = high;

	static_assert(min < max, "Lower bound above upper bound");
	static_assert(std::is_integral_v<value_t>, "Must have integral underlying type");
	// check low/high against numeric_limits min/max

	operator value_t() { return value; }
	bounded_int() {
		if (low <= 0 && high >= 0) value = 0;	// if static
		else value = low;
	}
	bounded_int(value_t init) {
		if (init < min || init > max) on_error(init);
		else value = init;
	}
	bounded_int(const bounded_int & rhs) : value(rhs.value) {};

	template <int rlow, int rhigh>	// how to deal with different int types?
	bounded_int(bounded_int<rlow, rhigh, value_t> r) {
		if (rlow < low)	// if static
			if (r.value < low) { on_error(value); }
		if (rhigh > high) // if static
			if (r.value > high) { on_error(value); }
		value = r.value;
	}

	template <int rlow, int rhigh, int newlow = low+rlow, int newhigh = high+rhigh, typename rtype>	// return type should be the wider of the two, rather than the left?
	bounded_int<newlow, newhigh, value_t> operator+ (bounded_int<rlow, rhigh, rtype> r) {
		bounded_int<newlow, newhigh, value_t> ret; 
		ret.value = value + r.value;
		return ret;
	}

};

template <int low, int high, typename value_p>
void bounded_int<low, high, value_p>::on_error(value_t val) {
//	std::ostringstream s;
//	s << "Value " << val << " not in bounds [" << min << ',' << max << "]";
//	throw std::domain_error(s.str());
	throw std::domain_error("bounded_int out of range");
}

