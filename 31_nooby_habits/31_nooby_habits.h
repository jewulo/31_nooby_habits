#pragma once

#include <algorithm>
#include <array>
#include <bit>
#include <iostream>
#include <string>
#include <vector>

// polluting file or procedure with namespace usage
namespace habit_1
{	
	namespace bad
	{
		void using_namespace_std()
		{
			using namespace std;

			string s{ "hello, world!" };
			cout << s << endl;
		}
	}
	namespace good
	{
		void using_namespace_std()
		{
			std::string s{ "hello, world!" };
			std::cout << s << std::endl;
		}
	}
	namespace better
	{
		using std::string;
		using std::cout;
		using std::endl;

		void using_namespace_std()
		{
			string s{ "hello, world!" };
			cout << s << endl;
		}
	}
}
// using std::endl in a loop. std::endl flushes the buffer.
namespace habit_2
{	
	namespace bad
	{
		void print_range(int start, int end)
		{
			for (auto i = start; i != end; ++i)
				std::cout << i << std::endl;
		}
	}
	// use a newline character instead
	namespace good
	{
		void print_range(int start, int end)
		{
			for (auto i = start; i != end; ++i)
				std::cout << i << '\n';
		}
	}
}
// using a for loop to index instead of a range
namespace habit_3
{
	struct Model {
		int data;
		void update(int val){ data = val; }
	};
	namespace bad
	{
		void train_model(const std::vector<int> &data, auto &model)
		{
			for (std::size_t i = 0; i < data.size(); ++i) {
				model.update(data[i]);
			}
		}
	}
	// use a range based for loop without the index
	namespace good
	{
		void train_model(const std::vector<int>& data, auto& model)
		{
			for (const auto &x: data) {
				model.update(data[i]);
			}
		}
	}
}
// using raw loops and conditionals instead of standard algorithms
namespace habit_4
{
	namespace bad
	{
		void know_your_algorithms()
		{
			const std::vector<int> data = { -1,-3,-5,8,15,-1 };

			std::size_t first_pos_idx;
			for (std::size_t i = 0; i < data.size(); ++i) {
				if (data[i] > 0) {
					first_pos_idx = i;
					break;
				}
			}
			// use first_pos_idx...
		}
	}

	namespace good
	{
		void know_your_algorithms()
		{
			const std::vector<int> data = { -1,-3,-5,8,15,-1 };

			const auto is_positive = [](const auto& x) { return x > 0; };
			auto first_pos_it = std::find_if(
						data.cbegin(),
						data.cend(),
						is_positive);
			// use first_pos_it...
		}
	}
}
// using C-style arrays and pointers
namespace habit_5
{
	namespace bad
	{
		void f(int* arr, int n)
		{
			// whatever loop
		}

		void using_c_array()
		{
			const int n = 256;
			int arr[n] = { 0 };

			f(arr, n);	// this is a potential bad bug
		}
	}
	// instead use a standard array.
	namespace good
	{
		template<std::size_t size>
		void better_f(std::array<int, size> &arr)
		{
			// whatever loop
		}

		void using_c_array()
		{
			const int n = 256;
			std::array<int, n> arr{};

			better_f(arr);
		}
	}
}
// any use of reinterpret_cast
namespace habit_6
{
	namespace bad
	{
		void any_use_of_reinterpret_cast()
		{
			long long x = 0;
			auto xp = reinterpret_cast<char*>(x);
			auto x2 = reinterpret_cast<long long>(xp);
		}
	}
	namespace worse
	{
		void any_use_of_c_style_cast()
		{
			float y = .123f;
			long i = *(long*)&y; // Sorry famous Quake III inv_sqrt code
			// ....
			y = *(float *) &i;
		}
	}
	namespace good
	{
		template<typename T>
		void print_bytes(const T& input)
		{
			auto* bytes = reinterpret_cast<const std::byte *>(&input);

			// print out bytes one at a time
		}
	}
	namespace better
	{
		template<typename T>
		void print_bytes(const T& input)
		{
			using bytearray = std::array<std::byte, sizeof(T)>;
			const auto &bytes = std::bit_cast<bytearray, T>(input);

			// print out bytes one at a time
		}
	}
}
https://youtu.be/i_wDa2AS_8w?t=164
namespace habit_7
{
}
