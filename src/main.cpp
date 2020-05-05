#include <csvm/compiler.hpp>
#include <cstdio>
#include <cerrno>
#include <fstream>
#include <cstring>

int main(int argc, const char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <INPUT>\n", argv[0]);
        return 1;
    }

    std::fstream fin(argv[1], std::ios::in);
    if (!fin) {
        fprintf(stderr, "%s: cannot open: %s\n", argv[1],
            strerror(errno));
        return 1;
    }

    std::string src;
    std::string line;
    while (std::getline(fin, line)) {
        src.append(line);
        src.push_back('\n');
    }

    try {
        auto ast = cs::compiler::compile_to_ast(argv[1], src);
        printf("%s\n", ast.c_str());
    } catch (cs::compile_error &err) {
        printf("CompileError: %s\n", err.what());
    }
    return 0;
}
