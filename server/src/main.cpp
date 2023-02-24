#include <all_protos/demo.grpc.pb.h>
#include <all_protos/demo_client.pb.h>
#include <grpc/grpc.h>
#include <grpcpp/server_builder.h>
#include <iostream>

class DemoMessage final : public ::demo_name::ClientToServer::Service {
public:
    ::grpc::Status SendOk(
        ::grpc::ServerContext *context,
        const ::demo_name::GetOk *request,
        ::demo_name::Ok *response
    ) override {
        std::cout << "server woke up" << std::endl;
        response->set_ok(true);
        return grpc::Status::OK;
    }
};

int main(int argc, char *argv[]) {
    grpc::ServerBuilder builder;
    builder.AddListeningPort(
        "0.0.0.0:50051", grpc::InsecureServerCredentials()
    );
    DemoMessage send_message;
    builder.RegisterService(&send_message);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    server->Wait();

    return 0;
}
