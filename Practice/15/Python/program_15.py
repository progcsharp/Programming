from random import randint
flag = True
while flag:
	
	print("{Приветственное сообщение от игры}")

	print("уорвень сложности от 1 до 3")

	i = int(input())
	r = 5
	if i == 1:
		b = randint(0,10)
	elif i == 2:
		b = randint(0,100)
	elif i == 3:
		b = randint(0,1000)	
		r = 10

	print("игра началась")
	for s in range(0,r):
		a = int(input())
		if a == b :
			print ("победил")
			break;
		elif a < b :
			print("нужно больше")
		elif a > b :
			print("поменьше")
	v = input("1-еще раз \n2-закончить\n")
	if v == "2" :
		flag = False		