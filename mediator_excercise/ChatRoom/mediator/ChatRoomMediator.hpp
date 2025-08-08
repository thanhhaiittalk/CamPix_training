#pragma once
#include "Mediator.hpp"
#include <vector>

class ChatRoomMediator : public Mediator {
    private: 
        std::vector<std::shared_ptr<User>> users;
    public:
        void broadcast (const std::string& message, std::shared_ptr<User> sender) override;
        void registerUser(std::shared_ptr<User> user) override;
};