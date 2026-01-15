#第二次实验课程内容：
#环境：python2.x/python3.x；机器：不限定；代码编辑工具：不限定；A103机器ubuntu密码：123456；注意：A103机器重启后还原。
#把代码跑起来
#阅读代码，了解每个函数的功能。
#完成文件最后的本次课程作业，并提交给助教检查登记。

#强大的Numpy
'''
NumPy（Numerical Python）是Python中用于科学计算的基础库之一，它提供了多维数组对象以及一系列操作这些数组的函数。
NumPy数组比Python原生列表更加高效，尤其是在进行大量数学运算时。
要查看NumPy的官方文档，你可以访问以下网址：
https://numpy.org/devdocs/user/index.html
在这个网站上，你可以找到以下几种资源：
用户指南（User Guide）：这是最全面的文档，涵盖了NumPy的基础知识、高级功能和最佳实践。
参考指南（Reference Guide）：这部分提供了NumPy中所有函数的详细描述，包括每个函数的作用、参数、返回值等。
NumPy教程：提供了从基础到高级的一系列教程，适合不同水平的用户。
API文档：详细的API文档，按模块组织，方便查找特定功能。
常见问题解答（FAQ）：解答了使用NumPy时常见的问题。
NumPy发行说明（Release Notes）：记录了每个版本的更新和改进。
'''
import numpy as np

a = (5, 6, 7, 8)
b = np.array(a, dtype = np.uint8)#创建数组

print(b.size, b.shape, b.ndim, b.dtype)

array_zeros = np.zeros([4 , 4])#全0
array_ones = np.ones([5, 5]) * 255#np.ones 创建全1数组
array_eye = np.eye(5, dtype=np.uint8) * 7#返回一个二维的对角数组

print(array_zeros)
print(array_ones)
print(array_eye)

print(array_eye.dtype)

matrix = np.random.rand(5, 6)
print(matrix.size, matrix.shape, matrix.dtype, matrix.ndim)
print(matrix)

# 矩阵转置
matrixT = matrix.T
print(matrixT.size, matrixT.shape, matrixT.dtype)
print(matrixT)

sub_matrix = matrix[1:4, 2:4]#切片选择中间部分，注意数组下标0开始
print(sub_matrix)

ma = np.random.rand(3, 3)
mb = np.random.rand(3, 3)
print(ma)
print(mb)

# matrix operations
print("Shape:",ma.shape) # print the matrix shape
print("Shape:",mb.shape) # print the matrix shape
print("Sum:",ma+mb) # matrix sum
print("Elementwise multiplication:",ma*mb) # elementwise multiplication
print("Power of two:",ma**2) # power of two
print("Matrix multiplication:",ma.dot(mb)) # product
print("Minimum:",ma.min()) # minumum
print("Maximum:",mb.max()) # maximum
print("Sum:",mb.sum()) #sum 
print("Mean:",ma.mean()) # mean

print(ma.std())

#画图
'''
Matplotlib、Seaborn和Plotly是Python中常用的三个数据可视化库，它们各有特点和适用场景。‌


Matplotlib是Python数据可视化的基石库，提供了丰富的绘图函数和工具，能够创建各种类型的基本图表，如折线图、柱状图、散点图、饼图等。
其设计理念注重底层的绘图控制，灵活性高，适合需要高度定制化图表的需求。然而，这种灵活性也带来了复杂性，初学者需要花费时间学习和掌握其复杂的API‌

Seaborn构建在Matplotlib之上，专注于提供美观且具有统计信息丰富的可视化效果。
它简化了复杂的统计绘图任务，能够轻松绘制热图、小提琴图和蜂群图等复杂统计图表。
Seaborn还提供了大量的预设样式和主题，适合快速生成美观且易于理解的统计图表。然而，对于高度定制化的需求，Seaborn可能不如Matplotlib灵活‌

Plotly以其强大的交互性脱颖而出，支持创建动态图表和3D图形，特别适合探索多维数据集。
Plotly生成的图表可以嵌入到Web应用中，用户可以通过缩放、旋转和平移与数据进行互动。
此外，Plotly具有良好的兼容性，可以在多种平台上运行，包括Jupyter Notebook、Python脚本、Dash应用程序等。对于需要交互性和动态性的用户来说，Plotly是最佳选择‌
'''
import matplotlib.pyplot as plt

