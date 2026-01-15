#环境：python2.x/python3.x；机器：不限定；代码编辑工具：不限定；A103机器ubuntu密码：123456；注意：A103机器重启后还原。
#把代码跑起来
#阅读代码，了解每个函数的功能。
#完成文件最后的本次课程作业，并提交给助教检查登记。

# 1、文件操作
f = open("test.txt", "w")
for i in range(10):
    f.write("Good Afternoon!")
    f.writelines(["Hello, world!\n", "Very happy\n"])
f.close()

f = open("test.txt", "r")
content = f.read()
print(content)
f.close()

with open("test.txt", "r") as f:
    content = f.read()
    print(content)


# 2、Get Request 1
# Get the informatoin of Stock SH002230
import requests
import json

url = 'https://stock.xueqiu.com/v5/stock/realtime/quotec.json?symbol=SH601003'
headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko)\
Chrome/55.0.2883.87 Safari/537.36'}
r = requests.get(url, headers = headers)
print(r.text)

# Status Code
print(r.status_code)
# The type of response
print(type(r.text))


# Use json to parse
hjson = json.loads(r.text)

# Type of hjson
type(hjson)
hjson

js = json.dumps(hjson, sort_keys=True, indent=4, separators=(',', ';'), ensure_ascii=False)
print(js)


# 3、Download images
import requests

def download_img(url_info):
    if url_info[1]:
        print("-----------downloading image %s"%(url_info[0]))
        try:
            url = url_info[0]
            response = requests.get(url)
            img = response.content
            
            # Save Path
            path='%s' % (url_info[1])
            with open(path, 'wb') as f:
                f.write(img)
            return (True, path)
        except Exception as ex:
            print("--------Error----")
            pass

download_img(['https://www.ustc.edu.cn/images/19/08/05/1bv2xhbf6r/img02.jpg','USTC.jpg'])

import cv2
import matplotlib.pyplot as plt
#matplotlib inline

img = cv2.imread('USTC.jpg')
img2= cv2.cvtColor(img,cv2.COLOR_BGR2RGB)
plt.imshow(img2)
plt.show()

# 4、Post Request 1

url = 'http://httpbin.org/post?a=b'
d = {'key1': 'value1', 'key2': 'value2'}
r = requests.post(url, data=d)
print(r.text)

# 5、BeautifulSoup
# 5.1、Example from offical tutorial

#https://www.crummy.com/software/BeautifulSoup/bs4/doc.zh/

html_doc = """
<html><head><title>The Dormouse's story</title></head>
<body>
<p class="title"><b>The Dormouse's story</b></p>

<p class="story">Once upon a time there were three little sisters; and their names were
<a href="http://example.com/elsie" class="sister" id="link1">Elsie</a>,
<a href="http://example.com/lacie" class="sister" id="link2">Lacie</a> and
<a href="http://example.com/tillie" class="sister" id="link3">Tillie</a>;
and they lived at the bottom of a well.</p>

<p class="story">...</p>
"""


from bs4 import BeautifulSoup
soup = BeautifulSoup(html_doc)

print(soup.prettify())

soup.title

soup.title.name

soup.title.string

soup.title.parent.parent.name

soup.p

soup.p['class']

soup.a

soup.find_all('a')

soup.find(id="link3")

for link in soup.find_all('a'):
    print(link.get('href'))

print(soup.get_text())


# 5.2、Get all the cities
import requests
from bs4 import BeautifulSoup

url = 'http://tianqi.moji.com/pm/china/anhui'
headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko)\
Chrome/55.0.2883.87 Safari/537.36'}

bs = BeautifulSoup(requests.get(url).content)
alphabet = bs.find(name = 'div', attrs={"class":'city_hot'})
#print(alphabet)
cities = dict()
for item in alphabet.find_all('a'):
    alphabet_name = str(item['href']).split(r'/')[-1]
    alphabet_name = filter(lambda ch: ch.isalpha() or ch.isdigit() or ch == '-', alphabet_name) 
    alphabet_name = ''.join(alphabet_name)
    zh_name = item.text
    print(alphabet_name, zh_name)
    cities[alphabet_name] = zh_name


# 6、Sqlite3

import sqlite3

# Connect a database and create a table
conn = sqlite3.connect('cities2.db')
print("Opened database successfully")
c = conn.cursor()
c.execute('CREATE TABLE CITIES(ID INT PRIMARY KEY     NOT NULL,EN_NAME        TEXT    NOT NULL,ZH_NAME        TEXT    NOT NULL);')
print("Cities Table Created!")
conn.commit()
conn.close()

# Show tables
conn = sqlite3.connect('cities2.db')
c = conn.cursor()
c.execute("select name from sqlite_master where type='table' order by name;")
print(c.fetchall())
conn.commit()

# Show table structure
c.execute("PRAGMA table_info(CITIES)")
print(c.fetchall())
conn.commit()
conn.close()

# Insert data
conn = sqlite3.connect('cities2.db')
c = conn.cursor()

# make sure you already have the dict CITIES in the memory
for i, k in enumerate(cities):
    sql = "INSERT INTO CITIES (ID,EN_NAME,ZH_NAME) \
      VALUES (%d, '%s', '%s');" % (i, k, cities[k])
    print(sql)
    c.execute(sql)

conn.commit()
print("Records created successfully")
conn.close()

# show data
conn = sqlite3.connect('cities2.db')
c = conn.cursor()
c.execute("select * from CITIES;")
data = c.fetchall()
conn.commit()
conn.close()

for item in data:
    print(item)




#课堂作业1：# Download USTC News on the frontpage
#课堂作业2：将'https://www.bizhizu.cn/manhua/katong/'此网址上所有的图片下载下来，保存在本目录（使用BeautifulSoup实现），并用matplotlib显示其中至少一张图片。
#课堂作业3：从示例“6、Sqlite3“， 找出hefei，输出对应的：“ID,EN_NAME,ZH_NAME”
