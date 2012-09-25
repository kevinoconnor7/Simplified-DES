#include <string.h>
#include <cmath>
#include <iostream>
#include "des.h"

//Build the keys based on given key
void DES::buildKeys()
{
	std::string working_key = this->key;

	if(working_key.size() != 10)
	{
		return;
	}

	//Being with permutation 10 on this key
	working_key = this->P10(working_key);

	//Split the key and shift
	std::string working_key_left = this->leftShift(this->left(working_key));
	std::string working_key_right = this->leftShift(this->right(working_key));

	//Make subkey 0 with permuatation 8
	this->keys[0] = this->P8(working_key_left + working_key_right);

	//Left shift the parts again but by 2 bits
	working_key_left = this->leftShift(working_key_left);
	working_key_right = this->leftShift(working_key_right);
	working_key_left = this->leftShift(working_key_left);
	working_key_right = this->leftShift(working_key_right);

	//Generate subkey 1 with permutation 8
	this->keys[1] = this->P8(working_key_left + working_key_right);
}

//Map input to Initial Permutation table
std::string DES::IP(std::string input)
{
	unsigned int IP_table[8] = {2,6,3,1,4,8,5,7};
	std::string output("");

	for(unsigned int i = 0; i < 8; ++i)
	{
		output += input[ IP_table[i]-1 ];
	}

	return output;
}

//Map input to Inverse Initial Permutation table
std::string DES::inverseIP(std::string input)
{
	unsigned int IIP_table[8] = {4,1,3,5,7,2,8,6};
	std::string output("");

	for(unsigned int i = 0; i < 8; ++i)
	{
		output += input[ IIP_table[i]-1 ];
	}

	return output;
}

//Map input to Permutation 10 table
std::string DES::P10(std::string input)
{
	unsigned int P10_table[10] = {3,5,2,7,4,10,1,9,8,6};
	std::string output = "";

	for(unsigned int i = 0; i < 10; ++i)
	{
		output += input[ P10_table[i]-1 ];
	}

	return output;
}

//Map input to Permutation 8 table
std::string DES::P8(std::string input)
{
	unsigned int P8_table[8] = {6,3,7,4,8,5,10,9};
	std::string output("");

	for(unsigned int i = 0; i < 8; ++i)
	{
		output += input[ P8_table[i]-1 ];
	}

	return output;
}

//Map input to Permutation 4 table
std::string DES::P4(std::string input)
{
	unsigned int P4_table[4] = {2,4,3,1};
	std::string output("");

	for(unsigned int i = 0; i < 4; ++i)
	{
		output += input[ P4_table[i]-1 ];
	}

	return output;
}

//Cyclic left shift
std::string DES::leftShift(std::string input)
{
	std::string output("");

	if(input.size() == 0)
	{
		return output;
	}

	//Move everything to the left except for first element
	for(unsigned int i = 1; i < input.size(); ++i)
	{
		output += input[i];
	}

	//Add first element to end of output
	output += input[0];

	return output;
}

//Binary XOR for binary strings
std::string DES::XOR(std::string input, std::string key)
{
	std::string output("");

	if(input.size() != key.size())
	{
		return output;
	}
	
	//Walk through and XOR every char
	for(unsigned int i = 0; i < input.size(); ++i)
	{
		output += (input[i]^key[i]) ? "1" : "0";
	}

	return output;
}

std::string DES::fBox(std::string input, int round)
{
	//Expand the input from 4-bits to 8-bits with the ebox
	input = eBox(input);

	//XOR the input with the key for this round
	input = XOR(input, this->keys[round]);

	//Left half goes to sBox 0
	std::string i_left = left(input);
	i_left = sBox(i_left, 0);

	//Right half goes to sBox 1
	std::string i_right = right(input);
	i_right = sBox(i_right, 1);

	std::string output = i_left + i_right;
	output = P4(output);

	return output;
}

std::string DES::sBox(std::string input, unsigned short int s_box)
{
	std::string output("");

	if(input.size() != 4)
	{
		return output;
	}

	//Create the box
	std::vector< std::vector<std::string> > box;

	//Sbox 0 definition
	if(s_box == 0)
	{
		//Fill the box
		std::vector<std::string> row;

		row.push_back("01");
		row.push_back("00");
		row.push_back("11");
		row.push_back("10");
		box.push_back(row);

		row.clear();
		row.push_back("11");
		row.push_back("10");
		row.push_back("01");
		row.push_back("00");
		box.push_back(row);

		row.clear();
		row.push_back("00");
		row.push_back("10");
		row.push_back("01");
		row.push_back("11");
		box.push_back(row);

		row.clear();
		row.push_back("11");
		row.push_back("01");
		row.push_back("11");
		row.push_back("10");
		box.push_back(row);
	} else if(s_box == 1) {
		//Sbox 1 definition
		//Fill the box
		std::vector<std::string> row;

		row.push_back("00");
		row.push_back("01");
		row.push_back("10");
		row.push_back("11");
		box.push_back(row);

		row.clear();
		row.push_back("10");
		row.push_back("00");
		row.push_back("01");
		row.push_back("11");
		box.push_back(row);

		row.clear();
		row.push_back("11");
		row.push_back("00");
		row.push_back("01");
		row.push_back("00");
		box.push_back(row);

		row.clear();
		row.push_back("10");
		row.push_back("01");
		row.push_back("00");
		row.push_back("10");
		box.push_back(row);
	} else {
		return output;
	}

	//Use Bit-2 and Bit-3 for column
	std::string col_bin("");
	col_bin += input[1];
	col_bin += input[2];
	int col = BinToDec(col_bin);

	//Use Bit-1 and Bit-4 for row
	std::string row_bin("");
	row_bin += input[0];
	row_bin += input[3];
	int row = BinToDec(row_bin);

	//Return the desired element from the sbox
	return box[row][col];
}

