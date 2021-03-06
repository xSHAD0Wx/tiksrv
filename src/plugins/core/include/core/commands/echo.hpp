#ifndef TIKSRV_PLUGINS_CORE_COMMANDS_ECHO_HPP
#define TIKSRV_PLUGINS_CORE_COMMANDS_ECHO_HPP

#include "interop/command.hpp"
#include "net/tcp_client.hpp"

#include <string>

namespace ts::plugins::core::commands {

class echo_command final : public ts::interop::command {
    using client_ptr = std::shared_ptr<ts::net::tcp_client>;

  public:
    echo_command() : ts::interop::command {"Echo"} {
    }

    void execute(client_ptr client, ts::net::request &&req) override;
};

} // namespace ts::plugins::core::commands

#endif
