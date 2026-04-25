#include <sw/redis++/redis++.h>
#include <iostream>
#include <unordered_map>

using namespace sw::redis;

int main() {
    try 
    {
        sw::redis::ConnectionOptions opts;
        opts.host = ""; 
        opts.port = 0;                                        
        opts.password = "";                   
        opts.user = "";                                      

        auto redis = Redis(opts);

        std::string stream_name = "sensor_stream";

        for(int i = 0; i < 5; i++) {
            std::unordered_map<std::string, std::string> data = {
                {"sensor_id", "A1"},
                {"value", "24.5"}
            };

            auto id = redis.xadd(stream_name, "*" , data.begin(), data.end());
            std::cout << "Stream data added with Id:" << id << std::endl;
        }
    }
    catch(const Error er) {
        std::cerr << "Error: " << er.what() << std::endl;
    }
}