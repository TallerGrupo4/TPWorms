#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>

#ifdef TESTING
#ifndef DUMMY_SOCKET_H
#define DUMMY_SOCKET_H


class Socket {
public:
    std::deque<void*> my_queue;
    int skt;
    Socket(const char* hostname, const char* servname) { this->skt = 0; }

    explicit Socket(const char* servname) { this->skt = 1; }

    int sendall(const void* data, unsigned int sz, bool* was_closed) {
        // Create a copy of the data and store it in my_queue
        char* copy = new char[sz];
        memcpy(copy, data, sz);
        my_queue.push_back(copy);
        return sz;
    }

    int recvall(void* data, unsigned int sz, bool* was_closed) {
        if (my_queue.empty()) {
            // Handle the case when the queue is empty
            // Set was_closed or any other appropriate error handling
            return -1;
        }

        // Retrieve the stored data
        char* copy = static_cast<char*>(my_queue.front());

        if (copy == nullptr) {
            // Handle the case when the copy is null (if it's ever possible)
            // Set was_closed or any other appropriate error handling
            return -1;
        }

        // Copy the data back to the provided buffer
        memcpy(data, copy, sz);

        // Clean up the copied data
        delete[] copy;

        // Remove the data from the queue
        my_queue.pop_front();

        return sz;
    }


    void shutdown(int how) {}
    int close() { return 0; }
    Socket accept() { return *this; }
    bool operator==(const Socket& other) const { return this->skt == other.skt; }
    bool operator!=(const Socket& other) const { return !(*this == other); }
    ~Socket() {}
};

#endif  // DUMMY_SOCKET_H
#endif  // TESTING
