#include <iostream>
#include <unistd.h> // getpid()
#include <sys/types.h> //pid_t

pid_t get_my_pid();

int main(void) {
  std::cout << "Die PID dieses Prozesses: "  << get_my_pid() << " \n" << std::endl;
}



pid_t get_my_pid() {
  return getpid();
}