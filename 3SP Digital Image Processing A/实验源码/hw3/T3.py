import numpy as np
import cv2

def DFT2D(matrix):
    M, N = matrix.shape
    u = np.arange(M).reshape(-1, 1)
    v = np.arange(N).reshape(-1, 1)
    x = np.arange(M).reshape(1, -1)
    y = np.arange(N).reshape(1, -1)
    
    W_M = np.exp(-2j * np.pi * u @ x / M)
    W_N = np.exp(-2j * np.pi * v @ y / N)
    
    return W_M @ matrix @ W_N

def DCT2D(matrix):
    M, N = matrix.shape
    u = np.arange(M).reshape(-1, 1)
    v = np.arange(N).reshape(-1, 1)
    x = np.arange(M).reshape(1, -1)
    y = np.arange(N).reshape(1, -1)
    
    alpha_u = np.sqrt(1 / M) * (u == 0) + np.sqrt(2 / M) * (u != 0)
    alpha_v = np.sqrt(1 / N) * (v == 0) + np.sqrt(2 / N) * (v != 0)
    
    cos_u = np.cos((2 * x + 1) * u * np.pi / (2 * M))
    cos_v = np.cos((2 * y + 1) * v * np.pi / (2 * N))
    
    return (alpha_u * cos_u) @ matrix @ (alpha_v * cos_v).T

image = cv2.imread('lena.bmp', cv2.IMREAD_GRAYSCALE)

# 计算二维DFT并保存结果
dft_result = DFT2D(image)
dft_magnitude = np.log(np.abs(dft_result) + 1)
cv2.imwrite('Lena_dft.bmp', (dft_magnitude / dft_magnitude.max() * 255).astype(np.uint8))

# 计算二维DCT并保存结果
dct_result = DCT2D(image)
dct_magnitude = np.log(np.abs(dct_result) + 1)
cv2.imwrite('Lena_dct.bmp', (dct_magnitude / dct_magnitude.max() * 255).astype(np.uint8))

# 平移图像后计算DFT并保存
shifted_image = image * np.fromfunction(lambda i, j: (-1) ** (i + j), image.shape)
dft_result2 = DFT2D(shifted_image)
dft_magnitude2 = np.log(np.abs(dft_result2) + 1)
cv2.imwrite('Lena_dft2.bmp', (dft_magnitude2 / dft_magnitude2.max() * 255).astype(np.uint8))