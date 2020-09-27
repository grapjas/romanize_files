#include "std_lib_facilities.h"

// https://www.cprogramming.com/tutorial/lesson14.html
// http://www.cplusplus.com/doc/tutorial/files/

string numeralToRoman(int);
string textToRoman(string);
void convertFileToRoman(string, string);
bool isDigit(char);
bool doesFileExist(string);

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

	if (!doesFileExist(input_file))
	{
		cout << "File " << input_file << " doesn't exit.\n";
		exit(1);
	}

	if (doesFileExist(output_file))
	{
		char yn;
		cout << "File " << output_file << " will be overwritten."
			 << " Are you sure? (y/n)\n";
		cin >> yn;
		if (yn == 'n' || yn == 'N')
		{
			cout << "Program will stop.\n";
			exit(1);
		}
	}

	convertFileToRoman(input_file, output_file);
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
	string roman {""};
	while (number > 0)
	{
		if (number >= 1000)
		{
			roman += "M";
			number -= 1000;
		}
		else if (number >= 900)
		{
			roman += "CM";
			number -= 900;
		}
		else if (number >= 500)
		{
			roman += "D";
			number -= 500;
		}
		else if (number >= 400)
		{
			roman += "CD";
			number -= 400;
		}
		else if (number >= 100)
		{
			roman += "C";
			number -= 100;
		}
		else if (number >= 90)
		{
			roman += "XC";
			number -= 90;
		}
		else if (number >= 50)
		{
			roman += "L";
			number -= 50;
		}
		else if (number >= 40)
		{
			roman += "XL";
			number -= 40;
		}
		else if (number >= 10)
		{
			roman += "X";
			number -= 10;
		}
		else if (number >= 9)
		{
			roman += "IX";
			number -= 9;
		}
		else if (number >= 5)
		{
			roman += "V";
			number -= 5;
		}
		else if (number >= 4)
		{
			roman += "IV";
			number -= 4;
		}
		else if (number >= 1)
		{
			roman += "I";
			number -= 1;
		}
	}
	return roman;
}