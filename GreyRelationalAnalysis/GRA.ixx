export module GRA;

import <iostream>;
import <vector>;
import <cmath>;
import <format>;

export namespace gra
{
	template<typename T>
	T sum(std::vector<T>& data) {
		T sum_{};
		for (const auto& value_ : data) sum_ += value_;
		return sum_;
	}

	template<typename T>
	const T minimum(std::vector<T>& data) {
		T min_value_{ data[0] };
		for (const auto& value_ : data) {
			if (min_value_ > value_) {
				min_value_ = value_;
			}
		}
		return min_value_;
	}

	template<typename T>
	const T maximum(std::vector<T>& data) {
		T max_value_{ data[0] };
		for (const auto& value_ : data) {
			if (max_value_ < value_) max_value_ = value_;
		}
		return max_value_;
	}

	template<typename T>
	const T mean(std::vector<T>& data) {
		T sum_{ sum(data) };
		return sum_ / static_cast<double>(data.size());
	}

	template<typename T>
	const T stdev(std::vector<T>& data) {
		/* stdev() is smart-enough to return either a sample or population standard deviation	*/

		size_t count_{ data.size() };
		std::vector<T> numerator_ {};
		T sum_numerator_{};

		for (const auto& value_ : data) numerator_.push_back(std::pow((value_ - mean(data)), 2));	// squared difference between data values and the mean
		for (const auto& value_ : numerator_) sum_numerator_ += value_;		// sum of squared differences on the numerator part

		if (count_ < 30) {
			return std::sqrt(sum_numerator_ / (count_ - 1));
		}
		else {
			return std::sqrt(sum_numerator_ / count_);
		}
	}

	template<typename T>
	std::vector<T> standard_scaler(std::vector<T>& data, bool with_mean, bool with_std) {		// with_mean and with_std should be std::optional<>
		std::vector<T> output_{};

		auto average_{ mean(data) };
		auto std_{ stdev(data) };

		for (auto& value : data) output_.push_back((value - average_) / std_);

		return output_;
	}

	template<typename T>
	std::vector<T> minmax_scaler(std::vector<T>& data, T range_min, T range_max) {
		std::vector<T> output_;
		T x_std_{};

		const T min_{ minimum(data) };
		const T max_{ maximum(data) };

		if ((static_cast<double>(range_min) == 0.0) && (static_cast<double>(range_max) == 1.0)) {
			for (const auto& x_ : data) {
				x_std_ = (x_ - min_) / (max_ - min_);
				output_.push_back(x_std_);
			}
		}
		else {
			T x_transformed_{};
			const T range_{ range_max - range_min };  // Feature-range desired for transformation

			for (size_t i{}; i < data.size(); i++) {
				x_std_ = (data.at(i) - min_) / (max_ - min_);  // Solve the problem of clipping decimal values (see screen output for reference)
				x_transformed_ = (x_std_ * range_) + min_;
				output_.push_back(x_transformed_);
			}
		}

		return output_;
	}
}	// namespace gra