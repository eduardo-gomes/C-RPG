#pragma once
#include "cryptlib.h"
#include "sha.h"
#include "hex.h"
#include "files.h"
#include <iostream>
//#include <sstream>

std::string generate_hash(std::string &msg){//VULNERABLE TO BRUTEFORCE NEED TO SALT
	using namespace CryptoPP;
	//HexEncoder encoder(new FileSink(std::cout));
	std::string digest;
	#ifdef HASH_SIZE_512
	SHA512 hash;
	#else
	SHA256 hash;
	#endif
	hash.Update((const unsigned char *)msg.data(), msg.size());
	digest.resize(hash.DigestSize());
	hash.Final((unsigned char *)&digest[0]);
	/*std::cout << "Message: " << msg << std::endl;
	std::cout << "Digest: " << hash_to_char(digest) << std::endl;
	//StringSource(digest, true, new Redirector(encoder));
	std::cout << std::endl;*/
	return digest;
}
