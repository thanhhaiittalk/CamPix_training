#pragma once
#include <string>

class Mediator;

class User {
    public:
        virtual void send(const std::string& message) = 0;
        virtual void receive(const std::string& message, const std::string& from) = 0;
        virtual std::string getName() const = 0;
        virtual ~User() = default;
};