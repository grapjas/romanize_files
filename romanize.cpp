#include "std_lib_facilities.h"

// https://www.cprogramming.com/tutorial/lesson14.html
// http://www.cplusplus.com/doc/tutorial/files/

string numeralToRoman(int);
string textToRoman(string);
void convertFileToRoman(string, string);
bool isDigit(char);
bool doesFileExist(string);
void inputCheck(string, string);

int main(int argc, char **argv)
{
	string input_file {""};
	string output_file {""};

	if (argc != 3)
	{
		cout << "usage: " << argv[0] << " <inputfile> <outputfile>\n";
		exit(1);
	}
	else 
	{
		input_file = argv[1];
		output_file = argv[2];
	}

	inputCheck(input_file, output_file);
	convertFileToRoman(input_file, output_file);
}

void inputCheck(string input_file, string output_file)
{
	if (!doesFileExist(input_file))
	{
		cout << "File " << input_file << " doesn't exit.\n";
		exit(1);
	}

	if (doesFileExist(output_file))
	{
		char yesno;
		cout << "File " << output_file << " will be overwritten."
			 << " Are you sure? (y/n)\n";
		cin >> yesno;
		if (yesno == 'y' || yesno == 'Y')
			;
		else 
		{
			cout << "Program will stop, you didn't enter y.\n";
			exit(1);
		}
	}
}

void convertFileToRoman(string input_file, string output_file)
{
	string output_text {""};

	string line;
	ifstream fileDigits (input_file);
	if (fileDigits.is_open())
	{
		while (getline (fileDigits, line))
		{
			output_text += textToRoman(line) + '\n';
		}
		fileDigits.close();
	}
	else 
	{
		cout << "Unable to open file " << input_file << '\n';
	}

	ofstream fileRoman (output_file);
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
	if (name)
		return true;
	else 
		return false;
}

string textToRoman(string text)
{
	string textRoman;

	for (int i = 0; i < text.size(); i++)
	{
		if (isDigit(text[i]))
		{
			string number {""};
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
	const vector <string> romans = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
	const vector <int> numerals = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
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