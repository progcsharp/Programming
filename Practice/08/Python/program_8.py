a,z,b = input().split()
s = 0
if z == "+":
	s = int(a) + int(b)
elif z == "-":
	s = int(a) - int(b)
elif z == "*":
	s = int(a) * int(b)
elif z == "/":
	s = int(a) / int(b)	
print(s)	