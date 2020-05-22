#include <csvm/variable.hpp>
#include <iostream>
#include <string>

int main()
{
    cs::var_t a;
    const cs::var_t b(a);
    cs::var_t c(cs::typeholder<std::string>(), "Hello");
    auto _b = b.get<cs::monotype>();
    c.get<std::string>() += "World";
    std::cout << b.type().name() << std::endl;
    std::cout << c.get<std::string>() << std::endl;
    return 0;
}
