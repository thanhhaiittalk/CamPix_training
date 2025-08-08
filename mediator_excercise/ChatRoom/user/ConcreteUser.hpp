#pragma once
#include "User.hpp"
#include "Mediator.hpp"
#include <vector>
#include <iostream>

class ConcreteUser : public User, public std::enable_shared_from_this<ConcreteUser> {
private:
    std::string name;
    std::shared_ptr<Mediator> mediator;
public:
    void send(const std::string& message) override;
    void receive(const std::string& message, const std::string& from) override;
    ConcreteUser(const std::string& name, std::shared_ptr<Mediator> med);
    std::string getName() const;
};

