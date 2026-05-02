#ifndef EXCEPTION_H
#define EXCEPTION_H

class out_of_range {
private:
    const char* msg;
public:
    explicit out_of_range(const char* _msg = "out_of_range: index was out of range") : msg(_msg) {}
    const char* what() const {
        return msg;
    }
};

class bad_alloc {
private:
    const char* msg;
public: 
    bad_alloc() : msg("bad_alloc: memory allocation failed") {}
    const char* what() const {
        return msg;
    }
};

class illegal_size {
private:
    const char* msg;
public:
    explicit illegal_size(const char* _msg = "illegal_size: ...") : msg(_msg) {}
    const char* what() const {
        return msg;
    }
};

#endif //EXCEPTION_H