#折线图
year = [2011, 2012, 2013, 2014, 2015]
pop = [1.2, 3.5, 6.7, 8.0, 9.1]

plt.plot(year, pop, 'g--')
plt.show()

# 散点图
plt.scatter(year, pop, color='yellow')
plt.show()

# 直方图
values = [0,1,2,3,4,1,2,3,4,4,5,2,4,1]
# 直方图绘制函数，bins为直方图间隔份数
plt.hist(values,bins=10)
plt.show()

# 多个子图
def f(t):
    return np.exp(-t) * np.cos(2 * np.pi * t)

t1 = np.arange(0, 5, 0.1)
t2 = np.arange(0, 5, 0.02)

plt.figure(12)
plt.subplot(221)## 第一行的左图 ，其中各个参数也可以用逗号,分隔开。第一个参数代表子图的行数；第二个参数代表该行图像的列数； 第三个参数代表每行的第几个图像。
plt.plot(t1, f(t1), 'bo', t2, f(t2), 'r--')

plt.subplot(222)# 第一行的右图
plt.plot(t2, np.cos(2 * np.pi * t2), 'r--')

plt.subplot(212)# 第二整行 
plt.plot([1, 2, 3, 4], [1, 4, 9, 16])

plt.show()

import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
X = [1, 1, 2, 2]
Y = [3, 4, 4, 3]
Z = [1, 2, 1, 1]
ax.plot_trisurf(X, Y, Z)
plt.show()

# 画心
# Story:
# https://baijiahao.baidu.com/s?id=1606866687044231987&wfr=spider&for=pc
    
t = np.arange(0,2*np.pi, 0.1)
x = 16*np.sin(t)**3
y = 13*np.cos(t)-5*np.cos(2*t)-2*np.cos(3*t)-np.cos(4*t)#通过调整16和13等系数可改变爱心宽高比例。
plt.plot(x,y)
plt.show()


# Show an internet image

from PIL import Image
import matplotlib.pyplot as plt
from io import BytesIO
import urllib.request
 
# 网络图片URL
url = 'https://p0.ifengimg.com/ifeng/index/20150921/ifengLogo.png'
 
# 使用urllib下载图片
with urllib.request.urlopen(url) as response:
    image = Image.open(BytesIO(response.read()))
 
# 使用matplotlib显示图片
plt.imshow(image)
plt.axis('off')  # 不显示坐标轴
plt.show()



# Show me more beautiful graphs

# 需要用到的csv文件，参考https://www.machinelearningplus.com/plots/top-50-matplotlib-visualizations-the-master-plots-python/

# Histogram for Continuous Variable


# pandas
'''
Pandas是一个强大的Python库，用于数据分析和操作，特别是在处理表格数据（如CSV文件、Excel文件等）方面。
要访问Pandas的官方文档，你可以访问以下网址：
https://pandas.pydata.org/pandas-docs/stable/
'''
import pandas as pd
import numpy as np

df = pd.read_csv("mpg_ggplot2.csv")

# Prepare data
x_var = 'displ'
groupby_var = 'class'
df_agg = df.loc[:, [x_var, groupby_var]].groupby(groupby_var)
vals = [df[x_var].values.tolist() for i, df in df_agg]

# Draw连续变量堆积直方图（Stacked Histogram for Continuous Variable）该图展示给定连续变量的频率分布。
plt.figure(figsize=(16,9), dpi= 80)
colors = [plt.cm.Spectral(i/float(len(vals)-1)) for i in range(len(vals))]
n, bins, patches = plt.hist(vals, 30, stacked=True, density=False, color=colors[:len(vals)])

# Decoration
plt.legend({group:col for group, col in zip(np.unique(df[groupby_var]).tolist(), colors[:len(vals)])})
plt.title(f"Stacked Histogram of ${x_var}$ colored by ${groupby_var}$", fontsize=22)
plt.xlabel(x_var)
plt.ylabel("Frequency")
plt.ylim(0, 25)
# plt.xticks(ticks=bins[::3], labels=[round(b,1) for b in bins[::3]])
plt.show()



