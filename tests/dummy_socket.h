#include <deque>

#ifndef DUMMY_SOCKET_H
#define DUMMY_SOCKET_H

class DummySocket {
private:
    std::deque<void*> my_queue;

public:
    DummySocket(const char* hostname, const char* servname){};

    explicit DummySocket(const char* servname){};

    int sendall(const void* data, unsigned int sz, bool* was_closed) {
        my_queue.push_back((void*)data);
        return sizeof(data);
    };
    int recvall(void* data, unsigned int sz, bool* was_closed) {
        data = my_queue.front();
        my_queue.pop_front();
        return sizeof(data);
    };
    void shutdown(int how){};
    int close() { return 0; };
    DummySocket accept() { return *this; };
};

#endif  // DUMMY_SOCKET_H
