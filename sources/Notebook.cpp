#include "Notebook.hpp"
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using namespace ariel;

/*
* This function gets a page number, row number, column number and number of chars to read horizontally.
* The function returns the desired string from the notebook.
*/
string Notebook::read_horizontal(int page, int row, int column, int number_of_chars)
{
	if (number_of_chars > 'd' || column + number_of_chars > 'd')
	{
		throw invalid_argument("Out of bounds!");
	}
	string desired_string;
	if (this->pages.find(page) != this->pages.end())
	{
		unordered_map<int, string> p = this->pages.at(page);
		if (p.find(row) != p.end())
		{
			string check = p.at(row);
			desired_string = check.substr(size_t(column), size_t(number_of_chars));
		}
		else
		{
			string new_row = "____________________________________________________________________________________________________";
			p[row] = new_row;
			this->pages[page] = p;
			desired_string = new_row.substr(size_t(column), size_t(number_of_chars));
		}
	}
	else
	{
		unordered_map<int, string> p;
		string new_row = "____________________________________________________________________________________________________";
		p[row] = new_row;
		this->pages[page] = p;
		desired_string = new_row.substr(size_t(column), size_t(number_of_chars));
	}
	return desired_string;
}

/*
* This function gets a page number, row number, column number and number of chars to read vertically.
* The function returns the desired string from the notebook.
*/
string Notebook::read_vertical(int page, int row, int column, int number_of_chars)
{
	string desired_string;
	if (this->pages.find(page) != this->pages.end())
	{
		unordered_map<int, string> p = this->pages.at(page);
		for (int i = 0; i < number_of_chars; i++)
		{
			if (p.find(row + i) != p.end())
			{
				string check = p.at(row + i);
				desired_string += check.substr(size_t(column), 1);
			}
			else
			{
				string new_row = "____________________________________________________________________________________________________";
				p[int(row + i)] = new_row;
				desired_string += '_';
			}
		}
		this->pages[page] = p;
	}
	else
	{
		unordered_map<int, string> p;
		for (int i = 0; i < number_of_chars; i++)
		{
			string new_row = "____________________________________________________________________________________________________";
			p[int(row + i)] = new_row;
			desired_string += '_';
		}
		this->pages[page] = p;
	}
	return desired_string;
}

/*
* This function gets a page number, row number, column number, direction and number of chars to read.
* The function returns the desired string from the notebook.
*/
string Notebook::read(int page, int row, int column, Direction direction, int number_of_chars)
{
	if (page < 0 || row < 0 || column < 0 || number_of_chars < 0)
	{
		throw invalid_argument("numbers need to be non-negative!");
	}
	if (column > 'c')
	{
		throw invalid_argument("Max column is 99!");
	}
	if (number_of_chars == 0)
	{
		return "";
	}
	string desired_string;
	if (direction == Direction::Horizontal)
	{
		desired_string = this->read_horizontal(page, row, column, number_of_chars);
	}
	else
	{
		desired_string = this->read_vertical(page, row, column, number_of_chars);
	}
	return desired_string;
}

/*
* This function gets a page number, row number, column number and string to write horizontally.
* The function writes the desired string to the notebook.
*/
void Notebook::write_horizontal(int page, int row, int column, const string & to_write)
{
	if (int(to_write.length()) > 'd' || column + int(to_write.length()) > 'd')
	{
		throw invalid_argument("Out of bounds!");
	}
	string check = this->read_horizontal(page, row, column, to_write.length());
	for (unsigned int i = 0; i < check.length(); i++)
	{
		if (check.at(i) != '_')
		{
			throw invalid_argument("Can't write on a written place!");
		}
	}
	unordered_map<int, string> p = this->pages.at(page);
	string old_row = p.at(row);
	string new_row;
	for (unsigned int i = 0; i < column; i++)
	{
		new_row += old_row.at(i);
	}
	new_row += to_write;
	for (unsigned int i = unsigned(column) + to_write.length(); i < 'd'; i++)
	{
		new_row += old_row.at(i);
	}
	p[row] = new_row;
	this->pages[page] = p;
}

/*
* This function gets a page number, row number, column number and string to write vertically.
* The function writes the desired string to the notebook.
*/
void Notebook::write_vertical(int page, int row, int column, const string & to_write)
{
	string check = this->read_vertical(page, row, column, to_write.length());
	for (unsigned int i = 0; i < check.length(); i++)
	{
		if (check.at(i) != '_')
		{
			throw invalid_argument("Can't write on a written place!");
		}
	}
	unordered_map<int, string> p = this->pages.at(page);
	for (unsigned int i = 0; i < to_write.length(); i++)
	{
		string old_row = p.at(row + int(i));
		string new_row = old_row.substr(size_t(0), size_t(column));
		new_row += to_write.at(i);
		new_row += old_row.substr(size_t(column)+1, 'd'- size_t(column)-1);
		for (unsigned int j = 0; j < unsigned(column); j++)
		{
			new_row += old_row.at(j);
		}
		new_row += to_write.at(i);
		for (unsigned int j = unsigned(column) + 1; j < 'd'; j++)
		{
			new_row += old_row.at(j);
		}
		p[row + int(i)] = new_row;
	}
	this->pages[page] = p;
}

