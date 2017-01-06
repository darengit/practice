#ifndef __dbg_h__
#define __dbg_h__

#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n",\
    __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define errno_to_string() (errno==0?"None":strerror(errno))

#define log_err(M, ...) fprintf(stderr,\
    "[ERROR] (%s:%d: errno_to_string: %s) " M "\n", __FILE__, __LINE__,\
    errno_to_string(), ##__VA_ARGS__)

#define log_warn(M, ...) fprintf(stderr,\
    "[WARN] (%s:%d: errno_to_string: %s) " M "\n",\
    __FILE__, __LINE__, errno_to_string(), ##__VA_ARGS__)

#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n",\
    __FILE__, __LINE__, ##__VA_ARGS__)

#define check(A, M, ...) if(!(A)) {\
    log_err(M, ##__VA_ARGS__); errno=0; goto error; }

#define goto_error(M, ...) {log_err(M, ##__VA_ARGS__);\
    errno=0; goto error; }

#define check_mem(A) check((A), "Out of memory.")

#define check_debug(A, M, ...) if(!(A)) {debug(M, ##__VA_ARGS__);\
    errno=0; goto error; }

#endif 
