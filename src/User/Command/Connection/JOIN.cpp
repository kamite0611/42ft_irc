#include "irc.hpp"
#include <iostream>

void JOIN(irc::Command *command)
{
  std::cout << "Hello join!" << std::endl;
  std::cout << "parameters: " << command->getParameter().size() << std::endl;
}
