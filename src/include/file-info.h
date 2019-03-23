#pragma once

#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <rcodes.h>


/**
 * Prints file info in ls -l style.
 * Returns ERR_NONE if success otherwise ERR_BAD_PTR.
 * @file     : File structure.
 * @stat_buf : File stat info.
 * @path     : Path to file.
 */
rcode_e file_info_print(
    const struct dirent *file,
    const struct stat *stat_buf,
    const char *path);
