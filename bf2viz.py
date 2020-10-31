stack = []
loopcnt = 0
with open("bf.dat") as f:
  while True:
    c = f.read(1)
    if not c:
      print("#EOF")
      break
    if c == '<':
        print("SUB#AN . 0001");
    elif c == '>':
        print("ADD#AN . 0001");
    elif c == '.':
        print("OUT#Na . .");
    elif c == ',':
        print("INP#Na . .");
    elif c == '[':
        print(":label" + str(loopcnt));
        stack.append(loopcnt)
        loopcnt+=1
    elif c == ']':
        print("JNZ#aN . .label" + str(stack.pop()));
    elif c == '+':
        print("ADD#aN . 0001");
    elif c == '-':
        print("SUB#aN . 0001");
