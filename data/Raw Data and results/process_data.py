with open('resultados pokemon atacando','r') as atk:
	atk_str = atk.read()
with open('resultados pokemon defensor','r') as defn:
	def_str = defn.read()
with open('tipos orden','r') as t:
	tipos = t.read()

def_d = {}
atk_d = {}
for i,t in enumerate(tipos.split('\n')):
	if i!='':
		try:
			at = atk_str.split('\n')[i]
			de = def_str.split('\n')[i]
			def_d[t] = float(de.strip())    
			atk_d[t] = float(at.strip())
		except:
			print("%s %s %s" %(i, at, de))

for k in def_d:
	if k !='':
		print("%s,%s,%s\n"%(k, def_d[k],atk_d[k]))

print('--- top defenders ---')
def_items = list(def_d.items())
def_items.sort(key = lambda x : x[1])
for k, v in def_items:
	print("%s: %.3f" % (k,v))

print('--- top attackers ---')
atk_items = list(atk_d.items())
atk_items.sort(key = lambda x : x[1])
for k, v in def_items:
	print("%s: %.3f" % (k,v))
