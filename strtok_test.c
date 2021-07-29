/**
 * @author zouxiaoliang
 * @date 2021/7/27
 */

#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>
#include <sys/stat.h>
#include <unistd.h>

#include "pslib.h"
#include "utils/dict.h"
#include "linux/proc_keys.h"

void dump_dirt_node(const char* key, const void* value) {
    printf(" -- %s -> '%s'\n", key, (const char*)value);
}

struct dict_t* parse_to_dict(char* buffer, const char* delim) {
    char* token = NULL;
    char* next_token = NULL;
    char* key = NULL;
    char* value = NULL;

    struct dict_t* d = dict_init(&free);
    if (NULL == d) {
        return NULL;
    }

    int is_token = 0;
    size_t token_count = sizeof(status_reserved) / sizeof(char*);

    token = strtok_r(buffer, delim, &next_token);
    while (NULL != token) {
        is_token = 0;
        size_t i = 0;

        for (i = 0; i < token_count; ++i) {
            if (0 == strcmp(token, status_reserved[i])) {
                // push to the dict
                if (NULL != key && NULL != value) {
                    dict_set(d, key, value);
                } else if (NULL != value) {
                    free(value);
                } else {
                    // no idea
                }

                // next key
                key = token;
                value = NULL;
                is_token = 1;

                break;
            }
        }

        if (0 == is_token) {
            // append to the value;
            if (NULL == value) {
                value = calloc(1, strlen(token) + 1);
                strcat(value, token);
            } else {
                value = realloc(value, strlen(value) + 1 + strlen(token) + 1);
                strcat(value, " ");
                strcat(value, token);
            }
        }

        token = strtok_r(NULL, delim, &next_token);
    }

    if (NULL != key && NULL != value) {
        dict_set(d, key, value);
    } else if (NULL != value) {
        free(value);
    } else {
        // no idea
    }

    return d;
}

char* procfs_read(const char* path) {
    char* content = NULL;
    char buffer[256];
    int fp = open(path, O_RDONLY);
    if (-1 == fp) {
        printf("open file %s failed, what: %s", path, strerror(errno));
        goto error;
    }

    size_t length = 0;
    do {
        int r = read(fp, buffer, 256);
        if (-1 == r) {
            goto error;
        } else if (0 == r) {
            break;
        } else {
            size_t i = length;
            length += r;
            content = realloc(content, length);
            memcpy(content + i, buffer, r);
        }
    } while (1);

    return content;

error:
    if (NULL != content) {
        free(content);
    }
    if (-1 != fp) {
        close(fp);
    }
    return NULL;
}

void status(pid_t pid) {
    char filepath[64];
    sprintf(filepath, "/proc/%d/status", pid);
    const char* delim = " :\t\n";

    char* buffer = procfs_read(filepath);
    if (NULL == buffer) {
        return;
    }

    struct dict_t* d = parse_to_dict(buffer, delim);
    for_each(d, &dump_dirt_node);
    dict_fini(d);
    free(buffer);
}

int main() {
    printf("hello world!!!\n");

    status(getpid());
    ARRAY_ProcessPtr * pl = get_processes();
    if (NULL != pl) {
        size_t i = 0;
        for (i = 0; i < pl->length; ++i) {
            printf("-- pid: %d, exe: %s, cmdline: %s\n",
                   pl->data[i]->pid,
                   pl->data[i]->exe,
                   pl->data[i]->cmdline);
        }
        ProcessPtr_fini_with_callback(pl, free_process);
    }

    pid_t p = 24299;
    printf("pid: %d\n", p);
    ARRAY_Thread * tl = get_threads(p);
    if (NULL != tl) {
        size_t i = 0;
        for (i = 0; i < tl->length; ++i) {
            printf(
                " -- tid: %d, name: %s\n", tl->data[i].tid, tl->data[i].name);
        }
        Thread_fini_with_callback(tl, free_thread);
    }else {
        printf("error...");
    }

    return 0;
}
