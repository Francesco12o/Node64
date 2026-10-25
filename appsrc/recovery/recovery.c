#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define PROMPT "BUSY> "
#define MAX_LINE 4096
#define MAX_ARGS 128

#ifndef BUSYBOX_PATH
#define BUSYBOX_PATH "/busybox"
#endif

static const char *default_message =
    "Your system Node.js is compromised!\n"
    "Hopefully, we can save you!\n"
    "REMINDER! - This busybox dosent link every command "
    "to PATH! so be aware youre typing Busybox!";

static void banner(void)
{
    puts("--------------------");
    puts("   WARNING!");
    puts("--------------------");
    puts(default_message);
}

static char *expand_mesg(const char *input)
{
    const char *value = getenv("MESG");

    if (value == NULL)
        value = default_message;

    size_t capacity = strlen(input) + strlen(value) + 1;
    char *output = malloc(capacity);

    if (!output)
        return NULL;

    size_t used = 0;

    for (size_t i = 0; input[i] != '\0';) {
        if (input[i] == '$' &&
            strncmp(input + i, "$MESG", 5) == 0 &&
            (input[i + 5] == '\0' ||
             !(isalnum((unsigned char)input[i + 5]) ||
               input[i + 5] == '_'))) {

            size_t length = strlen(value);

            if (used + length + 1 > capacity) {
                capacity = used + length + 1;
                char *tmp = realloc(output, capacity);

                if (!tmp) {
                    free(output);
                    return NULL;
                }

                output = tmp;
            }

            memcpy(output + used, value, length);
            used += length;
            i += 5;
        } else {
            if (used + 2 > capacity) {
                capacity *= 2;
                char *tmp = realloc(output, capacity);

                if (!tmp) {
                    free(output);
                    return NULL;
                }

                output = tmp;
            }

            output[used++] = input[i++];
        }
    }

    output[used] = '\0';
    return output;
}

static int parse_command(char *line, char **argv)
{
    int argc = 0;
    char *src = line;
    char *dst = line;

    while (*src) {
        while (isspace((unsigned char)*src))
            src++;

        if (!*src)
            break;

        if (argc >= MAX_ARGS - 1) {
            fprintf(stderr, "RecsC: too many arguments\n");
            return -1;
        }

        argv[argc++] = dst;

        char quote = '\0';

        while (*src) {
            if (quote) {
                if (*src == quote) {
                    quote = '\0';
                    src++;
                } else if (*src == '\\' && src[1] &&
                           quote == '"') {
                    src++;
                    *dst++ = *src++;
                } else {
                    *dst++ = *src++;
                }
            } else {
                if (*src == '\'' || *src == '"') {
                    quote = *src++;
                } else if (isspace((unsigned char)*src)) {
                    src++;
                    break;
                } else if (*src == '\\' && src[1]) {
                    src++;
                    *dst++ = *src++;
                } else {
                    *dst++ = *src++;
                }
            }
        }

        if (quote) {
            fprintf(stderr, "RecsC: unmatched quote\n");
            return -1;
        }

        *dst++ = '\0';
    }

    argv[argc] = NULL;
    return argc;
}

static void execute_command(char **argv)
{
    if (!argv[0] || !argv[0][0])
        return;

    if (strcmp(argv[0], "exit") == 0) {
        exit(EXIT_SUCCESS);
    }

    /*
     * Commands must use absolute paths.
     * For example: /busybox echo hello
     */
    if (argv[0][0] != '/') {
        fprintf(stderr,
                "RecsC: use an absolute executable path\n");
        return;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("RecsC: fork");
        return;
    }

    if (pid == 0) {
        execv(argv[0], argv);

        /*
         * If the requested executable is not available,
         * try the configured BusyBox binary as an applet.
         */
        if (strcmp(argv[0], BUSYBOX_PATH) != 0) {
            size_t count = 0;

            while (argv[count])
                count++;

            char **fallback = calloc(count + 2, sizeof(char *));

            if (fallback) {
                fallback[0] = (char *)BUSYBOX_PATH;
                fallback[1] = argv[0];

                for (size_t i = 1; i < count; i++)
                    fallback[i + 1] = argv[i];

                execv(BUSYBOX_PATH, fallback);
                free(fallback);
            }
        }

        fprintf(stderr, "RecsC: cannot execute %s: %s\n",
                argv[0], strerror(errno));
        _exit(127);
    }

    int status;

    while (waitpid(pid, &status, 0) < 0) {
        if (errno == EINTR)
            continue;

        perror("RecsC: waitpid");
        return;
    }
}

int main(void)
{
    char line[MAX_LINE];

    setvbuf(stdout, NULL, _IONBF, 0);
    banner();

    for (;;) {
        fputs(PROMPT, stdout);

        if (!fgets(line, sizeof(line), stdin)) {
            if (feof(stdin))
                break;

            if (errno == EINTR) {
                clearerr(stdin);
                continue;
            }

            perror("RecsC: input");
            break;
        }

        if (!strchr(line, '\n') && !feof(stdin)) {
            int ch;

            while ((ch = getchar()) != '\n' && ch != EOF)
                ;

            fprintf(stderr, "RecsC: command too long\n");
            continue;
        }

        line[strcspn(line, "\n")] = '\0';

        char *expanded = expand_mesg(line);

        if (!expanded) {
            fprintf(stderr, "RecsC: out of memory\n");
            continue;
        }

        char *argv[MAX_ARGS];
        int argc = parse_command(expanded, argv);

        if (argc > 0)
            execute_command(argv);

        free(expanded);
    }

    return EXIT_SUCCESS;
}
