//#include "Page.hpp"
#include <iostream>
#include "Direction.hpp"
#include <unordered_map>


using namespace std;
using namespace ariel;

namespace ariel {
	class Notebook {
	private:
		unordered_map<int, unordered_map<int, string>> pages;
	public:

		string read_horizontal(int page, int row, int column, int number_of_chars);

		string read_vertical(int page, int row, int column, int number_of_chars);

		string read(int page, int row, int column, Direction direction, int number_of_chars);

		void write_horizontal(int page, int row, int column, const string & to_write);

		void write_vertical(int page, int row, int column, const string & to_write);

		void write(int page, int row, int column, Direction direction, string to_write);

		void erase_horizontal(int page, int row, int column, int number_of_chars);

		void erase_vertical(int page, int row, int column, int number_of_chars);

		void erase(int page, int row, int column, Direction direction, int number_of_chars);

		void show(int page);
	};
}