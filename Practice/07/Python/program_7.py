import math


t = input("1-по сторонам \n 2-по координатам");

if t == "1":

	a = int(input())
	b = int(input())
	c = int(input())


	p = (a+b+c)/2

	s = math.sqrt(p*(p-a)*(p-b)*(p-c))
	print(s);
else:
	x1,y1 = map(int,input().split())
	x2,y2 = map(int,input().split())
	x3,y3 = map(int,input().split())

	s = 0.5 * math.fabs((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1))

	print(s)


y = input()	