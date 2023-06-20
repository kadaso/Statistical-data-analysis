#include <iostream>
#include <vector>
#include <cmath>
#include <format>  // For formatting the output
import GRA;

void print_scaled(std::vector<double>& original, std::vector<double>& scaled)
{
	std::cout << std::format("{:>10} | {:>7}", "Original", "Scaled") << std::endl;  // Output-table header

	size_t count{ original.size() };
	for (size_t i{}; i < count; i++)
	{
		std::cout << std::format("{:>10} | {:>7.4f}\n", original.at(i), scaled.at(i));
	}
	std::cout << std::endl;
}

int main()
{
	std::vector<double> doubles{ 1.5, -3.4, 5.9, 10.27, -5.2 };
	std::vector<int> ints{ -5, -4, -9, 7, 256, -1003, 67, -4, -1003, -1004, 500 };

	std::cout << "Vector of doubles:\n";
	std::cout << "Minimum value (doubles): " << gra::minimum(doubles) << std::endl;
	std::cout << "Maximum value (doubles): " << gra::maximum(doubles) << std::endl;
	std::cout << "Summation (doubles): " << gra::sum(doubles) << std::endl;
	std::cout << "Average value (doubles): " << gra::mean(doubles) << std::endl;
	std::cout << "Sample standard deviation (doubles): " << gra::stdev(doubles) << std::endl;

	std::cout << "\nResults of standard scaling:\n";
	std::vector<double> doubles_std_scaled{ gra::standard_scaler(doubles, 1, 1) };
	print_scaled(doubles, doubles_std_scaled);

	std::cout << "Results of min_max scaling:\n";
	std::vector<double> doubles_minmax_scaled{ gra::minmax_scaler(doubles, 0.0, 100.0) };
	print_scaled(doubles, doubles_minmax_scaled);

	std::cout << "---------------------------\n" << std::endl;

	std::cout << "Vector of ints:\n";
	std::cout << "Minimum value (ints): " << gra::minimum(ints) << std::endl;
	std::cout << "Maximum value (ints): " << gra::maximum(ints) << std::endl;
	std::cout << "Summation (ints): " << gra::sum(ints) << std::endl;
	std::cout << "Average value (ints): " << gra::mean(ints) << std::endl;
	std::cout << "Sample standard deviation (ints): " << gra::stdev(ints) << std::endl;
}