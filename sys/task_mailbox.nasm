%include 'inc/func.inc'
%include 'inc/task.inc'

	fn_function sys/task_mailbox, no_debug_enter
		;outputs
		;r0, r1 = current task mailbox id

		static_bind task, statics, r0
		vp_cpy [r0 + tk_statics_current_tcb], r0
		vp_cpy [r0 + tk_statics_cpu_id], r1
		vp_add tk_node_mailbox, r0
		vp_ret

	fn_function_end