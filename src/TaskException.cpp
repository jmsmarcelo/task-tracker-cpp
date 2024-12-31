#include "TaskException.hpp"

task::FileWriteException::FileWriteException(const std::string& fileName): message{"Failed to write to file: " + fileName} {}
const char* task::FileWriteException::what() const noexcept {
    return message.c_str();
}