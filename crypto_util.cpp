#include		"cryptopp700/rsa.h"
#include 		"cryptopp700/base64.h"
#include		"cryptopp700/osrng.h"
#include		"cryptopp700/files.h"
#include		"cryptopp700/hex.h"
#include		<string>
#include		<iostream>
#include		"transaction.h"

using namespace std;
namespace crypto{

void write_key_to_string(CryptoPP::InvertibleRSAFunction privKey, string file);
void write_key_to_string(CryptoPP::RSAFunction pubKey, string file);
void read_key_from_string(CryptoPP::InvertibleRSAFunction &privKey, string file);
void read_key_from_string(CryptoPP::RSAFunction &pubKey, string file);
void hash_transaction(string public_key, string prev_hash, string signed_hash, string &digest);
void sign_hash(string hash, string priv_key, string &buffer);
bool verify_signature(string signed_hash, string hash, string public_key);



/*
 * Writes a private key to a file. Overloaded for writing public keys
 */
void write_key_to_string(CryptoPP::InvertibleRSAFunction privKey, string &file){
	CryptoPP::AutoSeededRandomPool rng;
	CryptoPP::Base64Encoder privKeySink(new CryptoPP::StringSink(file));
	privKey.DEREncode(privKeySink);
	privKeySink.MessageEnd();
}
/*
 * Writes a public key to a file. 
 */
void write_key_to_string(CryptoPP::RSAFunction pubKey, string &file)
{
	CryptoPP::AutoSeededRandomPool rng;
	CryptoPP::Base64Encoder pubKeySink(new CryptoPP::StringSink(file));
	pubKey.DEREncode(pubKeySink);
	pubKeySink.MessageEnd();
}

/*
 * Reads a private key from file. Overloaded for reading public keys
 */
void read_key_from_file(CryptoPP::InvertibleRSAFunction &privKey, string &file)
{
	CryptoPP::ByteQueue bytes;
	CryptoPP::StringSource fyle(file, true, new CryptoPP::Base64Decoder);
	fyle.TransferTo(bytes);
	bytes.MessageEnd();
	privKey.Load(bytes);
}
/*
 * Reads a public key from file.
 */
void read_key_from_file(CryptoPP::RSAFunction &pubKey, string &file)
{
	CryptoPP::ByteQueue bytes;
	CryptoPP::StringSource fyle(file, true, new CryptoPP::Base64Decoder);
	fyle.TransferTo(bytes);
	bytes.MessageEnd();
	pubKey.Load(bytes);
}
/*
 * Signs the supplied hash with the supplied private key
 * Returns the hash in buffer
 */
void sign_hash(string hash, string priv_key, string &buffer)
{
	CryptoPP::InvertibleRSAFunction privKey;
	read_key_from_string(privKey, priv_key);
	CryptoPP::AutoSeededRandomPool rng;
	CryptoPP::RSASSA_PKCS1v15_SHA_Signer privSign(privKey);
	string lmao;

	CryptoPP::byte *signature;
	privSign.SignMessage(rng, (const CryptoPP::byte *)hash.data(), sizeof hash, &signature);

}

/*
 * Hashes the supplied data that constitutes a transaction.
 */
void hash_transaction(string public_key, string prev_hash, string signed_hash, string &digest)
{
	CryptoPP::SHA256 hash;
	hash.Update((const CryptoPP::byte *)public_key.data(), sizeof public_key.data());
	hash.Update((const CryptoPP::byte *)prev_hash.data(), sizeof prev_hash.data());
	hash.Update((const CryptoPP::byte *)signed_hash.data(), sizeof signed_hash.data());
	CryptoPP::byte digest_intermediary[CryptoPP::SHA256::DIGESTSIZE];

	CryptoPP::HexEncoder encoder;
	encoder.Attach(new CryptoPP::StringSink(digest));
	encoder.Put(digest_intermediary, sizeof digest_intermediary);
	encoder.MessageEnd();
}

/*
 * Returns true if the hash matches the signed hash
 */
bool verify_signature(string signed_hash, string hash, string public_key)
{
	return false;
}
int main(){

	CryptoPP::SHA256 hash;
	CryptoPP::InvertibleRSAFunction privKey;
	CryptoPP::AutoSeededRandomPool rng;


	privKey.Initialize(rng, 1024);




	string asdf = "asdfasdfdSF";
	CryptoPP::byte digest[CryptoPP::SHA256::DIGESTSIZE];

	hash.CalculateDigest(digest, (const CryptoPP::byte *)&asdf, sizeof asdf);
}
}