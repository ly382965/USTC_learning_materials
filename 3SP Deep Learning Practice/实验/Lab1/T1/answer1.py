import requests
from bs4 import BeautifulSoup
import json

urls = ['https://news.ustc.edu.cn/xwbl.htm'] + [f'https://news.ustc.edu.cn/xwbl/{i}.htm' for i in range(455, 445, -1)]
for url in urls:
    headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/55.0.2883.87 Safari/537.36'}

    response = requests.get(url, headers=headers)
    html_doc = response.content

    soup = BeautifulSoup(html_doc, 'html.parser')

    # 提取所有新闻项
    news_items = soup.find_all('li', class_='row')

    news_data = []

    for item in news_items:
        link = item.find('a', class_='col-sm-9 col-xs-12').get('href')
        title_text = item.find('a', class_='col-sm-9 col-xs-12').get_text(strip=True)
        date_text = item.find('div', class_='date').get_text(strip=True)
        
        if link.startswith('../'):
            link = link.replace('../', '')
            
        news_data.append({
            'title': title_text,
            'link': "https://news.ustc.edu.cn/" + link,
            'date': date_text
        })

    # 保存结果到文件
    with open('news_data.json', 'a', encoding='utf-8') as file:
        json.dump(news_data, file, ensure_ascii=False, indent=4)

    # 打印结果
    for news in news_data:
        print(f"标题: {news['title']}")
        print(f"链接: {news['link']}")
        print(f"日期: {news['date']}")
        print()