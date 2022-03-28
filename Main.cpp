#include <iostream>
#include "sources/Notebook.hpp"
#include "sources/Direction.hpp"
using namespace ariel;
using namespace std;

int main()
{
	Notebook nb;
	bool done = false;
	while (!done)
	{
		int choice = 0;
		while (choice != 1 && choice != 2 && choice != 3 && choice != 4)
		{
			cout << "Choose action:\n";
			cout << "1 - Write\n";
			cout << "2 - Read\n";
			cout << "3 - Erase\n";
			cout << "4 - Show\n" << endl;
			cin >> choice;
		}

		int page = -1;
		cout << "Enter page number (non-negative): ";
		cin >> page;

		if (choice != 4)
		{
			int row = -1;
			cout << "Enter row number (non-negative): ";
			cin >> row;

			int column = -1;
			cout << "Enter column number (0-100): ";
			cin >> column;

			int direct = 0;
			cout << "Enter Direction number:\n";
			cout << "1 - Horizontal\n";
			cout << "2 - Vertical\n";
			cin >> direct;
			Direction direction;
			if (direct == 1)
			{
				direction = Direction::Horizontal;
			}
			else
			{
				direction = Direction::Vertical;
			}

			if (choice != 1)
			{
				int chars = -1;
				cout << "Enter characters number (0-100): ";
				cin >> chars;

				if (choice == 2)
				{
					nb.read(page, row, column, direction, chars);
				}
				else
				{
					nb.erase(page, row, column, direction, chars);
				}
			}
			else
			{
				string write;
				cout << "Enter string to write: ";
				cin >> write;

				nb.write(page, row, column, direction, write);
			}
		}
		else
		{
			nb.show(page);
		}

		int check = -1;
		cout << "To finish, enter 1, otherwise, enter 0: ";
		cin >> check;
		if (check == 1)
		{
			done = true;
		}
	}
}