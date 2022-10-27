
#include <utils/keywords.h> // unless, in, assert
#include <iostream> // std::cerr, std::cout, std::endl

enum Status {
    first = 1,
    /////////////////
    PASSED = 1,
    FAILED = 2,
    SKIPPED = 3,
    /////////////////
    last = 3,
    size = 3
};

const char* str[] = {
    "", // 0 isn't used on purpose
    "passed",
    "failed",
    "skipped"
};

int main()
{
    Status status;
    unless (status) {
        std::cerr << "WARN: status uninitialized" << std::endl;
    }

    status = Status::PASSED;

    assert (in (Status::first, Status::last)(status), "Invalid Status");
    
    std::cout << "There are " << Status::size << " different statuses" << std::endl;
    
    for (auto status : range (Status::first, Status::last)) {
        std::cout << str[status] << std::endl;
    }
}
