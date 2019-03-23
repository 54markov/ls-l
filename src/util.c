#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>

#include <util.h>

#define RED      "\033[0;31m"
#define GRN      "\033[0;32m"
#define YEL      "\033[33m"
#define BLU      "\033[34m"
#define MAG      "\033[35m"
#define CYN      "\033[36m"
#define WHT      "\033[37m"
#define RST      "\033[0m"

#define STR_SIZE sizeof("rwxrwxrwx")


/**
 * Concatenates @path and @file to full path string.
 * Returns NULL if @path or @file isn't valid or resulting string > PATH_MAX.
 * @path : File path.
 * @file : File name.
 */
const char *util_path_file_concat(const char *path, const char *name)
{
    if (!path)
        return NULL;

    if (!name)
        return NULL;

    static char full_path[PATH_MAX];

    if (PATH_MAX < snprintf(full_path, PATH_MAX, "%s/%s", path, name))
    {
        fprintf(stderr, "Can't make full path, output was truncated!\n");
        return NULL;
    }

    return full_path;
}

/**
 * Returns ls -l style string for file permissions mask.
 * @perm  : File permissions mask.
 * @flags : Include set-user-ID, set-group-ID, and sticky
 *          bit information.
 */
const char *util_file_perm_str(const mode_t perm, int flags)
{
    static char str[STR_SIZE];

    snprintf(str, STR_SIZE, "%c%c%c%c%c%c%c%c%c",
        // Owner
        (perm & S_IRUSR) ? 'r' : '-',
        (perm & S_IWUSR) ? 'w' : '-',
        (perm & S_IXUSR) ?
            (((perm & S_ISUID) && (flags & UTIL_FP_SPECIAL)) ? 's' : 'x') :
            (((perm & S_ISUID) && (flags & UTIL_FP_SPECIAL)) ? 'S' : '-'),
        // Group
        (perm & S_IRGRP) ? 'r' : '-',
        (perm & S_IWGRP) ? 'w' : '-',
        (perm & S_IXGRP) ?
            (((perm & S_ISGID) && (flags & UTIL_FP_SPECIAL)) ? 's' : 'x') :
            (((perm & S_ISGID) && (flags & UTIL_FP_SPECIAL)) ? 'S' : '-'),
        // Others
        (perm & S_IROTH) ? 'r' : '-',
        (perm & S_IWOTH) ? 'w' : '-',
        (perm & S_IXOTH) ?
            (((perm & S_ISVTX) && (flags & UTIL_FP_SPECIAL)) ? 't' : 'x') :
            (((perm & S_ISVTX) && (flags & UTIL_FP_SPECIAL)) ? 'T' : '-'));

    return str;
}

/**
 * Returns ls -l style string for file type or NULL if @type isn't valid.
 * @type : Directory type.
 */
const char *util_file_type_str(const unsigned char type)
{
    switch (type)
    {
        case DT_REG:  return "-"; // Regular file
        case DT_DIR:  return "d"; // Directory
        case DT_FIFO: return "p"; // Pipe
        case DT_SOCK: return "s"; // Socket
        case DT_CHR:  return "c"; // Character device
        case DT_BLK:  return "b"; // Block device
        case DT_LNK:  return "l"; // Symbolic link
    }

    return NULL;
}

/**
 * Returns last modifed string for file in format: 'months day hour:min'
 * or NULL if @time isn't valid or can't convert time.
 * @time : File last modified time.
 */
const char *util_file_last_mod_time_str(const time_t *time)
{
    if (!time)
        return NULL;

    static char buf[NAME_MAX];
    if (0 == strftime(buf, NAME_MAX, "%b %d %H:%M", localtime(time)))
        return NULL;

    return buf;
}

/**
 * Returns colored file name (for symbolic links resolves references).
 * or NULL if @path @name isn't valid.
 * @path : Path to file.
 * @name : File name.
 * @type : File type.
 */
const char *util_file_name_fstr(
    const char *path,
    const char *name,
    const unsigned char type)
{
    if (!path)
        return NULL;

    if (!name)
        return NULL;

    char *resolved_path = NULL;
    static char buf[PATH_MAX];

    switch (type)
    {
        case DT_DIR:
            snprintf(buf, sizeof(buf), "%s%s%s", GRN, name, RST);
            break;
        case DT_FIFO:
            snprintf(buf, sizeof(buf), "%s%s%s", MAG, name, RST);
            break;
        case DT_SOCK:
            snprintf(buf, sizeof(buf), "%s%s%s", CYN, name, RST);
            break;
        case DT_CHR:
            snprintf(buf, sizeof(buf), "%s%s%s", YEL, name, RST);
            break;
        case DT_BLK:
            snprintf(buf, sizeof(buf), "%s%s%s", RED, name, RST);
            break;
        case DT_LNK:
             snprintf(buf, sizeof(buf), "%s%s%s -> %s", BLU, name, RST,
                realpath(path, resolved_path));
            break;
        default:
            snprintf(buf, sizeof(buf), "%s", name);
            break;     
    }

    free(resolved_path);

    return buf;
}
