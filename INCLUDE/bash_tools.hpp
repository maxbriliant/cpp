// bash_tools.hpp
#pragma once

#include <string>
#include <memory>
#include <cstdlib>  // realpath, free
#include <stdexcept>
#include <cerrno>
#include <cstring>  // strerror

namespace bash_tools {

// Holt den absoluten Pfad eines Dateisystems-Objekts
inline std::string get_realpath(const std::string& path) {
    char* resolved = realpath(path.c_str(), nullptr);
    if (!resolved) {
        throw std::runtime_error(std::string("\nrealpath() in get_realpath fehlgeschlagen \n(Existiert die Datei?) ") + strerror(errno) +"\n\n");
    }

    std::unique_ptr<char, decltype(&free)> ptr(resolved, &free);
    return std::string(ptr.get());
}

} // namespace bash_tools
