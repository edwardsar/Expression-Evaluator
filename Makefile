# author: Alexander Edwards
# Makefile for expression evaluator


# ==== Testing suite ====
# Rules and recipes for building testing drivers
fullTestSuiteResults.txt: listTest.o queueTest.o stackTest.o
	cat listTest.o queueTest.o stackTest.o > fullTestSuiteResults.txt

listTest.o: List.hpp ListNode.hpp Testing_Drivers/listDriver.cpp
	g++ -std=c++11 -o listTest.o Testing_Drivers/listDriver.cpp

queueTest.o: List.hpp ListNode.hpp Queue.hpp Testing_Drivers/queueDriver.cpp
	g++ -std=c++11 -o queueTest.o Testing_Drivers/queueDriver.cpp

stackTest.o: List.hpp ListNode.hpp Stack.hpp Testing_Drivers/stackDriver.cpp
	g++ -std=c++11 -o stackTest.o Testing_Drivers/queueDriver.cpp
# ---- end of test suite ----


clean:
	rm -fv fullTestSuiteResults.txt listTest.o queueTest.o stackTest.o
