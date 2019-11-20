// KVM paravirtualization support
//
// Copyright (C) 2019 Intel Corperation.
//
// This file may be distributed under the terms of the GNU LGPLv3 license.

#include "config.h" // CONFIG_KVM
#include "output.h" // dprintf
#include "paravirt.h" // PlatformRunningOn
#include "string.h" // memcpy
#include "x86.h" // cpuid
#include "kvm.h" // KVM_CPUID_SIGNATURE

u32 kvm_features(void)
{
    u32 base = KVM_CPUID_SIGNATURE, eax, ebx, ecx, edx;
    char signature[13];

    if (!CONFIG_KVM)
        return 0;

    cpuid(base, &eax, &ebx, &ecx, &edx);
    memcpy(signature + 0, &ebx, 4);
    memcpy(signature + 4, &ecx, 4);
    memcpy(signature + 8, &edx, 4);
    signature[9] = 0;
    signature[10] = 0;
    signature[11] = 0;
    signature[12] = 0;

    if (strcmp(signature, "KVMKVMKVM") != 0) {
        dprintf(1, "No KVM hypervisor found.\n");
        return 0;
    }

    dprintf(1, "\nFound KVM hypervisor signature at %x\n", base);

    cpuid(KVM_CPUID_FEATURES, &eax, &ebx, &ecx, &edx);

    return eax;
}
