#ifndef __config_h
#define __config_h

struct th_config {
    long max_memory;
    int max_cpu_time;
    int max_real_time;
    char *dir;
    char *in;
    char *out;
    char *err;
    char *env[256];
    char *args[256];
};

#endif  // __config_h
