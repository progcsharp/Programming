import math

h ,m  = map(int,input().split())
h2 ,m2  = map(int,input().split())


if math.fabs(h - h2) < 2	:
	if h - h2 == 0 and math.fabs(m - m2) <= 15 :
		print("встреча состоится ")
	elif math.fabs(h - h2) == 1 and math.fabs(m - 60) + m2 <= 15 :
		print("встреча состоится ")
	else:
		print("встреча не состоится") 						

else:
	print("встреча не состоится") 			
