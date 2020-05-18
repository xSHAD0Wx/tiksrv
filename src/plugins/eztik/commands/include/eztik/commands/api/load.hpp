#ifndef EZTIK_COMMANDS_API_LOAD_HPP
#define EZTIK_COMMANDS_API_LOAD_HPP

#include "eztik/commands/session_required.hpp"

#include "eztik/data/api_repository.hpp"
#include "eztik/services/sessions.hpp"

#include "log/logger.hpp"
#include "net/message.hpp"

#include <string>

namespace eztik::commands::api {

template <typename TModel>
class load_command : public session_required_command {
    using client_ptr = std::shared_ptr<ts::net::tcp_client>;

  public:
    load_command(std::string &&                     name,
                 ts::log::logger &                  logger,
                 eztik::services::sessions_service &sessions_svc)
        : session_required_command {std::move(name), logger, sessions_svc} {
    }

    void execute(client_ptr client, ts::net::request &&req) override {
        eztik::data::api_repository<TModel> repo {current_session()->api()};

        repo.load_stream([this, client {std::move(client)}](
                             const auto &err, auto &&user, auto is_last) {
            if (err) {
                logger().error("Could not load `{}': {}", TModel::api_path,
                               err.message());
                return;
            }

            if (is_last) {
                return;
            }

            logger().error("[+] Name: {}, Password: {}", user.name,
                           user.password);
        });
    }
};

} // namespace eztik::commands::api

#endif