#define _GNU_SOURCE

#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>

#include <linux/limits.h>

#include <util.h>
#include <rcodes.h>
#include <file-info.h>

int main(int argc, char const *argv[])
{
    char path[PATH_MAX] = { 0 };

    if (argc < 2)
    {
        snprintf(path, PATH_MAX, "%s", ".");
    }
    else
    {
        if (PATH_MAX < snprintf(path, PATH_MAX, "%s", argv[1]))
        {
            fprintf(stderr, "Can't make dir path, output was truncated!\n");
            return ERR_FAIL;
        }
    }

    DIR *dir = opendir(path);
    if (!dir)
    {
        fprintf(stderr, "Can't open directory %s, %s\n", path, strerror(errno));
        return ERR_FAIL; 
    }

    uint64_t total_bytes = 0;
    struct dirent *dir_entry = NULL;
    while ((dir_entry = readdir(dir)) != NULL)
    {
        if (dir_entry->d_name[0] == '.')
        {
            continue;
        }

        struct stat stat_buf = { 0 };
        const char *full_path = util_path_file_concat(path, dir_entry->d_name);
        if (!full_path)
        {
            closedir(dir);
            return ERR_FAIL;
        }

        if (0 != stat(full_path, &stat_buf))
        {
            closedir(dir);
            return ERR_FAIL;
        }
        
        if (DT_LNK == dir_entry->d_type)
        {
            if (0 != lstat(full_path, &stat_buf))
            {
                closedir(dir);
                return ERR_FAIL;
            }
        }

        // TODO: There is no column indenting
        // TODO: There is no alphabetic sorting
        if (ERR_NONE != file_info_print(dir_entry, &stat_buf, full_path))
        {
            closedir(dir);
            return ERR_FAIL;
        }

        total_bytes += (uint64_t)stat_buf.st_size;
    }

    printf("Total %ld bytes\n", total_bytes);

    closedir(dir);

    return ERR_NONE;
}
