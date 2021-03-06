(import 'inc/class.inc)
(import 'inc/code.inc)
(import 'inc/list.inc)
(import 'inc/mail.inc)

(def-class 'sys_link)
(def-method 'statics 'sys/link_statics)
(def-method 'init 'sys/link_init)
(def-method 'link 'sys/link)

;;;;;;;;;;;;;;;;;
; link structures
;;;;;;;;;;;;;;;;;

(def-enum 'lk_chan_status)
	(enum 'ready 'busy)
(def-enum-end)

(def-struct 'lk_table)
	(ptr 'array)
	(ulong 'array_size)
(def-struct-end)

(def-struct 'lk_node 'ln_node)
	(struct 'table 'lk_table)
	(ulong 'cpu_id)
	(ulong 'task_count)
(def-struct-end)

(def-struct 'lk_statics)
	(struct 'links_list 'lh_list)
(def-struct-end)

(def-struct 'lk_chan)
	(ulong 'status)
	(ulong 'task_count)
	(struct 'msg 'msg)
(def-struct-end)

(def-struct 'lk_buffer)
	(struct 'chan_1 'lk_chan)
	(struct 'chan_2 'lk_chan)
(def-struct-end)

(def-struct 'lk_route)
	(ulong 'hops)
(def-struct-end)
