#ifndef __config_h
#define __config_h

#include <sys/types.h>

struct th_config {
    long    max_memory;
    int     max_cpu_time;
    int     max_real_time;

    FILE    in;
    FILE    out;
    FILE    err;
    FILE    log;

    char    *path;
    char    *env[256];
    char    *args[256];

    uid_t   uid;
    gid_t   gid;
};

#endif  // __config_h
