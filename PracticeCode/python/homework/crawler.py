#coding=utf-8
import requests,re
from bs4 import BeautifulSoup
import collections # 词频统计库 
import numpy as np # numpy数据处理库 
import wordcloud # 词云展示库 
from PIL import Image # 图像处理库 
headers = {
    'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9',
    'Accept-Encoding': 'gzip, deflate',
    'Accept-Language': 'zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6',
    'Cache-Control': 'max-age=0',
    'Connection': 'keep-alive',
    'Content-Length': '122',
    'Content-Type': 'application/x-www-form-urlencoded',
    'Cookie': 'csrftoken=OoBameoPUOmEY5uzWOp81aQUn1pwEJWD',
    'Host': '1.117.204.48:8000',
    'Origin': 'http://1.117.204.48:8000',
    'Referer': 'http://1.117.204.48:8000/squery/login/',
    'Upgrade-Insecure-Requests': '1',
    'User-Agent': 'Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/107.0.0.0 Mobile Safari/537.36 Edg/107.0.1418.56'
}
data = {'csrfmiddlewaretoken': '4QNAavgXV0BguPzRPqtupjWEG4EnbB2BI4eAmzuCFENKiKTgB4IsgjCoTVTJFaO4',
'sid':'09021102',  # 学号
'login':'提交'
}
url = "http://1.117.204.48:8000/squery/login/"
r = requests.post(url,headers=headers,data=data)
target = r.text[18:-2].replace("'","").replace(" ","").split(',') # 处理字符串，将目标老师存入列表
#################################################################################
targetLink = {}  # 存储目标教师的个人主页超链接
headers = {
    'authority': 'cse.seu.edu.cn',
    'method': 'GET',
    'path': '/22623/list.htm',
    'scheme': 'https',
    'accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9',
    'accept-encoding': 'gzip, deflate, br',
    'accept-language': 'zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6',
    'cache-control': 'max-age=0',
    'cookie': 'zg_8da79c30992d48dfaf63d538e31b0b27=%7B%22sid%22%3A%201657090500004%2C%22updated%22%3A%201657090500004%2C%22info%22%3A%201657090500006%2C%22superProperty%22%3A%20%22%7B%7D%22%2C%22platform%22%3A%20%22%7B%7D%22%2C%22utm%22%3A%20%22%7B%7D%22%2C%22referrerDomain%22%3A%20%22%22%7D; zg_did=%7B%22did%22%3A%20%2217fa9e7dfab84c-075536baac82be-5617185b-144000-17fa9e7dface44%22%7D; zg_=%7B%22sid%22%3A%201664509876883%2C%22updated%22%3A%201664509876889%2C%22info%22%3A%201664509876887%2C%22superProperty%22%3A%20%22%7B%7D%22%2C%22platform%22%3A%20%22%7B%7D%22%2C%22utm%22%3A%20%22%7B%7D%22%2C%22referrerDomain%22%3A%20%22%22%2C%22cuid%22%3A%20%22213213446%22%2C%22zs%22%3A%200%2C%22sc%22%3A%200%2C%22firstScreen%22%3A%201664509876883%7D; NSC_xfcqmvt-05-iuuqt=ffffffff0948651e45525d5f4f58455e445a4a423660; JSESSIONID=24AC6BCCD628C85FAC4C2F49C6AEF704',
    'sec-ch-ua': '"Microsoft Edge";v="107", "Chromium";v="107", "Not=A?Brand";v="24"',
    'sec-ch-ua-mobile': '?1',
    'sec-ch-ua-platform': "Android",
    'sec-fetch-dest': 'document',
    'sec-fetch-mode': 'navigate',
    'sec-fetch-site': 'none',
    'sec-fetch-user': '?1',
    'upgrade-insecure-requests': '1',
    'user-agent': 'Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/107.0.0.0 Mobile Safari/537.36 Edg/107.0.1418.56'
}
url = 'https://cse.seu.edu.cn/22623/list.htm'
r = requests.get(url,headers=headers)
soup = BeautifulSoup(r.text,"html.parser")

for tag in soup('a'):
    try:
        name = tag["sudyfile-attr"][10:-2] # 提取姓名
        name = re.sub("\(.*\)","",name)  # 去除职位
        if name in target:
            targetLink[name] = tag["href"]  # 存储目标教师的个人主页超链接
    except KeyError:    # 非教师标签没有此key，会提前终止影响程序运行
        pass
#################################################################################
from lxml import etree
content = ""
i = 0
path = ['/html/body/div/div/div/div/div/article/p[5]/span[1]/text()','/html/body/div/div/div/div/div/article/p[2]/span/text()','/html/body/div/div/div/div/div/article/div/p[2]/span[1]/text()','/html/body/div/div/div/div/div/article/p[20]/span[17]/text()']
for key,value in targetLink.items():
    headers["path"] = value.replace("http://cse.seu.edu.cn/","")
    r = requests.get(value,headers=headers)
    select = etree.HTML(r.text)
    content += "".join(select.xpath(path[i]))
    i += 1

# 词频统计 
word_counts = collections.Counter(content) # 对分词做词频统计 
word_counts_top10 = word_counts.most_common(10) # 获取前10最高频的词 

# 词频展示 
mask = np.array(Image.open('redstar.jpg')) # 定义词频背景 
wc = wordcloud.WordCloud( 
	background_color='white', 
	font_path='C:/Windows/Fonts/simhei.ttf', # 设置字体格式 
	mask=mask, # 设置背景图 
	max_words=200, # 最多显示词数 
	max_font_size=100 # 字体最大值 
)
# 从字典生成词云 
wc.generate_from_frequencies(word_counts) 
# 从背景图建立颜色方案 
image_colors = wordcloud.ImageColorGenerator(mask) 
# 将词云颜色设置为背景图方案
wc.recolor(color_func=image_colors) 
wc.to_file('words.jpg')



