#include <deque>

#ifdef TESTING
#ifndef DUMMY_SOCKET_H
#define DUMMY_SOCKET_H

class Socket {
private:
    std::deque<void*> my_queue;
    int skt;

public:
    Socket(const char* hostname, const char* servname) {
        this->skt = 0;
    };

    explicit Socket(const char* servname) {
        this->skt = 1;
    };

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
    Socket accept() { return *this; };
    bool operator==(const Socket& other) const { return this->skt == other.skt; };
    bool operator!=(const Socket& other) const { return !(*this == other); };
    ~Socket(){};
};

#endif  // DUMMY_SOCKET_H
#endif  // TESTING