#Build Setup

# Compile Producer
g++ -std=c++17 producer.cpp -o producer -lredis++ -lhiredis -lpthread

# Compile Consumer
g++ -std=c++17 consumer.cpp -o consumer -lredis++ -lhiredis -lpthread