find_package(protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(Threads)

set(PROTO_FILES
        all_protos/demo.proto
        all_protos/demo_client.proto
        )


add_library(all_protos ${PROTO_FILES})
target_link_libraries(all_protos
        protobuf::libprotobuf
        gRPC::grpc
        gRPC::grpc++
        )
target_include_directories(all_protos PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)
protobuf_generate(TARGET all_protos LANGUAGE cpp)
protobuf_generate(TARGET all_protos LANGUAGE grpc GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}")
