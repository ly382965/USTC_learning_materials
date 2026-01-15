import numpy as np
import math
import cv2
import pywt

def DFT2D(matrix,M,N):
    dft_matrix = np.zeros((M,N),dtype=complex)
    for u in range(M):
        for v in range(N):
            for x in range(M):
                for y in range(N):
                    dft_matrix[u][v] += matrix[x][y]*np.exp(-2j*np.pi*(u*x/M+v*y/N))
    return dft_matrix

def DCT2D(matrix,M,N):
    dct_matrix = np.zeros((M,N),dtype=float)
    for u in range(M):
        for v in range(N):
            for x in range(M):
                for y in range(N):
                    dct_matrix[u][v] += matrix[x][y]*np.cos((2*x+1)*u*np.pi/(2*M))*np.cos((2*y+1)*v*np.pi/(2*N))
            if u == 0: # 1/sqrt(2) for u=0
                dct_matrix[u][v] *= 1/np.sqrt(2)
            if v == 0:
                dct_matrix[u][v] *= 1/np.sqrt(2)
            dct_matrix[u][v] *= 2/np.sqrt(M*N)
    return dct_matrix

def b(k, z):
        return (z >> k) & 1

# 定义矩阵
matrix = np.array([[0, 1, 1, 0],
                   [0, 1, 1, 0],
                   [0, 1, 1, 0],
                   [0, 1, 1, 0]])

H4= np.array([[1, 1, 1, 1],
             [1, -1, 1, -1],
             [1, 1, -1, -1],
             [1, -1, -1, 1]])

Harr4=np.array([[1, 1, 1, 1],
                [1, 1, -1, -1],
                [np.sqrt(2), -np.sqrt(2), 0, 0],
                [0, 0, np.sqrt(2), -np.sqrt(2)]])

# 计算二维DFT
dft_matrix_2 = DFT2D(matrix,4,4)
dct_matrix_2 = DCT2D(matrix,4,4)
Hadamard_matrix_2 = (1/4) * np.dot(np.dot(H4, matrix), H4.T)
Harr_matrix_2 = (1/4) * np.dot(np.dot(Harr4, matrix), Harr4.T)
# 打印结果
print("原矩阵:")
print(matrix)
print("二维DFT结果:")
np.set_printoptions(precision=2, suppress=True)
print(dft_matrix_2)
print("二维DCT结果:")
print(dct_matrix_2) 
print("Hadamard结果:")
print(Hadamard_matrix_2)
print("Harr结果:")
print(Harr_matrix_2)    
