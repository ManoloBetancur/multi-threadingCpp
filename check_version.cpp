#include <iostream>

int main() {
    std::cout << "C++ version: ";

#if __cplusplus == 199711L
    std::cout << "C++98/03";
#elif __cplusplus == 201103L
    std::cout << "C++11";
#elif __cplusplus == 201402L
    std::cout << "C++14";
#elif __cplusplus == 201703L
    std::cout << "C++17";
#elif __cplusplus == 202002L
    std::cout << "C++20";
#else
    std::cout << "Unknown";
#endif

    std::cout << std::endl;
    return 0;
}
