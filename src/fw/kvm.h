#ifndef __KVM_H
#define __KVM_H

#define KVM_CPUID_SIGNATURE	0x40000000
#define KVM_CPUID_FEATURES	0x40000001
#define KVM_FEATURE_HARDEN		14
#define KVM_HC_HARDEN  12
/* TODO Make this the 0th */
#define KVM_HC_HARDEN_SMM_INIT 2

#define SMM_FEATURE_INIT	(1 << 0)

u32 kvm_features(void);

/* TODO AMD uses VMMCALL instaed of VMCALL */

#define _kvm_hypercall2(type, name, a1, a2)                             \
({                                                                      \
    long __res;                                                         \
    asm volatile (                                                      \
        "vmcall"                                                        \
        : "=a" (__res)                                                  \
        : "a" ((long)(name)), "b" ((long)(a1)), "c" ((long)(a2))        \
        : "memory" );                                                   \
    (type)__res;                                                        \
})

#endif
