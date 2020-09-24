#dont use this its trash

opcodes = ["NOP", "ADD", "SUB", "MUL", "DIV", "CMP", "JMP", "GFX", "AND", "NOT", "OOR", "XOR", "INP", "OUT", "RSH", "LSH", "SET", "GET", "JOZ", "RND"]

print("switch(str2int(cmd.c_str())){")
a = 0
for code in opcodes:
	print("    case str2intc(\""+code+"\"):\n    data[0] = "+hex(a)+";\n    break;")
	a+=1
print("}")
