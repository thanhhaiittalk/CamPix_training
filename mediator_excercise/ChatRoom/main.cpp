#include "ChatRoomMediator.hpp"
#include "ConcreteUser.hpp"
#include <memory>

int main () {
    std::shared_ptr<Mediator> chatRoom = std::make_shared<ChatRoomMediator>();

    // Create users and register them
    std::shared_ptr<User> alice = std::make_shared<ConcreteUser>("Alice", chatRoom);
    std::shared_ptr<User> bob   = std::make_shared<ConcreteUser>("Bob", chatRoom);
    std::shared_ptr<User> charlie = std::make_shared<ConcreteUser>("Charlie", chatRoom);

    chatRoom->registerUser(alice);
    chatRoom->registerUser(bob);
    chatRoom->registerUser(charlie);

    alice->send("Hello everyone!");
    bob->send("Hi Alice!");

    return 0;
}