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