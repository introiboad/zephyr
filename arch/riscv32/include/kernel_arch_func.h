/*
 * Copyright (c) 2016 Jean-Paul Etienne <fractalclone@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief Private kernel definitions
 *
 * This file contains private kernel function/macro definitions and various
 * other definitions for the RISCV32 processor architecture.
 */

#ifndef _kernel_arch_func__h_
#define _kernel_arch_func__h_

#include <soc.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE
void k_cpu_idle(void);
void k_cpu_atomic_idle(unsigned int key);

static ALWAYS_INLINE void kernel_arch_init(void)
{
	_kernel.irq_stack = _interrupt_stack + CONFIG_ISR_STACK_SIZE;
}

static ALWAYS_INLINE void
_set_thread_return_value(struct k_thread *thread, unsigned int value)
{
	thread->arch.swap_return_value = value;
}

static inline void _IntLibInit(void)
{
#if defined(CONFIG_RISCV_SOC_INTERRUPT_INIT)
	soc_interrupt_init();
#endif
}

FUNC_NORETURN void _NanoFatalErrorHandler(unsigned int reason,
					  const NANO_ESF *esf);


#define _is_in_isr() (_kernel.nested != 0)

#ifdef CONFIG_IRQ_OFFLOAD
int _irq_do_offload(void);
#endif

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* _kernel_arch_func__h_ */
