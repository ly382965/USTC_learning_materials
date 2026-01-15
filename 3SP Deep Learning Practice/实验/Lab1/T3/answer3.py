import sqlite3

# 连接数据库
conn = sqlite3.connect('cities2.db')
print("Opened database successfully")
c = conn.cursor()

# 查找hefei
c.execute("SELECT ID, EN_NAME, ZH_NAME FROM CITIES WHERE EN_NAME = 'hefei';")#SQL语句
data = c.fetchone()
conn.commit()
conn.close()

# 输出结果
if data:
    print(f"ID: {data[0]}, EN_NAME: {data[1]}, ZH_NAME: {data[2]}")
else:
    print("No data found for 'hefei'")