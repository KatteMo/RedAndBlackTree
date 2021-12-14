#pragma once

#include <exception>

class FileNotOpen : public std::exception {
public:
    FileNotOpen() : reason("File is not open!") {}

    const char *what() const noexcept { return reason; }

private:
    const char *reason;
};

class WordError : public std::exception {
public:
    explicit WordError(std::string reason) :
            reason_(("Input word is not right: " + reason + "!"))
    {};

    const char* what() const noexcept override {return reason_.c_str();}
private:
    std::string reason_;
};

class FoundError : public std::exception {
public:
    explicit FoundError(std::string reason) :
            reason_(("Input word do not found:  "+ reason + "!"))
    {};

    const char* what() const noexcept override {return reason_.c_str();}
private:
    std::string reason_;
};

class FalseTranlanion : public std::exception {
public:
    explicit FalseTranlanion(std::string reason) :
            reason_(("Translation is not right:  "+ reason + "!"))
    {};

    const char* what() const noexcept override {return reason_.c_str();}

private:
    std::string reason_;
};
