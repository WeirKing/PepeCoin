#include		"cryptopp700/rsa.h"
#include 		"cryptopp700/base64.h"
#include		"cryptopp700/osrng.h"
#include		"cryptopp700/files.h"
#include		"cryptopp700/hex.h"
#include		"cryptopp700/pssr.h"
#include		"cryptopp700/whrlpool.h"
#include		<string>
#include		<iostream>
#include 		<assert.h>


using namespace std;
namespace crypto{

#define KEY_SIZE 				2048
#define KEY_BLOCK_START 		"==KEY_BLOCK_START=="
#define PUBLIC_BLOCK_END 		"==PUBLIC_BLOCK_END=="
#define PRIVATE_BLOCK_END 		"==PRIVATE_BLOCK_END=="

using Signer 	= CryptoPP::RSASS<CryptoPP::PSSR, CryptoPP::Whirlpool>::Signer;
using Verifier 	= CryptoPP::RSASS<CryptoPP::PSSR, CryptoPP::Whirlpool>::Verifier;

void write_key_to_string(const CryptoPP::RSA::PrivateKey pv_key, string &pv_key_string);
void write_key_to_string(const CryptoPP::RSA::PublicKey pubKey, string &pb_key_string);
void read_key_from_string(CryptoPP::RSA::PrivateKey &privKey, const string file);
void read_key_from_string(CryptoPP::RSA::PublicKey &pubKey, const string file);
void create_key_pair(string &pubKeyBuffer, string &privKeyBuffer);
void hash_transaction(string data, string &digest);
string sign_hash(string hash, string priv_key);
bool verify_signature(string signed_hash, string hash, string public_key);



/*
 * Writes a private key to a string. Overloaded for writing public keys
 */
void write_key_to_string(const CryptoPP::RSA::PrivateKey pv_key, string &pv_key_string){
	pv_key_string = "";
	CryptoPP::HexEncoder ss(
		new CryptoPP::StringSink(pv_key_string));
	pv_key.DEREncode(ss);
}
/*
 * Writes a public key to a string. 
 */
void write_key_to_string(const CryptoPP::RSA::PublicKey pb_key, string &pb_key_string)
{
	pb_key_string = "";
	/*
	CryptoPP::StringSink ss(pb_key_string);
	*/
	CryptoPP::HexEncoder ss(
		new CryptoPP::StringSink(pb_key_string));
	pb_key.DEREncode(ss);
}

/*
 * Reads a private key from string. Overloaded for reading public keys
 */
void read_key_from_string(CryptoPP::RSA::PrivateKey &pv_key, const string pv_key_string)
{
	//CryptoPP::StringSource ss(pv_key_string, true);

	CryptoPP::StringSource ss(pv_key_string, true, 
		new CryptoPP::HexDecoder());
	pv_key.BERDecode(ss);
}
/*
 * Reads a public key from string.
 */
void read_key_from_string(CryptoPP::RSA::PublicKey &pb_key, const string pb_key_string)
{
	//CryptoPP::StringSource ss(pb_key_string, true);
	CryptoPP::StringSource ss(pb_key_string, true, 
		new CryptoPP::HexDecoder());
	pb_key.BERDecode(ss);
}

/*
 * Signs the supplied hash with the supplied private key
 * Returns the signed hash
 * TODO figure out why size inflates so much
 */
string sign_hash(string hash, string priv_key){
	CryptoPP::RSA::PrivateKey private_key;
	read_key_from_string(private_key, priv_key);
	string signature;


	CryptoPP::AutoSeededRandomPool rng;
	Signer signer(private_key);

	CryptoPP::StringSource ss(hash, true,
		new CryptoPP::SignerFilter(rng, signer,
			new CryptoPP::StringSink(signature)));

	return signature;
}

/*
 * Returns true if the supplied signed hash is the signed version of the supplied hash given the supplied public key
 * Treats all hashes as unencoded text
 */
bool verify_signature(string signed_hash, string hash, string public_key_string){
	CryptoPP::RSA::PublicKey public_key;
	read_key_from_string(public_key, public_key_string);

/*
	string decoded_signature, decoded_hash;
	CryptoPP::StringSource ss(signed_hash, true,
		new CryptoPP::HexDecoder(
			new CryptoPP::StringSink(decoded_signature)));

//Code to unencode the supplied hash
	CryptoPP::StringSource ss3(hash, true,
		new CryptoPP::HexDecoder(
			new CryptoPP::StringSink(decoded_hash)));

*/
	bool result = false;
	Verifier verifier(public_key);
	CryptoPP::StringSource ss2(signed_hash + hash, true,
		new CryptoPP::SignatureVerificationFilter(verifier,
			new CryptoPP::ArraySink((CryptoPP::byte *)&result, sizeof(result))));

	return result;

}

/*
 * Hashes the supplied data that constitutes a transaction.
 */
void hash_transaction(string data, string &digest)
{
	CryptoPP::SHA256 hash;
	CryptoPP::StringSource ss(data, true, 
		new CryptoPP::HashFilter(hash, 
			new CryptoPP::HexEncoder(
				new CryptoPP::StringSink(digest))));
}


/*
 * Creates a keypair based on the defined KEY_SIZE
 */
void generate_key_pair(string &private_key_string, string &public_key_string){
	CryptoPP::RSA::PrivateKey private_key;
	CryptoPP::AutoSeededRandomPool rng;

	private_key.GenerateRandomWithKeySize(rng, KEY_SIZE);

	CryptoPP::RSA::PublicKey public_key(private_key);

	write_key_to_string(private_key, private_key_string);
	write_key_to_string(public_key, public_key_string);
}
}

