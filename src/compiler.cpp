#include <csvm/compiler.hpp>
#include "rustlib.hpp"

namespace cs {
    std::unique_ptr<compiled_code> compiler::compile_to_bytecode(const std::string &file,
                                                                 const std::string &src) {
        auto result = ::compile_source(file.c_str(), src.c_str());
        if (result.kind != CCompileResultKind::Success) {
            mpp::throw_ex<compile_error>(result.message);
        }
        return std::make_unique<compiled_code>(
            const_cast<unsigned char *>(result.compiled_code),
            result.compiled_code_length);
    }

    std::string compiler::compile_to_ast(const std::string &file, const std::string &src) {
        return std::__cxx11::string();
    }
}
