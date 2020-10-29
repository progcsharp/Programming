import math

a = int(input())
b = int(input())
c = int(input())
 
#ax^2 +bx +c = 0

if a == 0:
	x = -c / b
	print(x)
else:

	#d = b^2 - 4 a c

	D = b*b - 4*a*c
	#x = -b +- d^1/2 /2a

	if D == 0 :
		x = -b / (2*a)
		print(x)
	elif D > 0 :
		x_0 = (-b + math.sqrt(D))/(2*a)
		x_1 = (-b - math.sqrt(D))/(2*a) 
		print(x_0,x_1)
	else :
		print('увы')
s = input()	