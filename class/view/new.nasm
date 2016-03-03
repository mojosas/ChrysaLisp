%include 'class/class_view.inc'

	fn_function class/view/new
		;outputs
		;r0 = 0 if error, else object
		;trashes
		;r1-r3

		;allocate new view object
		vp_cpy view_size, r0
		fn_call sys/mem_alloc
		if r0, !=, 0
			;clear object memory
			vp_cpy r0, r3
			vp_cpy view_size, r1
			fn_call sys/mem_clear
			vp_cpy r3, r0
		endif
		vp_ret

	fn_function_end