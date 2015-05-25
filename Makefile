# author: Alexander Edwards
# Makefile for expression evaluator


# ==== Testing suite ====
# Rules and recipes for building testing drivers
fullTestSuite: listTest queueTest stackTest
	cat listTest queueTest stackTest > fullTestSuite

listTest: List.h Testing_Drivers/listDriver.cpp
	g++ -std=c++11 -o listTest Testing_Drivers/listDriver.cpp

queueTest: List.h Testing_Drivers/queueDriver.cpp
	g++ -std=c++11 -o queueTest Testing_Drivers/queueDriver.cpp

stackTest: List.h Testing_Drivers/stackDriver.cpp
	g++ -std=c++11 -o stackTest Testing_Drivers/queueDriver.cpp
# ---- end of test suite ----


clean:
	rm -fv fullTestSuite listTest queueTest stackTest