/*
 * Loads a keypair from the file into the supplied strings.
 * If the file only contains a public key then only the public key is loaded. 
 */
void load_key_pair(string &pv_key_string, string &pb_key_string, const string file){
	ifstream fs(file);
	string input;
	fs >> input;
	assert(input.compare(KEY_BLOCK_START) == 0);
	input = "";
	while (input.compare(PUBLIC_BLOCK_END) != 0){
		pb_key_string += input;
		fs >> input;
	}
	input = "";
	while (input.compare(PRIVATE_BLOCK_END) != 0){
		pv_key_string += input;
		fs >> input;
	}
	assert(input.compare(PRIVATE_BLOCK_END) == 0);
	
}

void save_key_pair(const string pv_key_string, const string pb_key_string, string file){
	ofstream fs(file);
	fs << KEY_BLOCK_START << endl;
	fs << pb_key_string << endl << PUBLIC_BLOCK_END << endl;
	fs << pv_key_string << endl << PRIVATE_BLOCK_END << endl;
}

/*
 * Returns true if the hash matches the signed hash
 */

int main(){

	string stuff;
	stuff = "this is a asdfasdfasdf    to hash";
	string hash;
	crypto::hash_transaction(stuff, hash);
	cout << stuff.c_str() << endl;
	cout << "This is the hash: " << hash << endl;

	string public_key, private_key;
	//crypto::generate_key_pair(private_key, public_key);

	load_key_pair(private_key, public_key, "test_key_pair.txt");

	cout << "private key: " << private_key << endl;
	cout << "public key: " << public_key << endl;
	string signed_hash;
	CryptoPP::RSA::PrivateKey pv_key;
	crypto::read_key_from_string(pv_key, private_key);

	signed_hash = crypto::sign_hash(hash, private_key);
	string message;
	ifstream example("example.txt");
	getline(example, message);
	string test = crypto::sign_hash(message, private_key);
	cout << "signed hash: " << signed_hash << endl;

	cout << "size of signed: " << signed_hash.length() << endl;
	cout << "size of hash: " << hash.length() << endl;
	cout << "size of test: " << message.length() << " size of signed stuff: " << test.length() << endl;
	if (crypto::verify_signature(signed_hash, hash, public_key)){
		cout << "they match!" << endl;
	} else {
		cout << "they don't match!" << endl;
	}

	return 0;
}	