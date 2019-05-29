#pragma once

#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <rcodes.h>

rcode_e file_info_print(const struct dirent *file,
	                    const struct stat *stat_buf,
                        const char *path);
