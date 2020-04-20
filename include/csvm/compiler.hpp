#pragma once

#include <mozart++/string>
#include <mozart++/core>
#include <memory>

namespace cs {
    struct compile_error : public mpp::runtime_error {
        explicit compile_error(const std::string &str)
            : mpp::runtime_error(str) {
        }
    };

    struct compiled_code : public mpp::nocopyable, mpp::nomovable {
        unsigned char *_bytecode;
        size_t _size;

        compiled_code(unsigned char *bytecode, size_t size)
            : _bytecode(bytecode), _size(size) {
        }

        ~compiled_code() {
            if (_bytecode) {
                ::free(_bytecode);
            }
        }
    };

    struct compiler {
        static std::unique_ptr<compiled_code> compile_to_bytecode(const std::string &file,
                                                                  const std::string &src);

        static std::string compile_to_ast(const std::string &file,
                                          const std::string &src);
    };
}
