#ifndef EZTIK_ROUTEROS_COMMANDS_HPP
#define EZTIK_ROUTEROS_COMMANDS_HPP

#include "eztik/routeros/sentence.hpp"
#include "eztik/routeros/util.hpp"

#include <cstdint>

namespace eztik::routeros::commands {

struct login1 : request_sentence {
    login1(std::uint32_t tag) : request_sentence {command, tag} {
    }

    static constexpr auto command = "/login";
};

struct login2 final : login1 {
    login2(std::uint32_t      tag,
           const std::string &name,
           const std::string &password,
           const std::string &cha)
        : login1 {tag} {
        push_param(name_param, name);
        push_param(password_param, "00{}", hash_password(password, cha));
    }

    static constexpr auto name_param      = "name";
    static constexpr auto password_param  = "response";
    static constexpr auto challenge_param = "ret";
    static constexpr auto challenge_size  = 32UL;
};

struct getall : request_sentence {
    getall(std::uint32_t tag, const std::string &path)
        : request_sentence {path + command_suffix, tag} {
    }

    static constexpr auto command_suffix = "/getall";
};

} // namespace eztik::routeros::commands

#endif