/*
* This function gets a page number, row number, column number, direction and string to write.
* The function writes the desired string to the notebook.
*/
void Notebook::write(int page, int row, int column, Direction direction, string to_write)
{
	for (unsigned int i = 0; i < to_write.length(); i++)
	{
		if (to_write.at(i) < '!' || to_write.at(i) >= '~')
		{
			if (to_write.at(i) != ' ')
			{
				throw invalid_argument("Invalid string to write!");
			}
		}
	}
	if (column > 'c')
	{
		throw invalid_argument("Max column is 99!");
	}
	if (page < 0 || row < 0 || column < 0)
	{
		throw invalid_argument("Page, Row, and Column must be non-negative!");
	}
	if (direction == Direction::Horizontal)
	{
		this->write_horizontal(page, row, column, to_write);
	}
	else
	{
		this->write_vertical(page, row, column, to_write);
	}
}

/*
* This function gets a page number, row number, column number and number of chars to erase horizontally.
* The function erases the desired string from the notebook.
*/
void Notebook::erase_horizontal(int page, int row, int column, int number_of_chars)
{
	string check = this->read_horizontal(page, row, column, number_of_chars);
	unordered_map<int, string> p = this->pages.at(page);
	string old_row = p.at(row);
	string new_row;
	for (unsigned int i = 0; i < column; i++)
	{
		new_row += old_row.at(i);
	}
	for (int i = column; i < column + number_of_chars; i++)
	{
		new_row += '~';
	}
	for (unsigned int i = unsigned(column + number_of_chars); i < 'd'; i++)
	{
		new_row += old_row.at(i);
	}
	p[row] = new_row;
	this->pages[page] = p;
}

/*
* This function gets a page number, row number, column number and number of chars to erase vertically.
* The function erases the desired string from the notebook.
*/
void Notebook::erase_vertical(int page, int row, int column, int number_of_chars)
{
	string check = this->read_vertical(page, row, column, number_of_chars);
	unordered_map<int, string> p = this->pages.at(page);
	for (int i = 0; i < number_of_chars; i++)
	{
		string old_row = p.at(row + i);
		string new_row;
		for (unsigned int j = 0; j < unsigned(column); j++)
		{
			new_row += old_row.at(j);
		}
		new_row += '~';
		for (unsigned int j = unsigned(column) + 1; j < 'd'; j++)
		{
			new_row += old_row.at(j);
		}
		p[int(row + i)] = new_row;
	}
	this->pages[page] = p;
}

/*
* This function gets a page number, row number, column number, direction and number of chars to erase.
* The function erases the desired string from the notebook.
*/
void Notebook::erase(int page, int row, int column, Direction direction, int number_of_chars)
{
	if (page < 0 || row < 0 || column < 0 || number_of_chars < 0)
	{
		throw invalid_argument("Page, Row, and Column must be non-negative!");
	}
	if (column > 'c')
	{
		throw invalid_argument("Max column is 99!");
	}
	if (direction == Direction::Horizontal)
	{
		this->erase_horizontal(page, row, column, number_of_chars);
	}
	else
	{
		this->erase_vertical(page, row, column, number_of_chars);
	}
}

/*
* This function gets a page number.
* The function shows the desired page from the notebook.
*/
void Notebook::show(int page)
{
	if (page < 0)
	{
		throw invalid_argument("Page must be non-negative!");
	}
	if (this->pages.find(page) != this->pages.end())
	{
		unordered_map<int, string> p = this->pages.at(page);
		vector <int> vec;
		vec.reserve(p.size());
		for (const auto & pair : p)
		{
			vec.push_back(pair.first);
		}
		sort(vec.begin(), vec.end());
		if (vec[0] != 0)
		{
			string first_row = this->read_horizontal(page, vec[0] - 1, 0, 'd');
			cout << first_row << endl;
		}
		for (unsigned int i = 0; i < vec.size(); i++)
		{
			cout << p.at(vec[i]) << endl;
		}
		string last_row = this->read_horizontal(page, vec[vec.size() - 1] + 1, 0, 'd');
		cout << last_row << endl;
	}
	else
	{
		cout << "Empty page!" << endl;
	}
}