//Map an input with the eBox table and return the result
//Will expand a 4-bit string to 8-bits
std::string DES::eBox(std::string input)
{
	unsigned int ebox_table[8] = {4,1,2,3,2,3,4,1};
	std::string output("");

	for(unsigned int i = 0; i < 8; ++i)
	{
		output += input[ ebox_table[i]-1 ];
	}

	return output;
}

//Split the string and return the left half
std::string DES::left(std::string input)
{
	std::string output("");
	if(input.size() == 0)
	{
		return output;
	}

	for(unsigned int i = 0; i < input.size()/2; ++i)
	{
		output += input[i];
	}

	return output;
}

//Split the string and return right half
std::string DES::right(std::string input)
{
	std::string output("");
	if(input.size() == 0)
	{
		return output;
	}

	for(unsigned int i = floor(input.size()/2); i < input.size(); ++i)
	{
		output += input[i];
	}

	return output;
}

std::string DES::encrypt()
{
	std::string output("");

	if(key.size() != 10 || plain.size() != 8)
	{
		return output;
	}

	std::string l_working, r_working, temp;
	std::string working = plain;

	//Do initial permutation
	working = IP(working);

	//Split left and right half
	l_working = left(working);
	r_working = right(working);

	//Apply XOR of left half and fBox of right half
	l_working = XOR(l_working, fBox(r_working, 0));

	//Swap sides
	temp = l_working;
	l_working = r_working;
	r_working = temp;

	//Apply XOR of left half and fBox of right half
	l_working = XOR(l_working, fBox(r_working, 1));	

	//Do inverse initial permutation to get output
	working = l_working + r_working;
	output = this->cipher = inverseIP(working);

	return output;
}

std::string DES::decrypt()
{
	std::string output("");

	if(key.size() != 10 || cipher.size() != 8)
	{
		return output;
	}

	std::string l_working, r_working, temp;
	std::string working = this->cipher;

	//Do initial permutation
	working = IP(working);

	//Split left and right half
	l_working = left(working);
	r_working = right(working);


	//Apply XOR of left half and fBox of right half
	l_working = XOR(l_working, fBox(r_working, 1));

	//Swap sides
	temp = l_working;
	l_working = r_working;
	r_working = temp;

	//Apply XOR of left half and fBox of right half
	l_working = XOR(l_working, fBox(r_working, 0));	

	//Do inverse initial permutation to get output
	working = l_working + r_working;
	output = this->plain = inverseIP(working);

	return output;
}

bool DES::set_key(std::string key)
{
	if(!validateBinary(key))
	{
		std::cerr << "ERROR: Given key is not a valid binary string" << std::endl;
		return false;
	}
	if(key.size() != 10)
	{
		std::cerr << "ERROR: Given key is not 10 bits" << std::endl;
		return false;
	}
	this->key = key;
	this->buildKeys();
	return true;
}
bool DES::set_plain(std::string plain)
{ 
	if(!validateBinary(plain))
	{
		std::cerr << "ERROR: Given plaintext is not a valid binary string" << std::endl;
		return false;
	}
	if(plain.size() != 8)
	{
		std::cerr << "ERROR: Given plaintext is not 8 bits" << std::endl;
		return false;
	}
	this->plain = plain; 
	return true;
}
bool DES::set_cipher(std::string cipher)
{ 
	if(!validateBinary(key))
	{
		std::cerr << "ERROR: Given ciphertext is not a valid binary string" << std::endl;
		return false;
	}
	if(cipher.size() != 8)
	{
		std::cerr << "ERROR: Given ciphertext is not 8 bits" << std::endl;
		return false;
	}
	this->cipher = cipher;
	return true;
}


//Convert a decimal int to binary string
std::string DecToBin(int input)
{
    if ( input == 0 ) return "0";
    if ( input == 1 ) return "1";

    if ( input % 2 == 0 )
        return DecToBin(input / 2) + "0";
    else
        return DecToBin(input / 2) + "1";
}

//Convery binary string to decimal int
int BinToDec(std::string input)
{
    int result = 0, pow = 1;
    for ( int i = input.length() - 1; i >= 0; --i, pow <<= 1 )
        result += (input[i] - '0') * pow;

    return result;
}


//Check to make sure a string is a binary string
bool validateBinary(std::string input)
{
	if(input.size() == 0)
	{
		return false;
	}

	for(unsigned int i = 0; i < input.size(); ++i)
	{
		if(input[i] != '0' && input[i] != '1')
		{
			return false;
		}
	}

	return true;
}