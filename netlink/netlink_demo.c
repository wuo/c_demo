/*
 * Use sudo to execute this program
 */
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <sys/poll.h>
#include <linux/netlink.h>
#include <sys/un.h>
#include <signal.h>
#include <fcntl.h>

static void handler(int p) {
    printf("in signal handler\n");
    return;
}

void process_uevent_message(int sock) {
    char buffer[64*64];
    int count = recv(sock, buffer, sizeof(buffer), 0);
    buffer[64*64 - 1] = '\0';
    printf("%s\n", buffer);
}

int main() {
    struct sockaddr_nl nladdr;
    struct pollfd pollfds[2];
    int uevent_sock;
    int ret, max = 0;
    int uevent_sz = 64 * 1024;
    int timeout = -1;
    struct sigaction timeoutsigact;
    timeoutsigact.sa_handler = handler;
    sigemptyset(&timeoutsigact.sa_mask);
    sigaddset(&timeoutsigact.sa_mask, SIGALRM);
    sigaction(SIGALRM, &timeoutsigact, 0);

    memset(&nladdr, 0, sizeof(nladdr));
    nladdr.nl_family = AF_NETLINK;
    nladdr.nl_pid = getpid();
    nladdr.nl_groups = 0xffffffff;

    uevent_sock = socket(PF_NETLINK, SOCK_DGRAM,  NETLINK_KOBJECT_UEVENT);
    if (uevent_sock < 0) {
        printf("Netlink socket failed\n");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(uevent_sock, SOL_SOCKET, SO_RCVBUFFORCE, &uevent_sz, sizeof(uevent_sz)) < 0) {
        printf("unable to set sock option\n");
        exit(EXIT_FAILURE);
    }

    if (bind(uevent_sock, (struct sockaddr*)&nladdr, sizeof(nladdr)) < 0) {
        printf("unable to bind\n");
        exit(EXIT_FAILURE);
    }

    pollfds[0].fd = uevent_sock;
    pollfds[0].events = POLLIN;

    ret = fcntl(uevent_sock, F_SETFL, O_NONBLOCK);
    if (ret < 0) {
        printf("fcntl error\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        ret = poll(pollfds, 1, timeout);
        switch(ret) {
            case 0:
                printf("poll timeout\n");
                continue;
            case -1:
                printf("poll error\n");
                break;
            default:
                if (pollfds[0].revents & POLLIN)
                    process_uevent_message(uevent_sock);
        }
    }

    close(uevent_sock);
    return 1;
}

