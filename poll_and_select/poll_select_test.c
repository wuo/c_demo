//gcc poll_select_test.c -o test -lpthread
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<sys/eventfd.h>
#include<sys/select.h>
#include<poll.h>

//#define USE_SELECT

void *thread_function(void* arg);
int value = 1;

int main() {
    int res;
    int efd = eventfd(1, 0);
    if (efd == -1) {
        printf("eventfd create error\n");
    }
    pthread_t a_thread;
    int message[1] = {efd};
    res = pthread_create(&a_thread, NULL, thread_function, (void*)message);
    if(res != 0) {
        printf("thread creation failed\n");
        exit(EXIT_FAILURE);
    }
    uint64_t u;
    size_t s;
    eventfd_t s1;
    eventfd_read(efd, &s1);
    printf("value before change %lu\n", s1);
#ifdef USE_SELECT
    fd_set set;
    FD_ZERO(&set);
    FD_SET(efd, &set);
    struct timeval tv;
    tv.tv_sec = 2;
    tv.tv_usec = 0;

    res = select(efd + 1, &set, NULL, NULL, &tv);
    if (res == -1) {
        printf("select error\n");
    } else if (res == 0) {
        printf("time out\n");
    } else {
        printf("select success\n");
        if(FD_ISSET(efd, &set)) {
            s = read(efd, &u, sizeof(uint64_t));
            if(s == sizeof(uint64_t))
                printf("read after select, value is %lu\n", u);
        }
    }
#else
    struct pollfd pfd;
    pfd.fd = efd;
    pfd.events = POLLIN;
    pfd.revents = 0;
    res = poll(&pfd, 1, 5000);
    if(res == -1) {
        printf("poll error\n");
    } else if(res == 0) {
        printf("time out \n");
    } else {
        printf("poll success\n");
        if(pfd.revents & POLLIN) {
            s = read(efd, &u, sizeof(uint64_t));
            if(s == sizeof(uint64_t))
                printf("read after poll, value is %lu\n", u);
        }
    }
#endif
    void *thread_result;
    res = pthread_join(a_thread, &thread_result);
    if(res != 0) {
        printf("thread join failed\n");
        exit(EXIT_FAILURE);
    }
    printf("thread joined, it resulted %s\n", (char*)thread_result);
    exit(EXIT_SUCCESS);
}

void *thread_function(void *arg) {
    sleep(1);
    int fd = *((int*)arg);
    printf("child thread running, argument: %d\n", fd);
    size_t s;
    uint64_t u = 55;
    s = write(fd, &u, sizeof(uint64_t));
    if(s == sizeof(uint64_t)) {
        printf("child thread write success\n");
    }else {
        printf("child thread write error\n");
    }
    pthread_exit("new thread exit\n");
}
