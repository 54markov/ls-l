#pragma once

#include <time.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

/*
 * Include set-user-ID, set-group-ID, and sticky
 * bit information.
 */
#define UTIL_FP_SPECIAL 1

const char *util_path_file_concat(const char *path, const char *name);
const char *util_file_perm_str(const mode_t perm, int flags);
const char *util_file_type_str(const unsigned char type);
const char *util_file_last_mod_time_str(const time_t *time);
const char *util_file_name_fstr(const char *path,
                                const char *name,
                                const unsigned char type);