/**
 * @author zouxiaoliang
 * @date 2021/7/29
 */
#ifndef CPS_PROC_KEYS_H
static const char* status_reserved[] = {"Name",
                                        "Umask",
                                        "State",
                                        "Tgid",
                                        "Ngid",
                                        "Pid",
                                        "PPid",
                                        "TracerPid",
                                        "Uid",
                                        "Gid",
                                        "FDSize",
                                        "Groups",
                                        "NStgid",
                                        "NSpid",
                                        "NSpgid",
                                        "NSsid",
                                        "VmPeak",
                                        "VmSize",
                                        "VmLck",
                                        "VmPin",
                                        "VmHWM",
                                        "VmRSS",
                                        "RssAnon",
                                        "RssFile",
                                        "RssShmem",
                                        "VmData",
                                        "VmStk",
                                        "VmExe",
                                        "VmLib",
                                        "VmPTE",
                                        "VmSwap",
                                        "HugetlbPages",
                                        "CoreDumping",
                                        "THP_enabled",
                                        "Threads",
                                        "SigQ",
                                        "SigPnd",
                                        "ShdPnd",
                                        "SigBlk",
                                        "SigIgn",
                                        "SigCgt",
                                        "CapInh",
                                        "CapPrm",
                                        "CapEff",
                                        "CapBnd",
                                        "CapAmb",
                                        "NoNewPrivs",
                                        "Seccomp",
                                        "Speculation_Store_Bypass",
                                        "Cpus_allowed",
                                        "Cpus_allowed_list",
                                        "Mems_allowed",
                                        "Mems_allowed_list",
                                        "SpeculationIndirectBranch",
                                        "voluntary_ctxt_switches",
                                        "nonvoluntary_ctxt_switches"};
#define CPS_PROC_KEYS_H

#endif // CPS_PROC_KEYS_H
