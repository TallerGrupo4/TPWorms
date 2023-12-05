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
    // std::queue<char> my_queue;
    std::deque<char*> my_queue;
    int skt;
    Socket(const char* hostname, const char* servname) { this->skt = 0; }

    explicit Socket(const char* servname) { this->skt = 1; }

    int sendall(const void* data, unsigned int sz, bool* was_closed) {
        // Create a copy of the data and store it in my_queue
        // Try without the new
        char* copy = new char[sz];
        memcpy(copy, data, sz);
        my_queue.push_back(copy);
        // for (unsigned int i = 0; i < sz; i++) {
        //     my_queue.push_back(static_cast<char*>(data)[i]);
        // }
        return sz;
    }

    int recvall(void* data, unsigned int sz, bool* was_closed) {
        if (my_queue.empty() && my_queue.size() < sz) {
            // Handle the case when the queue is empty or the size is smaller than sz
            // Set was_closed or any other appropriate error handling
            return -1;
        }

        // for (unsigned int i = 0; i < sz; i++) {
        //     data[i] = my_queue.front();
        //     my_queue.pop_front();
        // }
        // char copy = my_queue.front();
        // Retrieve the stored data
        char* copy = static_cast<char*>(my_queue.front());

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
    ~Socket() {
        for (unsigned int i = 0; i < my_queue.size(); i++) {
            delete[] my_queue[i];
        }
    }
};

#endif  // DUMMY_SOCKET_H
#endif  // TESTING
