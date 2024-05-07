/*
** EPITECH PROJECT, 2024
** fetch_info
** File description:
** fetch_info
*/

#ifndef FETCH_INFO_H
    #define FETCH_INFO_H
    #include <stddef.h>

    #define RESOLUTION_COMMAND "xdpyinfo | awk '/dimensions/ {print $2}'"
    #define UPTIME_PATH "/proc/uptime"
    #define HOST_PATH "/sys/devices/virtual/dmi/id/product_name"
    #define MEMORY_PATH "/proc/meminfo"
    #define OS_PATH "/etc/os-release"
    #define CPU_PATH "/proc/cpuinfo"
    #define GPU_COMMAND "lspci -mm | grep -i 'vga\\|3d\\|2d'"

char *get_os(env_t *);
char *get_host(env_t *);
char *get_kernel(env_t *);
char *get_uptime(env_t *);
char *get_shell(env_t *);
char *get_resolution(env_t *);
char *get_desktop_environment(env_t *);
char *get_cpu(env_t *);
char *get_gpu(env_t *);
char *get_memory(env_t *);

static const size_t SIZE_FETCH_INFO = 10;

typedef struct fetch_info_s {
    char *var;
    char *(*data)(env_t *);
} fetch_info_t;

static const fetch_info_t FETCH_INFO[] = {
    {"OS", get_os},
    {"Host", get_host},
    {"Kernel", get_kernel},
    {"Uptime", get_uptime},
    {"Shell", get_shell},
    {"Resolution", get_resolution},
    {"DE", get_desktop_environment},
    {"CPU", get_cpu},
    {"GPU", get_gpu},
    {"Memory", get_memory}
};

#endif /* !FETCH_MODEL_H */
