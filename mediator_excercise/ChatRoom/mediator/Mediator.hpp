#pragma once
#include <string>
#include <memory>
#include <vector>

class User; // forwared declaration

class Mediator {
    public:
        virtual void broadcast (const std::string& message, std::shared_ptr<User> sender) = 0;
        virtual void registerUser(std::shared_ptr<User> user) = 0;
        virtual ~Mediator() = default;
};
