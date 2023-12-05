#include <exception>

#ifndef CUSTOM_ERRORS_H
#define CUSTOM_ERRORS_H

class MatchAlreadyExists: public std::exception {
public:
    MatchAlreadyExists() {}
    ~MatchAlreadyExists() {}
    virtual const char* what() const noexcept { return "Match already exists"; }
};

class MatchNotFound: public std::exception {
public:
    MatchNotFound() {}
    ~MatchNotFound() {}
    virtual const char* what() const noexcept { return "Match not found"; }
};

class MatchFull: public std::exception {
public:
    MatchFull() {}
    ~MatchFull() {}
    virtual const char* what() const noexcept { return "Match is full"; }
};

class PlayerNotFound: public std::exception {
public:
    PlayerNotFound() {}
    ~PlayerNotFound() {}
    virtual const char* what() const noexcept { return "Player not found"; }
};

class MatchAlreadyStarted: public std::exception {
public:
    MatchAlreadyStarted() {}
    ~MatchAlreadyStarted() {}
    virtual const char* what() const noexcept { return "Match already started"; }
};

class MapNotFound: public std::exception {
    const char* what() const noexcept override {
        return "Was not able to find Map with that id when creating the match";
    }
};

class NoWormsLeft: public std::exception {
public:
    NoWormsLeft() {}
    ~NoWormsLeft() {}
    virtual const char* what() const noexcept { return "No worms left"; }
};

class LostConnection: public std::exception {
public:
    LostConnection() {}
    ~LostConnection() {}
    virtual const char* what() const noexcept { return "Lost connection with the server"; }
};

#endif
