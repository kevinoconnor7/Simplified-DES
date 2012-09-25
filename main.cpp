#include <string>
#include <iostream>
#include "des.h"

void help();

int main(int argc, char *argv[])
{
	DES des = DES();

	if(argc != 4)
	{
		std::cerr << "Not enough parameters." << std::endl;
		help();
		return 0;
	}

	std::string method = argv[1]; 
	std::string cipher_plain = argv[2];
	std::string key = argv[3];

	if(method == "encrypt")
	{
		if(!des.set_key(key))
		{
			help();
			return 0;
		}
		if(!des.set_plain(cipher_plain))
		{
			help();
			return 0;
		}
		std::cout << "Plaintext:\t" << cipher_plain << "\n\rKey:\t\t" << key << "\n\rCiphertext:\t";
		std::cout << des.encrypt() << std::endl;
	} else if(method == "decrypt") {
		if(!des.set_key(key))
		{
			help();
			return 0;
		}
		if(!des.set_cipher(cipher_plain))
		{
			help();
			return 0;
		}
		std::cout << "Ciphertext:\t" << cipher_plain << "\n\rKey:\t\t" << key << "\n\rPlaintext:\t";
		std::cout << des.encrypt() << std::endl;
	} else {
		std::cerr << "Invalid mode!" << std::endl;
		help();
		return 0;
	}

	//des.set_key("1011011011");
	//des.set_plain("10101010");
	//std::cout << des.encrypt() << std::endl;
	//std::cout << des.decrypt() << std::endl;
}

void help()
{
	std::cout << "S-DES Usage:\n\rsdes <encrypt|decrypt> <plaintext|ciphertext> <key>" << std::endl;
}