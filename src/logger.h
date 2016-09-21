#ifndef __logger_h
#define __logger_h

// TODO

#define LOGI    (void *) 0
#define LOGD    (void *) 0
#define LOGE    (void *) 0
#define LOGF    (void *) 0

FILE * log_open(const char *);
void log_close(FILE *);
void log_write();

#endif  // __logger_h
