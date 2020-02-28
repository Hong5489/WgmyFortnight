import random
valid_character = list("BCDFHIJKLNOPQTUVXZ")
key = ''
for i in range(16):
	temp = random.choice(valid_character)
	key += temp
	valid_character.remove(temp)
	if (i+1) % 4 == 0:
		key += '-'
print key[:-1]