# Read data
import seaborn as sns

df = pd.read_csv("email_campaign_funnel.csv")

# Draw Plot 金字塔图，可以理解为一种排过序的分组水平柱状图barplot，可很好展示不同分组之间的差异，可可视化逐级过滤或者漏斗的每个阶段。
plt.figure(figsize=(13,10), dpi= 80)
group_col = 'Gender'
order_of_bars = df.Stage.unique()[::-1]
colors = [plt.cm.Spectral(i/float(len(df[group_col].unique())-1)) for i in range(len(df[group_col].unique()))]

for c, group in zip(colors, df[group_col].unique()):
    sns.barplot(x='Users', y='Stage', data=df.loc[df[group_col]==group, :], order=order_of_bars, color=c, label=group)

# Decorations    
plt.xlabel("$Users$")
plt.ylabel("Stage of Purchase")
plt.yticks(fontsize=12)
plt.title("Population Pyramid of the Marketing Funnel", fontsize=22)
plt.legend()
plt.show()



import plotly.express as px
df = px.data.gapminder()

fig = px.scatter(df.query("year==2007"), x="gdpPercap", y="lifeExp",
	         size="pop", color="continent",
                 hover_name="country", log_x=True, size_max=60)
fig.show()

import pandas as pd
quakes = pd.read_csv('earthquakes-23k.csv')

import plotly.graph_objects as go
fig = go.Figure(go.Densitymapbox(lat=quakes.Latitude, lon=quakes.Longitude, z=quakes.Magnitude,
                                 radius=10))
fig.update_layout(mapbox_style="stamen-terrain", mapbox_center_lon=180)
fig.update_layout(margin={"r":0,"t":0,"l":0,"b":0})
fig.show()


'''
Python Imaging Library（PIL）是一个功能丰富且易于使用的图像处理库。它提供了各种各样的图像操作功能，包括打开、保存、调整大小、旋转、滤镜应用等。
OpenCV是一个广泛使用的开源计算机视觉库，它提供了大量的图像处理和计算机视觉算法。

PIL提供了一些基本的图像处理功能，如调整大小、旋转、裁剪等。
它也支持一些简单的滤镜应用，如模糊、锐化等。
但在复杂的图像处理任务中，如特征检测、目标识别等，PIL的功能相对有限。

相比之下，OpenCV提供了更多的图像处理算法和功能，包括边缘检测、特征提取、模板匹配等.
'''
from PIL import Image

# load an image
im = Image.open('lena.png')
# Show the image ：PIL库不会弹出窗口显示图像，需要主动调用
im.show()

# rotate
print(im.format, im.size)
out = im.transpose(Image.ROTATE_90)
print(out.format, out.size)
out

# Resize
im_big = im.resize((400, 400))
print(im_big.format, im_big.size)
im_big

# split channels
r, g, b = im.split()
r

g

b

# merge 3 channels
im2 = Image.merge("RGB", [r, g, b])
im2

from PIL import ImageFilter
im3 = im.filter(ImageFilter.BLUR)
im3

# Get an Internet Image and show it
import requests

im = Image.open(requests.get("https://p0.ifengimg.com/ifeng/index/20150921/ifengLogo.png", stream=True).raw)
print(im.format, im.size)

out = im.transpose(Image.ROTATE_90)
out

#OpenCV
#!conda install opencv -c conda-forge
import cv2
import matplotlib.pyplot as plt

print(cv2.__version__)

img = cv2.imread("lena.png")
#使用cv2.imread()读取图像时，默认彩色图像的三通道顺序为B、G、R，这与我们所熟知的RGB中的R通道和B通道正好互换位置了。
#而使用plt.imshow()函数却默认显示图像的通道顺序为R、G、B，导致图像出现色差发蓝。
print(img.shape)

plt.imshow(img)
plt.show()#阻塞操作‌：plt.show() 是一个阻塞型调用，这意味着它会阻止脚本的进一步执行，直到关闭所有的图形窗口。这对于交互式使用 Matplotlib 非常有用，因为它允许用户有足够的时间查看图表。

