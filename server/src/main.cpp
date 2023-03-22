#include <thread>
#include "../network/include/server.hpp"

int main(int argc, char *argv[]) {
    ServerServices service;
    std::string address = "0.0.0.0:50051";
    std::thread t(&RunServer, address, &service);
    t.join();
    return 0;
}
