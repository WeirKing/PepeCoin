all: miner server
miner: pepe_miner.cc pepe_miner.util pepe_miner.h pepe_client.cc
	c++ pepe_miner.cc -o miner
server: pepe_test_server.cc pepe_miner.util pepe_miner.h
	c++ pepe_test_server.cc -o server