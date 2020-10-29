v_0 = int(input())
x_0 = int(input())
t = int(input())

a = 9.8
c = a*t*t / 2
b = 1/2 * a*t*t

x_t = x_0 + v_0*t - a*t*t / 2

print(c,b)
print(x_t)
i = input()