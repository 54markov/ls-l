#pragma once

#include <time.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

/**
 * Include set-user-ID, set-group-ID, and sticky
 * bit information.
 */
#define UTIL_FP_SPECIAL 1

/**
 * Concatenates @path and @file to full path string.
 * Returns NULL if @path or @file isn't valid or resulting string > PATH_MAX.
 * @path : File path.
 * @file : File name.
 */
const char *util_path_file_concat(const char *path, const char *name);

/**
 * Returns ls -l style string for file permissions mask.
 * @perm  : File permissions mask.
 * @flags : Include set-user-ID, set-group-ID, and sticky
 *          bit information.
 */
const char *util_file_perm_str(const mode_t perm, int flags);

/**
 * Returns ls -l style string for file type or NULL if @type isn't valid.
 * @type : Directory type.
 */
const char *util_file_type_str(const unsigned char type);

/**
 * Returns last modifed string for file in format: 'months day hour:min'
 * or NULL if @time isn't valid or can't convert time.
 * @time : File last modified time.
 */
const char *util_file_last_mod_time_str(const time_t *time);

/**
 * Returns colored file name (for symbolic links resolves references)
 * or NULL if @path @name isn't valid.
 * @path : Path to file.
 * @name : File name.
 * @type : File type.
 */
const char *util_file_name_fstr(
    const char *path,
    const char *name,
    const unsigned char type);