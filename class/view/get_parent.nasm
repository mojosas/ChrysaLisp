%include 'inc/func.inc'
%include 'class/class_view.inc'

	fn_function class/view/get_parent
		;inputs
		;r0 = view object
		;outputs
		;r0 = view object
		;r1 = parent

		vp_cpy [r0 + view_parent], r1
		vp_ret

	fn_function_end