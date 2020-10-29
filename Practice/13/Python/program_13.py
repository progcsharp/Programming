i = int(input("n = "))
b = True
s = 2
while s*s <= i:
	if i % s == 0:
		b = False
		break
	else:
		s += 1	
if b:
	print("простое")
else:
	print("не простое")			