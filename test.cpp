#include <iostream>
#include <unistd.h>

int main(void) {
    char *cmd[4] = {(char *)"python3", (char *)"data/Cgi/script.py", (char *)NULL};
    
    execve("/usr/bin/python3", cmd, cmd);
    
    std::cout << "Failed to execute the Python script." << std::endl;

    return 1;
}
