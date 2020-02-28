text = [1,0,0,0,4,0,0xffffff7c,0,0,0,0,0,0xfffffff9,0,0,0,0,0x22c4,3,0,0,0,0xffffffec,0,0x539,0]
valid_character = ''
for i,t in enumerate(text):
	if not t:
		valid_character += chr(i+65)
print valid_character