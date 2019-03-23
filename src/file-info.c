#define _GNU_SOURCE

#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <stdint.h>

#include <util.h>
#include <file-info.h>

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
    const char *path)
{
    if (!stat_buf)
    {
        fprintf(stderr, "Can't print file info, stat buffer invalid!\n");
        return ERR_BAD_PTR;
    }

    if (!file)
    {
        fprintf(stderr, "Can't print file info, file invalid!\n");
        return ERR_BAD_PTR;
    }

    if (!path)
    {
        fprintf(stderr, "Can't print file info, path invalid!\n");
        return ERR_BAD_PTR;
    }

    struct passwd *passwd = getpwuid(stat_buf->st_uid);
    if (!passwd)
    {
        fprintf(stderr, "Can't print file info, passwd invalid!\n");
        return ERR_BAD_PTR;
    }

    struct group *group = getgrgid(stat_buf->st_gid);
    if (!group)
    {
        fprintf(stderr, "Can't print file info, group invalid!\n");
        return ERR_BAD_PTR;
    }

    printf("%s%s %ld %s %s %ld %s %s\n",
        util_file_type_str(file->d_type),
        util_file_perm_str(stat_buf->st_mode, UTIL_FP_SPECIAL),
        stat_buf->st_nlink,
        passwd->pw_name,
        group->gr_name,
        stat_buf->st_size,
        util_file_last_mod_time_str(&stat_buf->st_mtime),
        util_file_name_fstr(path, file->d_name, file->d_type));

    return ERR_NONE;
}
