import cv2
import numpy as np
import matplotlib.pyplot as plt

# 读取图像（灰度模式）
image = cv2.imread('lena.bmp', 0)  # 确保图片路径正确

# 添加高斯噪声
def add_gaussian_noise(img, mean, sigma):
    row, col = img.shape
    gauss = np.random.normal(mean, sigma, (row, col))
    noisy = img + gauss
    noisy = np.clip(noisy, 0, 255)
    return noisy.astype(np.uint8)

# 添加椒盐噪声
def add_salt_pepper_noise(img, prob):
    noisy = img.copy()
    row, col = img.shape
    salt = np.random.rand(row, col) < prob / 2
    noisy[salt] = 255
    pepper = np.random.rand(row, col) < prob / 2
    noisy[pepper] = 0
    return noisy

# 生成噪声图像
gaussian_noisy = add_gaussian_noise(image,0,50)
salt_pepper_noisy = add_salt_pepper_noise(image,0.1)

# 均值滤波（3x3核）
def mean_filter(img, kernel_size=3):
    pad = (kernel_size - 1) // 2
    # 边缘填充（复制边缘像素）
    padded = np.pad(img, ((pad, pad), (pad, pad)), mode='edge')
    filtered = np.zeros_like(img, dtype=np.float32)
    row,col = img.shape
    for i in range(row):
        for j in range(col):
            window = padded[i:i+kernel_size, j:j+kernel_size]
            filtered[i, j] = np.sum(window)/(kernel_size * kernel_size)
    return filtered.astype(np.uint8)

# 中值滤波（3x3核）
def median_filter(img, kernel_size=3):
    pad = kernel_size // 2
    # 边缘填充（复制边缘像素）
    padded = np.pad(img, pad_width=((pad, pad), (pad, pad)), mode='edge')
    filtered = np.zeros_like(img)
    row,col = img.shape
    for i in range(row):
        for j in range(col):
            window = padded[i:i+kernel_size, j:j+kernel_size]
            filtered[i, j] = np.median(window)
    return filtered.astype(np.uint8)

# 对高斯噪声图像滤波
mean_gaussian= mean_filter(gaussian_noisy)
median_gaussian = median_filter(gaussian_noisy)

# 对椒盐噪声图像滤波
mean_sp= mean_filter(salt_pepper_noisy)
median_sp = median_filter(salt_pepper_noisy)

plt.figure(figsize=(12, 8))

plt.subplot(3, 3, 2)
plt.imshow(image, cmap='gray')
plt.title('Original Image')

plt.subplot(3, 3, 4)
plt.imshow(gaussian_noisy, cmap='gray')
plt.title('Gaussian Noise')
plt.subplot(3, 3, 5)
plt.imshow(mean_gaussian, cmap='gray')
plt.title('Mean Filter (Gaussian)')
plt.subplot(3, 3, 6)
plt.imshow(median_gaussian, cmap='gray')
plt.title('Median Filter (Gaussian)')

plt.subplot(3, 3, 7)
plt.imshow(salt_pepper_noisy, cmap='gray')
plt.title('Salt & Pepper Noise')
plt.subplot(3, 3, 8)
plt.imshow(mean_sp, cmap='gray')
plt.title('Mean Filter (Salt & Pepper)')
plt.subplot(3, 3, 9)
plt.imshow(median_sp, cmap='gray')
plt.title('Median Filter (Salt & Pepper)')

plt.tight_layout()
plt.show()