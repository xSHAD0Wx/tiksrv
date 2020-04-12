#include "config.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

void
ts_config_parse_argv(struct ts_config *cfg, int argc, char **argv)
{
    char arg;
    long parsed_value;

    static struct option options[] = {
        { "port", required_argument, NULL, 'p' },
        { "backlog", required_argument, NULL, 'b' },
        { "ipv6", no_argument, NULL, '6' },
        { "verbose", no_argument, NULL, 'v' },
        { "help", no_argument, NULL, 'h' },
        { "version", no_argument, NULL, 'V' },
    };

    cfg->exec_name   = argv[0];
    cfg->listen_port = TS_CONFIG_DEFAULT_PORT;
    cfg->backlog     = TS_CONFIG_DEFAULT_BACKLOG;
    cfg->ipv6        = TS_CONFIG_DEFAULT_IPV6_ENABLED;
    cfg->log_level   = TS_CONFIG_DEFAULT_LOG_LEVEL;

    while ((arg = getopt_long_only(
                argc, argv, TS_CONFIG_ARGS_LIST, options, NULL)) != -1) {
        switch (arg) {
        case 'h':
            printf("Usage: %s %s\n\n%s\n\nOptions:\n%s\n",
                   argv[0],
                   TS_CONFIG_COMMAND_LINE_USAGE,
                   TS_CONFIG_APP_DESCRIPTION,
                   TS_CONFIG_COMMAND_LINE_HELP);
            exit(EXIT_SUCCESS);
        case 'V':
            printf(
                "%s version %s\n", TS_CONFIG_APP_NAME, TS_CONFIG_APP_VERSION);
            exit(EXIT_SUCCESS);
        case 'p':
            cfg->listen_port = atoi(optarg);
            break;
        case 'b':
            cfg->backlog = atoi(optarg);
            break;
        case 'v':
            ++cfg->log_level;
            break;
        case '6':
            cfg->ipv6 = 1;
            break;
        default:
            fprintf(stderr, "[!] Invalid argument value %s\n", optarg);
            exit(EXIT_FAILURE);
        }
    }
}
