#include <iostream>
#include <variant>

namespace Response {
    struct Successful  /* 2XX */ {int code;};
    struct ClientError /* 4XX */ {int code;};
    struct ServerError /* 5XX */ {int code;};
    using Any = std::variant<Successful,ClientError,ServerError>;
    
    struct Process {
        void operator()(Successful _) {
            std::cout << "successful response" << std::endl;
        }
        void operator()(ClientError _) {
            std::cout << "client error response" << std::endl;
        }
        void operator()(ServerError _) {
            std::cout << "server error response" << std::endl;
        }
    };
};

void process(Response::Any r) {
    std::visit(Response::Process{}, r);
}

template<class T>
void process(int response_code) {
    process(T{response_code});
}

int main()
{
    int code = 0;
    // disguise code as a specific type
    process<Response::Successful>(code);
    process(Response::ClientError{code});
    
    {
        using namespace Response;
        Process{}(ServerError{code});
    }
}