# cv2.namedWindow('Lena')
# cv2.imshow('Lena',img)
# cv2.waitKey()
# cv2.destroyAllWindows()

# 色彩恢复
img2=cv2.cvtColor(img,cv2.COLOR_BGR2RGB)
plt.imshow(img2)
plt.show()

# cv2.imwrite("newlena.jpg", img2)

img_g=cv2.GaussianBlur(img2,(7,7),3)
plt.imshow(img_g)
plt.show()

img_gray=cv2.cvtColor(img2,cv2.COLOR_BGR2GRAY)
print(img_gray.shape)
plt.imshow(img_gray,cmap='gray') #cmap='gray' is required to show the image correctly
plt.show()

# edge detection
img_canny = cv2.Canny(img2,180,200)
plt.imshow(img_canny,cmap='gray')
plt.show()

print(type(img2))

# Treat matrix as an image
# You can operate 
img3 = img2 * 2
plt.imshow(img3)
plt.show()

# Translation
import numpy as np
rows, cols, chs = img2.shape
print(rows, cols, chs)
M = np.float32([[1,0,100],[0,1,50]])
dst = cv2.warpAffine(img2,M,(cols,rows))

plt.imshow(dst)
plt.show()

# Rotation
R = cv2.getRotationMatrix2D(((cols-1)/2.0,(rows-1)/2.0),45,1)
dst = cv2.warpAffine(img2,R,(cols,rows))

plt.imshow(dst)
plt.show()

# Hough Line
# https://docs.opencv.org/3.4/d6/d10/tutorial_py_houghlines.html
import cv2
import numpy as np
import matplotlib.pyplot as plt
img = cv2.imread('sudoku.jpg')
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
edges = cv2.Canny(gray,50,150,apertureSize = 3)
lines = cv2.HoughLines(edges,1,np.pi/180,200)
for line in lines:
    rho,theta = line[0]
    a = np.cos(theta)
    b = np.sin(theta)
    x0 = a*rho
    y0 = b*rho
    x1 = int(x0 + 1000*(-b))
    y1 = int(y0 + 1000*(a))
    x2 = int(x0 - 1000*(-b))
    y2 = int(y0 - 1000*(a))
    cv2.line(img,(x1,y1),(x2,y2),(0,0,255),2)

plt.imshow(img)
plt.show()

# Use GrabCut for foreground Extraction 提取图像中的前景
# https://docs.opencv.org/3.4/d8/d83/tutorial_py_grabcut.html

imgori = cv2.imread('messi4.jpg')
img = cv2.cvtColor(imgori, cv2.COLOR_BGR2RGB)
plt.imshow(img)
plt.show()

mask = np.zeros(img.shape[:2],np.uint8)
bgdModel = np.zeros((1,65),np.float64)
fgdModel = np.zeros((1,65),np.float64)
rect = (50,50,450,290)
cv2.grabCut(img,mask,rect,bgdModel,fgdModel,5,cv2.GC_INIT_WITH_RECT)
mask2 = np.where((mask==2)|(mask==0),0,1).astype('uint8')
img = img*mask2[:,:,np.newaxis]

plt.imshow(img)
plt.show()



#timeit np.sum(a) # numpy自带的求和函数
#timeit sum(a) # python自带的求和函数
#timeit nb_sum(a) # numba加速的求和函数
#timeit py_sum(a) # 没加速的求和函数

'''
#本次实验课程作业：
创建一个长度为10的向量，每一个向量的元素64位浮点型，每个元素均为PI

创建一个长度为10的随机向量，并将其排序,打印排序前后的向量。 （使用numpy)

创建一个长度为10的向量，并将向量中最大值替换为1。（使用numpy)

生成一个5＊5的随机矩阵，计算矩阵的秩,特征值。 （使用numpy)

生成一个7x7的随机矩阵，提取最中心的3x3区块。 （使用numpy)

在两个子图，位置是上下关系，分别画sin(x)和cos(x)

在一张图中，绘制三组不同的直方图，并设置不同透明度

绘制一组随机三维点

画一个101＊101的彩色图，背景图是红色的，前景中心处有一个21＊21的蓝色方块。

打开一幅图像，对其进行直方图均衡化，分别显示前后两幅图
'''
