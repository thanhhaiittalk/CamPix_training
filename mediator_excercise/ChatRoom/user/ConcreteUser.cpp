#include "ConcreteUser.hpp"

// Constructor
ConcreteUser::ConcreteUser(const std::string& name, std::shared_ptr<Mediator> med)
    : name(name), mediator(med) {}

// Empty send method
void ConcreteUser::send(const std::string& message) {
    std::cout << "[" << name << "] sends: " << message << std::endl;
    mediator->broadcast(message, shared_from_this());
}

// Empty receive method
void ConcreteUser::receive(const std::string& message, const std::string& from) {
    std::cout << "[" << name << "]" << " received: " <<message <<" [from "<< from <<"]"<< std::endl;
}

// Empty getName method
std::string ConcreteUser::getName() const {
    return name; // return empty string for now
}