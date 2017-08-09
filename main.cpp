#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <ostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <regex>
#include <set>
/*
 *
 */
bool is_palindrome(const std::string & phrase)
{
	std::string temp(phrase.size(), '*');
	auto it = std::remove_copy_if(phrase.begin(), phrase.end(), temp.begin(),
			[](char c) {return !static_cast<bool>(isalpha(c));});
	temp.erase(it, temp.end());
	std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
	auto mid = (int) temp.size() / 2;
	return std::equal(temp.begin(), temp.begin() + mid, temp.rbegin());
}

void test_is_palindrome()
{
	std::string str_i = std::string("Was it a car or a cat I saw?");
	std::string str_u = std::string("Was it a car or a cat U saw?");
	std::cout << "the phrase \""
	             + str_i + "\" is "
	             + (is_palindrome(str_i) ? "" : "not ") << "a palindrome\n";

	std::cout << "the phrase \""
	             + str_u + "\" is "
	             + (is_palindrome(str_u) ? "" : "not ") << "a palindrome\n";
}

template <typename Iterator>
std::pair<Iterator, bool> second_max(Iterator start, Iterator finish)
{
	if ((start + 1) >= finish) {
		return std::pair<Iterator, bool>{finish, false};
	}

	Iterator max1 = start;
	Iterator max2 = start;
	Iterator it = start;

	while (it != finish) {
		if (*it > *max1) {
			max2 = max1;
			max1 = it;
		} else if ((*it < *max1 && *it > *max2) || (*it < *max2 && max1 == max2)){
			max2 = it;
		}
		it++;
	}
	return std::pair<Iterator, bool>{max2, max1 != max2};
};


void test_second_max()
{
	std::vector<int> int_vec{1, 1, 5, 5, 7, 7};

	auto retval = second_max(int_vec.begin(), int_vec.end());
	if (retval.second) {
		std::cout << "The second largest element in int_vec is " << *retval.first << std::endl;
	} else {
		if (retval.first == int_vec.end()) {
			std::cout << "List empty, no elements\n";
		} else {
			std::cout << "Container's elements are all equal to " << *retval.first << std::endl;
		}
	}
}


std::string remove_leading_trailing_nonalpha(const std::string &word)
{
	int b = std::find_if(word.begin(), word.end(), isalpha) - word.begin();
	int e = word.size() - (std::find_if(word.rbegin(), word.rend(), isalpha) - word.rbegin());
    return word.substr(b, e-b);
}

void print_word_frequency_1(const std::string &filename)
{
	std::ifstream ifs (filename);
	if(!ifs) throw std::invalid_argument("could not open file " + filename);

	std::map<std::string, int> word_frequency_map;

	std::string line;
	while (getline(ifs, line)) {
		std::istringstream iss(line);
		std::string word;
		while (iss >> word) {
			++word_frequency_map[remove_leading_trailing_nonalpha(word)];
		}
	}
	int it = 1;
	for (const auto &word : word_frequency_map) {

		std::cout << std::setw(10)
		          << word.first << " " << word.second << std::endl;
	}
}


class MyCompare {
public:
	bool operator()(const std::string & o1, const std::string & o2) const
	{
		std::string o1_temp{o1};
		std::string o2_temp{o2};
		std::transform(o1_temp.begin(), o1_temp.end(), o1_temp.begin(), ::tolower);
		std::transform(o2_temp.begin(), o2_temp.end(), o2_temp.begin(), ::tolower);
		return o1_temp < o2_temp;
	}
};

void print_word_frequency_2(const std::string &filename)
{
	std::ifstream ifs (filename);
	if(!ifs) throw std::invalid_argument("could not open file " + filename);

	std::map<std::string, int, MyCompare> word_frequency_map;

	std::string line;
	while (getline(ifs, line)) {
		std::istringstream iss(line);
		std::string word;
		while (iss >> word) {
			++word_frequency_map[remove_leading_trailing_nonalpha(word)];
		}
	}
	for (const auto &word : word_frequency_map) {

		std::cout << std::setw(10)
		          << word.first << " " << word.second << std::endl;
	}
}


void print_word_index(const std::string & filename)
{
	std::map<std::string, std::set<int>, MyCompare> word_index;

	std::ifstream ifs(filename);
	if (!ifs) throw std::invalid_argument("could not open file " + filename);

	std::string line, word;
	int index = 1;
	while (getline(ifs, line)) {
		std::istringstream iss(line);
		while (iss >> word) {
			word_index[remove_leading_trailing_nonalpha(word)].insert(index);
		}
		++index;
	}
	for (const auto &word : word_index) {
		std::cout << std::setw(10) << word.first;
		for (const auto &line : word.second) {
			std::cout << " " << line;
		}
		std::cout << std::endl;
	}
}
int main()
{
	test_is_palindrome();
	std::cout << "-----------------------------------------------" << std::endl;

	test_second_max();
	std::cout << "-----------------------------------------------" << std::endl;

	std::string filename = "input.txt";

	print_word_frequency_1(filename);
	std::cout << "-----------------------------------------------" << std::endl;

	print_word_frequency_2(filename);
	std::cout << "-----------------------------------------------" << std::endl;

	print_word_index(filename);
	return 0;
}