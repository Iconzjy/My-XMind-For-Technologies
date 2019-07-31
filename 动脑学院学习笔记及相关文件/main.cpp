#include <unistd.h>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <signal.h>

std::ofstream fs;
void handler(int s)
{
        fs << "exit." << std::endl;
        exit(0);
}

int main(int argc, char** argv)
{
        pid_t pid;
        int fd;
        if ( (pid = fork()) < 0) {
                std::cerr << "[Error] can't fork!" << std::endl;
        } else if ( pid !=0 ) {
                exit(0);
        }
        setsid();
        if ( (fd = open("dev/null", O_RDWR)) != -1) {
                dup2(fd, 0);
                dup2(fd, 1);
                dup2(fd, 2);
                if (fd >2){
                        close(fd);
                }
        }
        signal(SIGINT, handler);
        fs.open("log.txt", std::ofstream::out | std::ofstream::app);
        for(;;){
                fs << "hello" << std::endl;
                sleep(5);
        }
        return 0;
}
}