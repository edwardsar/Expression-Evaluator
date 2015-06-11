# author: Alexander Edwards
# Makefile for expression evaluator

evaluate : driver.o Parser.o ParseTable.o Evaluator.o
	g++ -std=c++11 -o Expression-Evaluator driver.o Parser.o ParseTable.o Evaluator.o -o evaluate

driver.o : Parser.hpp Parser.cpp ParseTable.hpp ParseTable.cpp Evaluator.hpp Evaluator.cpp Stack.hpp Queue.hpp HashTable.hpp HashTable.cpp List.hpp ListNode.hpp
	g++ -std=c++11 -c driver.cpp

Parser.o : Parser.hpp Parser.cpp
	g++ -std=c++11 -c Parser.cpp

ParseTable.o : ParseTable.hpp ParseTable.cpp Stack.hpp Queue.hpp
	g++ -std=c++11 -c ParseTable.cpp 

Evaluator.o : Evaluator.hpp Evaluator.cpp Stack.hpp Queue.hpp HashTable.hpp HashTable.cpp List.hpp ListNode.hpp
	g++ -std=c++11 -c Evaluator.cpp 


# ==== Testing suite ====
# Rules and recipes for building testing drivers
fullTestSuiteResults.txt: listTest.o queueTest.o stackTest.o
	cat listTest.o queueTest.o stackTest.o > fullTestSuiteResults.txt

listTest.o: List.hpp ListNode.hpp Testing_Drivers/listDriver.cpp
	g++ -std=c++11 -o listTest.o Testing_Drivers/listDriver.cpp

queueTest.o: List.hpp ListNode.hpp Queue.hpp Testing_Drivers/queueDriver.cpp
	g++ -std=c++11 -o queueTest.o Testing_Drivers/queueDriver.cpp

stackTest.o: List.hpp ListNode.hpp Stack.hpp Testing_Drivers/stackDriver.cpp
	g++ -std=c++11 -o stackTest.o Testing_Drivers/stackDriver.cpp

hashTableTest.o: HashTable.hpp Testing_Drivers/hashTableDriver.cpp
	g++ -std=c++11 -o hashTableTest.o Testing_Drivers/hashTableDriver.cpp
# ---- end of test suite ----


clean:
	rm -fv fullTestSuiteResults.txt *.o *.gch *~ evaluate 
