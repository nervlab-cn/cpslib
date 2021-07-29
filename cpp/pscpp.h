/**
 * @author zouxiaoliang
 * @date 2021/7/27
 */
#ifndef PSCPP_H
#define PSCPP_H

#include <memory>
#include <vector>

extern "C" {
#include "pslib.h"
}

namespace pscpp {

inline std::shared_ptr<DiskUsage> disk_usage(const char* path) {
    if (nullptr == path) {
        return nullptr;
    }

    auto usage = std::shared_ptr<DiskUsage>(new (std::nothrow) DiskUsage,
                                            [](DiskUsage* v) {
                                                if (nullptr != v)
                                                    delete v;
                                            });
    if (nullptr == usage) {
        return nullptr;
    }
    if (!::disk_usage(path, usage.get())) {
        return nullptr;
    }

    return usage;
}

inline std::shared_ptr<DiskPartitionInfo> disk_partitions(bool physical) {
    auto usage = std::shared_ptr<DiskPartitionInfo>(
        ::disk_partitions(physical), [](DiskPartitionInfo* v) {
            if (nullptr != v)
                ::free_disk_partition_info(v);
        });
    return usage;
}

inline std::shared_ptr<DiskIOCounterInfo> disk_io_counters() {
    auto usage = std::shared_ptr<DiskIOCounterInfo>(
        ::disk_io_counters(), [](DiskIOCounterInfo* v) {
            if (nullptr != v)
                ::free_disk_io_counter_info(v);
        });

    return usage;
}

inline std::shared_ptr<NetIOCounterInfo> net_io_counters() {
    auto usage = std::shared_ptr<NetIOCounterInfo>(
        ::net_io_counters(), [](NetIOCounterInfo* v) {
            if (nullptr != v)
                ::free_net_io_counter_info(v);
        });

    return usage;
}

inline std::shared_ptr<UsersInfo> get_users() {
    auto usage = std::shared_ptr<UsersInfo>(::get_users(), [](UsersInfo* v) {
        if (nullptr != v)
            ::free_users_info(v);
    });

    return usage;
}

inline uint32_t get_boot_time() {
    return ::get_boot_time();
}

inline std::shared_ptr<VmemInfo> virtual_memory() {
    auto info = std::make_shared<VmemInfo>();
    if (nullptr == info) {
        return info;
    }

    if (!::virtual_memory(info.get())) {
        return info;
    }

    return info;
}

inline std::shared_ptr<SwapMemInfo> swap_memory() {
    auto info = std::make_shared<SwapMemInfo>();
    if (nullptr == info) {
        return nullptr;
    }

    if (!::swap_memory(info.get())) {
        return nullptr;
    }

    return info;
}

// bug
inline std::shared_ptr<CpuTime> cpu_times_all() {
    auto rate = std::shared_ptr<CpuTime>(::cpu_times(false), [](CpuTime* v) {
        if (nullptr != v)
            free(v);
    });

    return rate;
}

// bug
inline std::shared_ptr<CpuTime> cpu_times_percpu() {
    auto rate = std::shared_ptr<CpuTime>(::cpu_times(true), [](CpuTime* v) {
        if (nullptr != v)
            free(v);
    });

    return rate;
}

// bug
inline std::shared_ptr<CpuTime> cpu_times_percent_all(
    std::shared_ptr<CpuTime> prev_times) {
    auto percent = std::shared_ptr<CpuTime>(
        ::cpu_times_percent(false, prev_times.get()), [](CpuTime* v) {
            if (nullptr != v)
                free(v);
        });

    return percent;
}

// bug
inline std::shared_ptr<CpuTime> cpu_times_percent_percpu(
    std::shared_ptr<CpuTime> prev_times) {
    auto percent = std::shared_ptr<CpuTime>(
        ::cpu_times_percent(true, prev_times.get()), [](CpuTime* v) {
            if (nullptr != v)
                free(v);
        });

    return percent;
}

// bug
inline double cpu_util_percent_all(std::shared_ptr<CpuTime> prev_times) {
    auto percent_ptr = std::shared_ptr<double>(
        ::cpu_util_percent(false, prev_times.get()), [](double* v) {
            if (nullptr != v)
                free(v);
        });

    return (nullptr != percent_ptr ? *percent_ptr : 0.0);
}

// bug
inline double cpu_util_percent_percpu(std::shared_ptr<CpuTime> prev_times) {
    auto percent_ptr = std::shared_ptr<double>(
        ::cpu_util_percent(false, prev_times.get()), [](double* v) {
            if (nullptr != v)
                free(v);
        });

    return (nullptr != percent_ptr ? *percent_ptr : 0.0);
}

inline uint32_t cpu_count(bool logical) {
    return ::cpu_count(logical);
}

inline bool pid_exists(pid_t pid) {
    return ::pid_exists(pid);
}

inline std::shared_ptr<Process> get_process(pid_t pid) {
    auto p = std::shared_ptr<Process>(::get_process(pid), [](Process* v) {
        if (nullptr != v) {
            ::free_process(v);
        }
    });
    return p;
}

inline double process_cpu_util_percent(pid_t pid) {
    return ::process_cpu_util_percent(pid);
}

inline std::shared_ptr<ProcessMemInfo> process_memory(pid_t pid) {
    auto memory_info = std::make_shared<ProcessMemInfo>();
    if (nullptr == memory_info) {
        return nullptr;
    }

    if (!process_memory(pid, memory_info.get())) {
        return nullptr;
    }

    return memory_info;
}

namespace extension {
struct ProcessDetails {
    std::shared_ptr<Process> self; // 自身信息
    std::vector<std::shared_ptr<Process>> threads; // 线程信息
};

/**
 * @brief get_process_details 获取当前进程详细信息，其中包括县城
 * @param pid
 * @return
 */
std::shared_ptr<ProcessDetails> get_process_details(pid_t pid) {
    return nullptr;
}

/**
 * @brief get_process_list
 * @return
 */
std::vector<std::shared_ptr<Process>> get_process_list() {
    std::vector<std::shared_ptr<Process>> process_list;

    return process_list;
}

} // namespace extension

}; // namespace pscpp

#endif // PSCPP_H
