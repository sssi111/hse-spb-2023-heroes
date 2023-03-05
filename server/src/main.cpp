#include <thread>
#include "server.hpp"

int main(int argc, char *argv[]) {
    ServerServices services;
    Server s("0.0.0.0:50051", &services, 2);

    std::thread server = std::thread(s.start());
    return 0;
}
