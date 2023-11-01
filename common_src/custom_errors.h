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
