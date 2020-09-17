opcodes = ["AND", "ADD", "GFX", "NOP", "CLS", "ORN", "NOT", "NOR", "SUB", "MUL", "DIV", "CMP", "JMP", "SQR", "DRW", "XOR"]

print("switch(str2int(cmd.c_str())){")
a = 0
for code in opcodes:
	print("    case str2intc(\""+code+"\"):\n    data[0] = "+hex(a)+";\n    break;")
	a+=1
print("}")
