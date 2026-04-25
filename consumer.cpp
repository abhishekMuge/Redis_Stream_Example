#include <sw/redis++/redis++.h>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace sw::redis;

int main() {
    try {
        sw::redis::ConnectionOptions opts;
        opts.host = ""; 
        opts.port = 0;                                        
        opts.password = "";                   
        opts.user = "";                                    

        auto redis = Redis(opts);

        std::string stream = "sensor_stream";
        std::string group = "processing_group";
        std::string consumer = "worker_1";

        // Create the group (ignores error if already exists)
        try {
            redis.xgroup_create(stream, group, "$");
        } catch (const ReplyError &err) {}

        std::cout << "Worker listening (Type-Agnostic Mode)..." << std::endl;

        while (true) {
            // We define the result container using standard types.
            // The library's xreadgroup will fill this map:
            // Key: Stream Name
            // Value: A collection of messages
            std::unordered_map<std::string, std::vector<std::pair<std::string, std::vector<std::pair<std::string, std::string>>>>> results;

            // XREADGROUP
            // Note: We use the block duration (milliseconds) as the 4th argument
            redis.xreadgroup(group, consumer, stream, ">", 1, std::inserter(results, results.end()));

            for (auto const& stream_entry : results) {
                // messages is a vector of pairs: {ID, {Field-Value-Pairs}}
                auto const& messages = stream_entry.second;

                for (auto const& msg : messages) {
                    std::string msg_id = msg.first;
                    auto const& fields = msg.second;

                    std::cout << "\n[Message Received] ID: " << msg_id << std::endl;

                    for (auto const& field_pair : fields) {
                        std::cout << "  " << field_pair.first << ": " << field_pair.second << std::endl;
                    }

                    // Acknowledge the message
                    redis.xack(stream, group, msg_id);
                    std::cout << "Acknowledged: " << msg_id << std::endl;
                }
            }
        }
    } catch (const Error &e) {
        std::cerr << "Redis Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}