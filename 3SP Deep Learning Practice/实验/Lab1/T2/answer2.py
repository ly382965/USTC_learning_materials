import requests
from bs4 import BeautifulSoup
import os
import cv2
import matplotlib.pyplot as plt

# 创建保存图片的目录
if not os.path.exists('images'):
    os.makedirs('images')

# 下载图片的函数
def download_img(url, path):
    try:
        response = requests.get(url)
        img = response.content
        with open(path, 'wb') as f:
            f.write(img)
        return True
    except Exception as ex:
        print(f"Error downloading {url}: {ex}")
        return False

# 获取网页内容
url = 'https://www.bizhizu.cn/manhua/katong/'
headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/55.0.2883.87 Safari/537.36'}
response = requests.get(url, headers=headers)
html_doc = response.content

# 解析网页内容
soup = BeautifulSoup(html_doc, 'html.parser')

# 提取所有图片链接
img_tags = soup.find_all('img')
img_urls = [img['src'] for img in img_tags if img.get('src')]

# 下载所有图片
for i, img_url in enumerate(img_urls):
    img_name = f"images/img_{i}.jpg"
    if download_img(img_url, img_name):
        print(f"Downloaded {img_url} to {img_name}")

# 显示其中一张图片
img_path = 'images/img_0.jpg'
img = cv2.imread(img_path)
img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
plt.imshow(img_rgb)
plt.axis('off')
plt.show()