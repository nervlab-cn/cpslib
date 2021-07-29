/**
 * @author zouxiaoliang
 * @date 2021/7/27
 */
#ifndef PS_H
#define PS_H

#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>

#include "utils/array.h"

/**
 * @brief 进程状态
 */
enum EProcStatus {
    STATUS_RUNNING,
    STATUS_SLEEPING,
    STATUS_DISK_SLEEP,
    STATUS_STOPPED,
    STATUS_TRACING_STOP,
    STATUS_ZOMBIE,
    STATUS_DEAD,
    STATUS_WAKE_KILL,
    STATUS_WAKING,
    STATUS_IDLE,
    STATUS_LOCKED,
    STATUS_WAITING
};

/**
 *
 */
enum EIOPrioClass {
    IO_PRIO_CLASS_NONE,
    IO_PRIO_CLASS_RT,
    IO_PRIO_CLASS_BE,
    IO_PRIO_CLASS_IDLE
};

/*enum rlimit {
  RLIMIT_INFINITY,
  RLIMIT_AS,
  RLIMIT_CORE,
  RLIMIT_CPU,
  RLIMIT_DATA,
  RLIMIT_FSIZE,
  RLIMIT_LOCKS,
  RLIMIT_MEMLOCK,
  RLIMIT_MSGQUEUE,
  RLIMIT_NICE,
  RLIMIT_NOFILE,
  RLIMIT_NPROC,
  RLIMIT_RSS,
  RLIMIT_RTPRIO,
  RLIMIT_RTTIME,
  RLIMIT_SIGPENDING,
  RLIMIT_STACK
};*/

/**
 * @brief 连接状态
 */
enum EConnectStatus {
    ESTABLISHED,
    SYN_SENT,
    SYN_RECV,
    FIN_WAIT1,
    FIN_WAIT2,
    TIME_WAIT,
    CLOSE,
    CLOSE_WAIT,
    LAST_ACK,
    LISTEN,
    CLOSING,
    NONE,
    DELETE_TCB,
    IDLE,
    BOUND
};

/**
 * @brief 进程属性
 */
enum EProcPriority {
    ABOVE_NORMAL_PRIORITY_CLASS,
    BELOW_NORMAL_PRIORITY_CLASS,
    HIGH_PRIORITY_CLASS,
    IDLE_PRIORITY_CLASS,
    NORMAL_PRIORITY_CLASS,
    REALTIME_PRIORITY_CLASS
};

typedef struct {
    uint64_t total; // 总量
    uint64_t used; // 已使用
    uint64_t free; // 空闲
    float percent; // 使用占比
} DiskUsage;

typedef struct {
    char* device; // 设备名
    char* mountpoint; // 挂载点
    char* fs_type; // 文件系统类型
    char* opts; // 参数
} DiskPartition, *DiskPartitionPtr; /* TODO: Pluralise */

typedef struct {
    uint32_t nitems; // 分区id
    DiskPartition* partitions; // 分区信息
} DiskPartitionInfo;
C_ARRAY(DiskPartitionPtr);

typedef struct {
    char* name; // 磁盘名称
    uint64_t readbytes; // 读字节数
    uint64_t writebytes; // 写字节数
    uint64_t reads; // 读次数
    uint64_t writes; // 写次数
    uint64_t readtime; // 读占用时间
    uint64_t writetime; // 写占用事件
} DiskIOCounters, *DiskIOCountersPtr;

typedef struct {
    uint32_t nitems; //
    DiskIOCounters* iocounters; // 磁盘IO统计
} DiskIOCounterInfo;
C_ARRAY(DiskIOCountersPtr);

typedef struct {
    char* name;
    uint64_t bytes_sent;
    uint64_t bytes_recv;
    uint64_t packets_sent;
    uint64_t packets_recv;
    uint64_t errin;
    uint64_t errout;
    uint64_t dropin;
    uint64_t dropout;
} NetIOCounters, *NetIOCountersPtr;

typedef struct {
    uint32_t nitems;
    NetIOCounters* iocounters;
} NetIOCounterInfo;
C_ARRAY(NetIOCountersPtr);

typedef struct {
    char* username; // 用户名
    char* tty; // tty名称
    char* hostname; // 主机名
    float tstamp; // 登陆时间
} Users, *UsersPtr;

typedef struct {
    uint32_t n_items; // 用户数量
    Users* users; // 用户列表
} UsersInfo;
C_ARRAY(UsersPtr);

typedef struct {
    uint64_t total;
    uint64_t available;
    float percent;
    uint64_t used;
    uint64_t free;
    uint64_t active;
    uint64_t inactive;
    uint64_t buffers;
    uint64_t cached;
    uint64_t wired;
} VmemInfo;

typedef struct {
    uint64_t total;
    uint64_t used;
    uint64_t free;
    float percent;
    uint64_t sin;
    uint64_t sout;
} SwapMemInfo;

typedef struct {
    double user;
    double system;
    double idle;
    double nice;
    double iowait;
    double irq;
    double softirq;
    double steal;
    double guest;
    double guest_nice;
} CpuTime;

typedef struct {
    CpuTime** list;
    size_t length;
    size_t allocated;
} CpuTimeList;
C_ARRAY(CpuTime);

typedef struct {
    double** ratio;
    size_t length;
    size_t allocated;
} CpuRatio;
C_ARRAY(double);

typedef struct {
    pid_t pid;
    pid_t ppid;
    char* name;
    char* exe;
    char* cmdline;
    double create_time;
    uint32_t uid;
    uint32_t euid;
    uint32_t suid;
    uint32_t gid;
    uint32_t egid;
    uint32_t sgid;
    char* username;
    char* terminal;
} Process, *ProcessPtr;

typedef struct {
    uint64_t virtual_size; // 任务虚拟地址空间大小
    uint64_t resident_size; // 正在使用的物理内存大小
    uint64_t shared_size; // 共享内存大小
    uint64_t dirty_size; // 脏页大小
    uint64_t trs; // 程序所有的可执行虚拟内存大小
    uint64_t lrs; // 被影射到任务的虚拟内存空间的库的大小
    uint64_t drs; // 脏页的大小
    double mem_rate;
} ProcessMemInfo;

C_ARRAY(ProcessPtr);

typedef struct {
    pid_t tid; // 线程id
    char* name; // 线程名
} Thread;
C_ARRAY(Thread);

#endif // PS_H
