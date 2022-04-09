#ifndef ERROR_HPP
#define ERROR_HPP

class Error
{
    private:
        char* _error;

    public:
        Error(const char* err);
        ~Error();

    public:
        inline const char* String() { return _error != nullptr ? _error : ""; }
        inline bool HasError() { return _error != nullptr; }
};

#endif