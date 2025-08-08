#include "ChatRoomMediator.hpp"
#include "User.hpp"

void ChatRoomMediator::broadcast(const std::string& message, std::shared_ptr<User> sender){
    for (const auto& user : users) {
        if (user != sender) {
            user->receive(message,sender->getName());    
        }
    }
}

void ChatRoomMediator::registerUser(std::shared_ptr<User> user){
    users.push_back(user);
}