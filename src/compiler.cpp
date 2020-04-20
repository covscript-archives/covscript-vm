#include <csvm/compiler.hpp>
#include "rustlib.hpp"

namespace cs {
    static void check_and_throw_error(CCompileResult &result) {
        if (result.kind != CCompileResultKind::Success) {
            if (result.kind != CCompileResultKind::MallocError) {
                std::string message{result.message};
                std::free(reinterpret_cast<void *>(
                    const_cast<char *>(result.message)));
                mpp::throw_ex<compile_error>(message);
            } else {
                mpp::throw_ex<compile_error>("An error occurred but we failed to "
                                             "save the error message because malloc() "
                                             "returned a nullptr");
            }
        }
    }

    std::unique_ptr<compiled_code> compiler::compile_to_bytecode(const std::string &file,
                                                                 const std::string &src) {
        auto result = ::compile_source(file.c_str(), src.c_str());
        check_and_throw_error(result);

        return std::make_unique<compiled_code>(
            const_cast<unsigned char *>(result.compiled_code),
            result.compiled_code_length);
    }

    std::string compiler::compile_to_ast(const std::string &file, const std::string &src) {
        auto result = ::compile_to_ast(file.c_str(), src.c_str());
        check_and_throw_error(result);
        std::string ast_text{result.message};
        std::free(reinterpret_cast<void *>(
            const_cast<char *>(result.message)));
        return std::move(ast_text);
    }
}
