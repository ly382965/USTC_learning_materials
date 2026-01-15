import numpy as np
import matplotlib.pyplot as plt
from numpy.linalg import matrix_rank, eig
import cv2

print("T1:创建一个长度为10的向量，每一个向量的元素64位浮点型，每个元素均为PI")
vector_pi = np.full(10, np.pi, dtype=np.float64)
print("PI向量:", vector_pi)

print("T2:创建一个长度为10的随机向量，并将其排序,打印排序前后的向量")
random_vector = np.random.rand(10)
print("前:", random_vector)
sorted_vector = np.sort(random_vector)
print("后:", sorted_vector)

print("T3:创建一个长度为10的随机向量，并将其最大值替换为1")
vector = np.random.rand(10)
print("前:", vector)
vector[vector.argmax()] = 1
print("后:", vector)

print("T4:生成一个5*5的随机矩阵，计算矩阵的秩,特征值")
matrix_5x5 = np.random.rand(5, 5)
rank = matrix_rank(matrix_5x5)
eigenvalues, _ = eig(matrix_5x5)
print("矩阵:\n", matrix_5x5)
print("秩:", rank)
print("特征值:", eigenvalues)

print("T5:生成一个7x7的随机矩阵，提取最中心的3x3区块")
matrix_7x7 = np.random.rand(7, 7)
center_block = matrix_7x7[2:5, 2:5]
print("矩阵:\n", matrix_7x7)
print("最中心的3x3区块:\n", center_block)

print("T6-T10:将这五张图片同时输出显示")

# T6: sin(x) 和 cos(x)
x = np.linspace(0, 2 * np.pi, 100)
fig1, axs1 = plt.subplots(2, 1)
axs1[0].plot(x, np.sin(x), label="sin(x)")
axs1[0].legend()
axs1[1].plot(x, np.cos(x), label="cos(x)")
axs1[1].legend()

# T7: 三组不同的直方图
data1 = np.random.normal(25, 10, 10000)
data2 = np.random.normal(50, 10, 10000)
data3 = np.random.normal(75, 10, 10000)
fig2 = plt.figure()
plt.hist(data1, bins=50, alpha=0.3, label="Data 1", color='r')
plt.hist(data2, bins=50, alpha=0.6, label="Data 2", color='g')
plt.hist(data3, bins=50, alpha=0.9, label="Data 3", color='b')
plt.legend()

# T8: 三维散点图
fig3 = plt.figure()
ax3 = fig3.add_subplot(111, projection='3d')
x = np.random.rand(100)
y = np.random.rand(100)
z = np.random.rand(100)
ax3.scatter(x, y, z)

# T9: 彩色图
fig4 = plt.figure()
image = np.zeros((101, 101, 3), dtype=np.uint8)
image[:, :] = [255, 0, 0]  # 红色
image[40:61, 40:61] = [0, 0, 255]  # 蓝色方块
plt.imshow(image)

# T10: 彩色图像直方图均衡化
image = cv2.imread("lena.png")
image_rgb = cv2.cvtColor(image, cv2.COLOR_BGR2RGB) # 将BGR图像转换为RGB图像
r, g, b = cv2.split(image_rgb)

#直方图均衡化
r_eq = cv2.equalizeHist(r)
g_eq = cv2.equalizeHist(g)
b_eq = cv2.equalizeHist(b)

equalized_image = cv2.merge((r_eq, g_eq, b_eq))

fig5, axs5 = plt.subplots(1, 2, figsize=(10, 5))
axs5[0].imshow(image_rgb)
axs5[0].set_title("Original Image")
axs5[0].axis("off")
axs5[1].imshow(equalized_image)
axs5[1].set_title("Equalized Image")
axs5[1].axis("off")

plt.show()
