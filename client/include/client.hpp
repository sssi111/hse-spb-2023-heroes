#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <all_protos/demo.grpc.pb.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <memory>

class Client final {
public:
    Client(const std::shared_ptr<grpc::Channel> &channel)
        : stub(namespace_proto::Server::NewStub(channel)) {
    }

    Client(const Client &) = delete;
    Client &operator=(const Client &) = delete;
    Client(Client &&) = delete;
    Client &operator=(Client &&) = delete;

private:
    std::unique_ptr<namespace_proto::Server::Stub> stub;

public:
    const std::unique_ptr<namespace_proto::Server::Stub> &getStub() const {
        return stub;
    }

    //    void SendOk(google::protobuf::Empty){
    //
    //    }

private:
    grpc::CompletionQueue client_queue;
};

#endif  // CLIENT_HPP
