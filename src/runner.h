#ifndef __runner_h
#define __runner_h

#include <signal.h>

#include "config.h"
#include "logger.h"
#include "result.h"

#define STATUS_SUCCESS              0
#define FORK_FAILED                 1
#define WAIT4_FAILED                2
#define EXEC_FAILED                 3
#define SETTIMER_FAILED             4
#define SETRLIMIT_FAILED            5
#define DUP2_FAILED                 6
#define EXCEVE_FAILED               7
#define LOAD_SECCOMP_FAILED         8
#define SET_UID_FAILED              9
#define SET_GID_FAILED             10

#define RESULT_SUCCESS              0
#define CPU_TIME_LIMIT_EXCEEDED     1
#define REAL_TIME_LIMIT_EXCEEDED    2
#define MEMORY_LIMIT_EXCEEDED       3
#define RUNTIME_ERROR               4
#define SYSTEM_ERROR                5

#define ERR(fp, code)    LOGF((fp), "Error code: %d", (code)); raise(SIGUSR1);

void run(struct th_config *, struct th_result *);

#endif
