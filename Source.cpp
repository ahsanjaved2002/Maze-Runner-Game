#include <iostream>
#include <fstream>
using namespace std;

void Get_Data_From_File(char* filename, char** &data, int &rows, int &cols)
{
	if (data != nullptr)
	{
		for (int i = 0; i < rows; i++)
			delete[] data[i];
		delete[] data;
	}

	ifstream fin(filename);
	fin >> rows;
	fin >> cols;
	data = new char*[rows];

	for (int i = 0; i < rows; i++)
		data[i] = new char[cols];

	for (int i = 0; i < rows; i++)
	for (int j = 0; j < cols; j++)
		fin >> data[i][j];

}

void Print_Maze(char** data, int rows, int cols)
{
	if (data != nullptr)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				cout << data[i][j] << "\t\t";
			}
			cout << endl;
		}
	}
	else
		cout << "Data is Empty " << endl;
}

bool Moves_Input(char input, int &curr_row, int &curr_col, char** data, int rows, int cols)
{
	if (input == 'U' || input == 'D' || input == 'L' || input == 'R' || input == 'u' || input == 'd' || input == 'l' || input == 'r')
	{

		if (input == 'U' || input == 'u')
		{
			curr_row--;
			if (curr_row < 0)
			{
				curr_row++;
				return false;
			}
			else if (data[curr_row][curr_col] != '*' && data[curr_row][curr_col] != '1')
			{
				curr_row++;
				return false;
			}
		}
		else if (input == 'D' || input == 'd')
		{
			curr_row++;
			if (curr_row >= rows)
			{
				curr_row--;
				return false;
			}
			else if (data[curr_row][curr_col] != '*' && data[curr_row][curr_col] != '1')
			{
				curr_row--;
				return false;
			}
		}
		if (input == 'L' || input == 'l')
		{
			curr_col--;
			if (curr_col < 0)
			{
				curr_col++;
				return false;
			}
			else if (data[curr_row][curr_col] != '*' && data[curr_row][curr_col] != '1')
			{
				curr_col++;
				return false;
			}
		}
		else if (input == 'R' || input == 'r')
		{
			curr_col++;
			if (curr_col >= cols)
			{
				curr_col--;
				return false;
			}
			else if (data[curr_row][curr_col] != '*' && data[curr_row][curr_col] != '1')
			{
				curr_col--;
				return false;
			}
		}
	}
	else
		return false;

	return true;
}

int main()
{
back:
	char filename[30];
	cout << "Enter Your Name with .txt File Extension : ";
	cin >> filename;
	char** data = nullptr;
	int rows, cols;
	Get_Data_From_File(filename, data, rows, cols);
	cout << "Enter The Mode of Game " << endl;
	cout << "For Easy Mode Press 1 " << endl;
	cout << "For Medium Mode Press 2 " << endl;
	cout << "For Hard Mode Press 3 " << endl;
	cout << "For Checking Statics Press 6 " << endl;
	int opt;
	do{
		cout << "Enter Your Option : ";
		cin >> opt;
		if (opt == 1 || opt == 2 || opt == 3)
			break;
		if (opt == 6)
		{
			ifstream record("highrecord.txt");
			cout << "- NAME -       - SCORE - " << endl;
			char recordname[40];
			int recordscore;
			while (record.eof() == false)
			{
				record >> recordname;
				record >> recordscore;
				cout << "  " << recordname << "            " << recordscore << endl;
			}
		}
		else
			cout << "Wrong Input " << endl;
		cout << "Enter The Mode of Game " << endl;
		cout << "For Easy Mode Press 1 " << endl;
		cout << "For Medium Mode Press 2 " << endl;
		cout << "For Hard Mode Press 3 " << endl;
	} while (1);
	int lives = 0, moves = rows + cols + cols / 2;
	if (opt == 1)
		lives = 3;
	else if (opt == 2)
		lives = 2;
	else if (opt == 3)
		lives = 1;

	//    Print_Maze(data, rows, cols);
	int curr_row = 0, curr_col = 0;
	char input;
	bool won = 0, lost = 0;
	data[0][0] = '0';
	while (1)
	{
		data[curr_row][curr_col] = '0';
		Print_Maze(data, rows, cols);
		cout << " Press U For Up" << endl;
		cout << " Press D For Down" << endl;
		cout << " Press L For Left" << endl;
		cout << " Press R For Right" << endl;
		cout << " The Character * Is Path IS Free To Go:" << endl;
		cout << " The Character | Is Blockage In Path" << endl;
		cout << " The Character + Is Monster Creature In Path" << endl;
		cout << " The Character 0 Shows your Current Location in Maze" << endl;
		cout << " You Have Only " << lives << " Lives " << endl;
		cout << " You Have Only " << moves << " Moves " << endl;
		cout << " You Enter 1 Moves " << endl;
		cout << " Enter your Command : ";
		cin >> input;
		data[curr_row][curr_col] = '1';
		if (Moves_Input(input, curr_row, curr_col, data, rows, cols) == 0)
		{
			cout << endl << " ----- > Wrong Move < ----- " << endl << endl;
			lives--;
			if (lives != 0)
			{
				cout << "Enter 2 for Resume from Start " << endl;
				cout << "Enter 3 for Resume the Game Where You Left " << endl;
				int opt;
				do{
					cout << "Enter Your Option : ";
					cin >> opt;
					if (opt == 2 || opt == 3)
						break;
					cout << "Wrong Input " << endl;
				} while (1);
				if (opt == 2)
				{
					Get_Data_From_File(filename, data, rows, cols);
					curr_row = 0;
					curr_col = 0;
					data[0][0] = '0';
				}
			}
			moves = rows + cols + cols / 2 + 1;

		}
		else
			data[curr_row][curr_col] = '0';
		if (lives == 0 || moves == 0)
		{
			lost = 1;
			break;
		}
		if (data[rows - 1][cols - 1] == '0')
		{
			won = 1;
			break;
		}

		moves--;


	}
	int score = 0;
	char name[40];

	if (won == 1)
	{
		score = rows + cols + cols / 2;
		score = score - moves;
		score = score * 10;
		cout << "Congratulations ! you have ended the the game !!" << endl;
		cout << " >>>>>> || YOU WON || <<<<<<<<" << endl;
		cout << "Enter YOur Name (only First Name) : ";
		cin >> name;
		cout << "Thank You for Playing " << name << endl;
		cout << "Your Score is " << score << endl;

		ofstream record2("highrecord.txt", ios::app);
		record2 << endl << name << " " << score << endl;


	}
	if (lost == 1)
	{
		cout << "Your Lost !!!!" << endl;
		cout << "You Want to play again press 1 " << endl;
		cout << "Press any key to Exit " << endl;
		int opt;
		cin >> opt;
		if (opt == 1)
			goto back;
	}
	cout << "Thank you For Playing !!! " << endl;
	cout << "Signing out " << endl;
	for (int i = 0; i < rows; i++)
		delete[] data[i];
	delete[] data;


	return 0;
}
