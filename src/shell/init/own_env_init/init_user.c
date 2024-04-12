/*
** EPITECH PROJECT, 2024
** init user
** File description:
** init user and group
*/

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include "functions.h"
#include "env.h"

bool init_user(env_list_t **env)
{
    __uid_t uid = getuid();
    __gid_t gid = getgid();
    struct group *grp = getgrgid(gid);
    struct passwd *pwd = getpwuid(uid);

    if (grp == NULL) {
        perror("getgrgid");
        return false;
    } else
        insert_in_env("GROUP", grp->gr_name, env);
    if (pwd == NULL) {
        perror("getpwuid");
        return false;
    } else {
        insert_in_env("USER", pwd->pw_name, env);
        insert_in_env("LOGNAME", pwd->pw_name, env);
        insert_in_env("HOME", pwd->pw_dir, env);
    }
    return true;
}
