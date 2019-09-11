#ifndef __ASM_IRQ_H
#define __ASM_IRQ_H

#define IRQ_STACK_SIZE			THREAD_SIZE
#define IRQ_STACK_START_SP		THREAD_START_SP

#ifndef __ASSEMBLER__

#include <linux/percpu.h>
#include <linux/sched.h>

#include <asm-generic/irq.h>
#include <asm/thread_info.h>

struct pt_regs;

DECLARE_PER_CPU(unsigned long [IRQ_STACK_SIZE/sizeof(long)], irq_stack);

extern void set_handle_irq(void (*handle_irq)(struct pt_regs *));

static inline int nr_legacy_irqs(void)
{
	return 0;
}

void arch_trigger_all_cpu_backtrace(void);
#define arch_trigger_all_cpu_backtrace arch_trigger_all_cpu_backtrace

static inline bool on_irq_stack(unsigned long sp)
{
	unsigned long low = (unsigned long)raw_cpu_ptr(irq_stack);
	unsigned long high = low + IRQ_STACK_START_SP;

	return (low <= sp && sp <= high);
}

static inline bool on_task_stack(struct task_struct *tsk, unsigned long sp)
{
	unsigned long low = (unsigned long)task_stack_page(tsk);
	unsigned long high = low + THREAD_SIZE;

	return (low <= sp && sp < high);
}

#endif /* !__ASSEMBLER__ */
#endif
