#include <future>
#include "client.hpp"
#include "game.hpp"
#include "menu.hpp"

int main() {
    menu_view::Menu main_menu{};
    while (!main_menu.get_window()->is_done()) {
        main_menu.update();
        main_menu.render();
    }
    const std::shared_ptr<::grpc::ChannelInterface> &channel =
        grpc::CreateChannel(
            "localhost:50051", grpc::InsecureChannelCredentials()
        );
    get_client_state()->m_stub =
        std::make_unique<namespace_proto::Server::Stub>(channel);
    namespace_proto::UserState user;
    user.mutable_user()->set_id(-1);
    //    get_client_state()->m_user = user;
    int type;
    std::cout << "select type 0 - for login / 1 - for sign up .....  ";
    std::cin >> type;
    if (type == 0){
        std::cout << "LogIn: enter your name and password:\n";
        std::string name, password;
        while (user.user().id() == -1) {
            std::cin >> name >> password;
            namespace_proto::LogInData request;
            request.set_name(name);
            request.set_password(password);
            grpc::ClientContext context{};
            get_client_state()->m_stub->LogIn(
                &context, request, user.mutable_user()
            );
            if (user.user().id() == -1){
                std::cout << "try again\n";
            }
        }
    }
    else{
        std::cout << "SignUp: enter your name and password:\n";
        std::string name, password;
        while (user.user().id() == -1) {
            std::cin >> name >> password;
            namespace_proto::LogInData request;
            request.set_name(name);
            request.set_password(password);
            grpc::ClientContext context{};
            get_client_state()->m_stub->SignUp(
                &context, request, user.mutable_user()
            );
            if (user.user().id() == -1){
                std::cout << "try again\n";
            }
        }
    }
    std::cout << user.user().id() << '\n';
    get_client_state()->m_user = user;
    std::thread receiver(&Client::run_receiver);
    while (!game_view::get_game_state()->get_window()->is_done()) {
        {
            std::unique_lock lock{get_client_state()->m_mutex};
            game_view::get_game_state()->update();
        }
        game_view::get_game_state()->render();
    }
    receiver.join();
    return 0;
}