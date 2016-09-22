#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <seccomp.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "runner.h"

#define STACK_SIZE  (2 * 1024 * 1024)

static int set_timer(int sec, int ms, int is_cpu_time) {
    struct itimerval timerval;
    timerval.it_interval.tv_sec = timerval.it_interval.tv_usec = 0;
    timerval.it_value.tv_sec = sec;
    timerval.it_value.tv_usec = ms * 1000;

    if (setitimer(is_cpu_time ? ITIMER_VIRTUAL : ITIMER_REAL, &timerval, NULL) != 0) {
        return SETITIMER_FAILED;
    }

    return EXEC_SUCCESS;
}

static void init_sandbox() {
    // Syscalls whitelist.
    static int whitelist[] = {
        SCMP_SYS(brk),          SCMP_SYS(read),
        SCMP_SYS(open),         SCMP_SYS(mmap),
        SCMP_SYS(fstat),        SCMP_SYS(close),
        SCMP_SYS(access),       SCMP_SYS(munmap),
        SCMP_SYS(mprotect),     SCMP_SYS(arch_prctl),
        SCMP_SYS(exit_group),
    };

    static int whitelist_length = sizeof(syscalls_whitelist) / sizeof(int);

    scmp_filter_ctx ctx = seccomp_init(SCMP_ACT_KILL);

    for (int i = 0; i < whitelist_length; ++i) {
        seccomp_rule_add(ctx, SCMP_ACT_ALLOW, whitelist[i], 0);
    }

    // Extra rule for execve.
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(execve), 1, SCMP_A0(SCMP_CMP_EQ, (scmp_datum_t)(config->dir)));

    // Only fd 0, 1, 2 are allowed.
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(write), 1, SCMP_A0(SCMP_CMP_LE, 2));

    seccomp_load(ctx);
    seccomp_release(ctx);
}

// TODO: spawn a child process.
void spawn() {}

// TODO: run the custom program.
void run(struct th_config *config, struct th_result *result) {
    int status;
    struct rusage resource_usage;
}
