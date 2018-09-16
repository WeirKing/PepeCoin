all: miner server
miner: src/pepe_miner.cc src/pepe_miner.util src/pepe_miner.h src/pepe_client.cc
	c++ src/pepe_miner.cc -o miner -l cryptopp -I./
server: src/pepe_test_server.cc src/pepe_miner.util src/pepe_miner.h
	c++ src/pepe_test_server.cc -o server -l cryptopp -I./
crypto: crypto_test.cpp src/pepe_miner.h src/pepe_miner.util src/crypto.util
	c++ crypto_test.cpp -o crypto -l cryptopp -I./