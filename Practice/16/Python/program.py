n = int(input())

s = input()
x = 0
for i in range(0,n+1):
	st = s[0+(10*i):9 + (10*i)]
	if st[0:1] == "a" and st[4:9] == "55661":
		print(st)
		x = 1
if x == 0:
	print("-1")