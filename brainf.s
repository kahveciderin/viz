JMP#NN . .program_start
:string_read
PSH#CN . .
MOV#NB . .
:_read_loop
MOV#NC . .
INP#NC . .
SUB#CN . 003B
JOZ#CN . ._str_read_end
ADD#CN . 000a
SET#CA . .
ADD#AN . 0002
ADD#BN . 0002
JMP#NN . ._read_loop
:_str_read_end
POP#NC . .
RET#NN . .
# --END STRING_READ--
:program_start
MOV#NA .brainf_program_data .
CAL#NN . .string_read
# b now set to brainf program end
# 005b = [
# 005d = ]
# y is pair list length
ADD#BA . .
MOV#NY .parentheses_pairs .
:_brainf_paren_parse_loop

GET#AX . .
SUB#XN . 005b
JOZ#XN . ._brainf_open_bracket_branch
SUB#XN . 0002
JOZ#XN . ._brainf_close_bracket_branch
JMP#NN . ._brainf_nonparse_char_branch
:_brainf_open_bracket_branch
PSH#AN . .
JMP#NN . ._brainf_nonparse_char_branch
:_brainf_close_bracket_branch
POP#NX . .
SET#XY . .
ADD#YN . 0002
SET#AY . .
ADD#YN . 0002
:_brainf_nonparse_char_branch
ADD#AN . 0002
# check if c equal to b
XOR#AB . .
JOZ#AN . ._brainf_execute_loop_init
XOR#AB . .
JMP#NN . ._brainf_paren_parse_loop
:_brainf_execute_loop_init
MOV#NA .brainf_program_tape .
MOV#NX .brainf_program_data .
:_brainf_execute_loop
# y equals the top of the pairs list
# x is program pointer
# b is end of program_data
# a is tape pointer
# use z as character read register
# 002b = +
# 002c = ,
# 002d = -
# 002e = .
# 003c = <
# 003e = >
# 005b = [
# 005d = ]
GET#XZ . .
XOR#ZN . 002B
JOZ#ZN . ._brainf_exec_plus
XOR#ZN . 0007
JOZ#ZN . ._brainf_exec_comma
XOR#ZN . 0001
JOZ#ZN . ._brainf_exec_minus
XOR#ZN . 0003
JOZ#ZN . ._brainf_exec_dot
XOR#ZN . 0012
JOZ#ZN . ._brainf_exec_st
XOR#ZN . 0002
JOZ#ZN . ._brainf_exec_gt
XOR#ZN . 0065
JOZ#ZN . ._brainf_exec_bropen
XOR#ZN . 0006
JOZ#ZN . ._brainf_exec_brclose
JMP#NN . ._brainf_exec_noop

:_brainf_exec_plus
GET#AZ . .
ADD#ZN . 0001
SET#ZA . .
JMP#NN . ._brainf_exec_noop

:_brainf_exec_minus
GET#AZ . .
SUB#ZN . 0001
SET#ZA . .
JMP#NN . ._brainf_exec_noop

:_brainf_exec_comma
INP#NZ . .
SET#ZA . .
JMP#NN . ._brainf_exec_noop

:_brainf_exec_dot
GET#AZ . .
OUT#ZN . .
JMP#NN . ._brainf_exec_noop

:_brainf_exec_st
SUB#AN . 0001
JMP#NN . ._brainf_exec_noop

:_brainf_exec_gt
ADD#AN . 0001
JMP#NN . ._brainf_exec_noop

:_brainf_exec_bropen
MOV#NZ .parentheses_pairs .
:_brainf_bropen_search_loop
GET#ZH . .
XOR#HX . .
JOZ#HN . ._brainf_bropen_found
ADD#ZN . 0004
XOR#ZY . .
JOZ#ZN . ._brainf_bropen_not_found
XOR#ZY . .
JMP#NN . ._brainf_bropen_search_loop
:_brainf_bropen_found
ADD#ZN . 0002
GET#AH . .
JNZ#AN . ._brainf_exec_noop
GET#ZX . .
JMP#NN . ._brainf_exec_noop

:_brainf_exec_brclose
MOV#NZ .parentheses_pairs .
ADD#ZN . 0002
:_brainf_bropen_search_loop
GET#ZH . .
XOR#HX . .
JOZ#HN . ._brainf_bropen_found
ADD#ZN . 0004

SUB#ZY . .
SUB#ZN . 0002
JOZ#ZN . ._brainf_bropen_not_found
ADD#ZY . .
ADD#ZN . 0002

JMP#NN . ._brainf_bropen_search_loop
:_brainf_bropen_found
SUB#ZN . 0002
GET#AH . .
JOZ#AN . ._brainf_exec_noop
GET#ZX . .
JMP#NN . ._brainf_exec_noop
:_brainf_bropen_not_found
HLT#NN . .
:_brainf_exec_noop
# check if program has ended
ADD#XN . 0002
XOR#XB . .
JOZ#XN . ._brainf_end
XOR#XB . .
JMP#NN . ._brainf_execute_loop
:_brainf_end
HLT#NN . .
:brainf_program_data
@!0100
:parentheses_pairs
@!0040
:brainf_program_tape
@!0100