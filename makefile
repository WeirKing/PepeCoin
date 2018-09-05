all: miner server
miner: pepe_miner.cc pepe_miner.util pepe_miner.h pepe_client.cc
	c++ pepe_miner.cc -o miner -l cryptopp
server: pepe_test_server.cc pepe_miner.util pepe_miner.h
	c++ pepe_test_server.cc -o server -l cryptopp
crypto: crypto_test.cpp pepe_miner.h pepe_miner.util crypto.util
	c++ crypto_test.cpp -o crypto -l cryptopp