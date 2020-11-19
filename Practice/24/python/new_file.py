import json
#from array import *

l = list('')
usid = 1
k = 0
with open('in.json','r') as r:
	
	f = json.loads(r.read())
	for x in range(len(f)):

		if usid == f[x]['userId']:
			if f[x]['completed']:
				k += 1
		elif usid < f[x]['userId']:
			if f[x]['completed']:
				k += 1
			d = {
				'userId': usid,
				'task_completed': k
			}		
			l.append(d)
			k = 0
			
			print(x)
			usid += 1
	with open('output.json','w') as w:
		w = json.dump(l,w,indent=3)		