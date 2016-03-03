%ifndef CLASS_OBJ_1234
    %define CLASS_OBJ_1234

%include 'inc/func.inc'

    %assign _map_null_size 0

    %macro vtable_emit 1
        ;%1 = <class name>
        %assign %%_n 0
        %rep _map_%[%1]_size
			fn_jmp _map_%[%1]_func_%[%%_n]
            %assign %%_n %%_n + 1
        %endrep
    %endmacro

    %macro map_copy 2
        ;%1 = <source class name>
        ;%2 = <dest class name>
        %assign %%_n 0
        %rep _map_%[%1]_size
            %define _map_%[%2]_name_%[%%_n] _map_%[%1]_name_%[%%_n]
            %define _map_%[%2]_func_%[%%_n] _map_%[%1]_func_%[%%_n]
            %assign %%_n %%_n + 1
        %endrep
        %assign _map_%[%2]_size _map_%[%1]_size
    %endmacro

	%macro def_class 2
        ;%1 = <class name>
        ;%2 = <super class name>
        map_copy %2, %1
		%define _class_ %1
		%define _super_class_%[%1] %2
    %endmacro

    %macro def_method 2-3 declare
        ;%1 = <member name>
        ;%2 = <member function>
		;%3 = mode (declare/override)
        %assign %%_n 0
        %rep _map_%[_class_]_size
            %ifidn _map_%[_class_]_name_%[%%_n], %1
                %exitrep
            %else
                %assign %%_n %%_n + 1
            %endif
        %endrep
        %if %%_n = _map_%[_class_]_size
            ;new method
			%ifidn %3, declare
				%assign _map_%[_class_]_size %%_n + 1
				%define _map_%[_class_]_name_%[%%_n] %1
				%define _map_%[_class_]_func_%[%%_n] %2
			%elifidn %3, override
				%fatal Method %1 does not exist, use declare ?
			%else
				%fatal Must use declare or override !
			%endif
        %else
            ;existing method
			%ifidn %3, declare
            	%fatal Method %1 allready exists, use override ?
			%elifidn %3, override
				;existing method
	            %define _map_%[_class_]_name_%[%%_n] %1
	            %define _map_%[_class_]_func_%[%%_n] %2
			%else
				%fatal Must use declare or override !
			%endif
        %endif
    %endmacro

    %macro method_call 2
        ;%1 = <class name>
        ;%2 = <member name>
        %assign %%_n 0
        %rep _map_%[%1]_size
            %ifidn _map_%[%1]_name_%[%%_n], %2
                %exitrep
            %else
                %assign %%_n %%_n + 1
            %endif
        %endrep
        %if %%_n = _map_%[%1]_size
            ;no such method
            %fatal No such method %2
        %else
            vp_cpy [r0 + obj_vtable], r15
			vp_call [r15 + (%%_n * 6)]
        %endif
    %endmacro

    %macro class_call 2
        ;%1 = <class name>
        ;%2 = <member name>
        %assign %%_n 0
        %rep _map_%[%1]_size
            %ifidn _map_%[%1]_name_%[%%_n], %2
                %exitrep
            %else
                %assign %%_n %%_n + 1
            %endif
        %endrep
        %if %%_n = _map_%[%1]_size
            ;no such method
            %fatal No such method %2
        %else
            fn_call _map_%[%1]_func_%[%%_n]
        %endif
    %endmacro

	%macro super_call 2
		;%1 = <class name>
        ;%2 = <member name>
		class_call _super_class_%[%1], %2
    %endmacro

    def_class obj, null
    def_method create, class/obj/create
    def_method destroy, class/obj/destroy
    def_method new, class/obj/new
    def_method delete, sys/mem_free
    def_method init, class/obj/init
    def_method deinit, class/obj/deinit

	struc obj
		obj_vtable:		resq 1
	endstruc

%endif