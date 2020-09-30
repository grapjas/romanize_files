#include "std_lib_facilities.h"

// how to use files
// http://www.cplusplus.com/doc/tutorial/files/
// how to use command line parameters
// http://www.cplusplus.com/articles/DEN36Up4/ 

string numeralToRoman(int);
string textToRoman(string);
void convertFileToRoman(string, string);
bool isDigit(char);
bool doesFileExist(string);
void inputCheck(string, string);
void showUsage(string);

int main(int argc, char **argv)
{
	string input_file{""};
	string output_file{""};

	if (argc != 5)
	{
		showUsage(argv[0]);
		exit(1);
	}

	for (int i = 1; i < argc; ++i)
	{
		string arg = argv[i];
		if (arg == "-i" || arg == "--in")
		{
			if (i + 1 < argc)
				input_file = argv[i+1];
			else 
			{
				showUsage(argv[0]);
				exit(1);
			}
		}
		else if (arg == "-o" || arg == "--out")
		{
			if (i + 1 < argc)
				output_file = argv[i+1];
			else 
			{
				showUsage(argv[0]);
				exit(1);
			}
		}
		else if (arg == "-h" || arg == "--help")
		{
			showUsage(argv[0]);
			exit(1);
		}
	}

	inputCheck(input_file, output_file);
	convertFileToRoman(input_file, output_file);
}

void showUsage(string name)
{
	cout << "Usage: " << name << " -i <file> -o <file>\n"
		 << "or:    " << name << " --in <file> --out <file>\n";
}

// Check if input file and output file exists.
// [y/n] warning prompt if output file exists because the file will be overwritten
void inputCheck(string input_file, string output_file)
{
	if (!doesFileExist(input_file))
	{
		cout << "File " << input_file << " doesn't exist.\n";
		exit(1);
	}
	
	if (doesFileExist(output_file))
	{
		char yesno;
		cout << "File " << output_file << " will be overwritten."
			 << " Are you sure? [y/n]\n";
		cin >> yesno;

		if (yesno == 'y' || yesno == 'Y');
		else
		{
			cout << "File " << output_file << " won't be overwritten."
				 << " Program will exit.\n";
			exit(1);
		}
	}
	else 
	{
		cout << "File " << output_file << " doesn't exist.\n";
		exit(1);
	}
}

void convertFileToRoman(string input_file, string output_file)
{
	string output_text{""};

	string line;
	ifstream fileDigits(input_file);
	if (fileDigits.is_open())
	{
		while (getline(fileDigits, line))
		{
			output_text += textToRoman(line) + '\n';
		}
		fileDigits.close();
	}
	else
	{
		cout << "Unable to open file " << input_file << '\n';
	}

	ofstream fileRoman(output_file);
	if (fileRoman.is_open())
	{
		fileRoman << output_text;
		fileRoman.close();
	}
	else
	{
		cout << "Unable to open file " << output_file << '\n';
	}
}

bool doesFileExist(string filename)
{
	ifstream name;
	name.open(filename);
	bool fileExists = bool(name);
	name.close();
	return fileExists;
}

string textToRoman(string text)
{
	string textRoman;

	for (int i = 0; i < text.size(); i++)
	{
		if (isDigit(text[i]))
		{
			string number{""};
			while (isDigit(text[i]))
			{
				number += text[i];
				++i;
			}
			textRoman += numeralToRoman(stoi(number));
			--i;
		}
		else
		{
			textRoman += text[i];
		}
	}
	return textRoman;
}

bool isDigit(char a)
{
	return (a >= '0' && a <= '9');
}

string numeralToRoman(int number)
{
	const vector<string> romans = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
	const vector<int> numerals = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
	string roman;

	int i = 0;

	while (number > 0 && i < numerals.size())
	{
		if (number >= numerals[i])
		{
			roman += romans[i];
			number -= numerals[i];
		}
		else
		{
			i++;
		}
	}

	return roman;
}