#ifndef des_h
#define des_h

#include <string>
#include <vector>

class DES
{
public:
	bool set_key(std::string key);
	bool set_plain(std::string plain);
	bool set_cipher(std::string cipher);
	std::string encrypt();
	std::string decrypt();
private:
	void buildKeys();
	std::string P10(std::string input);
	std::string P8(std::string input);
	std::string P4(std::string input);
	std::string IP(std::string input);
	std::string inverseIP(std::string input);
	std::string leftShift(std::string input);
	std::string XOR(std::string input, std::string key);
	std::string left(std::string input);
	std::string right(std::string input);
	std::string eBox(std::string input);
	std::string sBox(std::string input, unsigned short int box);
	std::string fBox(std::string input, int round);

	std::string key, plain,cipher;
	std::string keys[2];
};

std::string DecToBin(int input);
int BinToDec(std::string input);

bool validateBinary(std::string input);

#endif