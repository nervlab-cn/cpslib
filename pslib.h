#pragma once

#include "ps.h"

/**
 * @brief disk_usage 磁盘使用量
 * @param path 路径
 * @param usage info 使用量
 * @return true/false 是否成功
 */
bool disk_usage(const char*, DiskUsage*);

/**
 * @brief disk_partitions 获取磁盘分区信息
 * @return 从磁盘分区信息
 */
DiskPartitionInfo* disk_partitions(bool physical);
void free_disk_partition_info(DiskPartitionInfo*);

/**
 * @brief disk_io_counters 获取磁盘I/O计数信息
 * @return I/O信息
 */
DiskIOCounterInfo* disk_io_counters(void);
void free_disk_io_counter_info(DiskIOCounterInfo*);

/**
 * @brief net_io_counters 获取网络I/O计数信息
 * @return I/O信息
 */
NetIOCounterInfo* net_io_counters(void);
void free_net_io_counter_info(NetIOCounterInfo*);

/**
 * @brief get_users 获取用户信息
 * @return 用户信息
 */
UsersInfo* get_users(void);
void free_users_info(UsersInfo*);

/**
 * @brief get_boot_time 获取系统启动时间
 * @return
 */
uint32_t get_boot_time(void);

/**
 * @brief virtual_memory 获取系统虚拟内存使用量
 * @return true/false
 */
bool virtual_memory(VmemInfo*);

/**
 * @brief swap_memory 获取系统swap使用量
 * @return true/false
 */
bool swap_memory(SwapMemInfo*);

/**
 * @brief cpu_times
 * @return
 */
CpuTime* cpu_times(bool per_cpu);

CpuTimeList* cpu_times_s(bool per_cpu);

/**
 * @brief cpu_times_percent
 * @return
 */
CpuTime* cpu_times_percent(bool per_cpu, CpuTime* prev_times);
CpuTimeList* cpu_time_percent_s(bool per_cpu, CpuTimeList* prev_times);

/**
 * @brief cpu_util_percent
 * @param percpu
 * @param prev_times
 * @return
 */
double* cpu_util_percent(bool per_cpu, CpuTime* prev_times);
CpuRatio cpu_util_percent_s(bool per_cpu, CpuTimeList* perv_times);

/**
 * @brief cpu_count 逻辑计算器数量
 * @return
 */
uint32_t cpu_count(bool);

/**
 * @brief pid_exists 检查进程是否存在
 * @return
 */
bool pid_exists(pid_t);

/**
 * @brief get_process 获取进程信息
 * @return
 */
ProcessPtr get_process(pid_t);
void free_process(ProcessPtr p);

/**
 * @brief process_cpu_util_percent 获取进程cpu使用量
 * @param pid
 * @return
 */
double process_cpu_util_percent(pid_t pid);

/**
 * @brief process_memory 获取进程内存使用量
 * @param pid 进程id
 * @param mem 内存
 * @return true/false
 */
bool process_memory(pid_t pid, ProcessMemInfo* mem);

/**
 * @brief get_processes 获取进程列表
 * @return true/false
 */
ARRAY_ProcessPtr* get_processes();

ARRAY_Thread* get_threads(pid_t pid);
void free_thread(Thread* t);

/* Required to avoid [-Wimplicit-function-declaration] for python bindings */
// void gcov_flush(void);

// disk_io_counters_per_disk
// net_io_counters_per_nic
