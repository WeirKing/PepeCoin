all: miner server
miner: src/temple_miner.cc src/temple_miner.util src/temple_miner.h src/temple_client.cc
	c++ src/temple_miner.cc -o miner -l cryptopp -I./
server: src/temple_test_server.cc src/temple_miner.util src/temple_miner.h
	c++ src/temple_test_server.cc -o server -l cryptopp -I./
crypto: crypto_test.cpp src/temple_miner.h src/temple_miner.util src/crypto.util
	c++ crypto_test.cpp -o crypto -l cryptopp -I./