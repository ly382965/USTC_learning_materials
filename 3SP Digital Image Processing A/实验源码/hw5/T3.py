import math
import numpy as np
import cv2
import sys

"""
该脚本实现对“Lema.bmp”图像进行任意角度旋转，采样时采用双线性插值方法。
旋转时以图像中心为旋转中心，同时扩展输出图像尺寸确保完整包含旋转后的图像。
"""

def bilinear_interpolate(img, x, y):
    """
    对灰度或RGB图像进行双线性插值
    img: numpy数组，形状为(H, W)或(H, W, C)
    x, y: 浮点数坐标（横坐标: 列，纵坐标: 行）
    返回插值后的像素值（可能为RGB元组或单个值）
    """
    h = img.shape[0]
    w = img.shape[1]
    x0 = int(math.floor(x))
    x1 = x0 + 1
    y0 = int(math.floor(y))
    y1 = y0 + 1
    u = x - x0
    v = y - y0

    if x0 < 0 or x1 >= w or y0 < 0 or y1 >= h:
        if img.ndim == 3:
            return np.array([0, 0, 0], dtype=img.dtype)
        else:
            return 0

    I1 = img[y0, x0]
    I2 = img[y1, x0]
    I3 = img[y0, x1]
    I4 = img[y1, x1]

    return (1 - u) * (1 - v) * I1 + (1 - u) * v * I2 + u * (1 - v) * I3 + u * v * I4

def rotate_image(img, angle):
    """
    旋转图像
    img: numpy数组，形状为(H, W)或(H, W, C)
    angle: 旋转角度，单位为度（正值逆时针旋转）
    返回旋转后的图像数组
    """
    angle_rad = math.radians(angle)
    cos_val = math.cos(angle_rad)
    sin_val = math.sin(angle_rad)

    h = img.shape[0]
    w = img.shape[1]

    #中心坐标，以中心建立坐标系
    cx, cy = w / 2, h / 2

    corners = np.array([
        [-cx, -cy],
        [w - cx, -cy],
        [-cx, h - cy],
        [w - cx, h - cy]
    ])

    # 旋转矩阵
    R = np.array([[cos_val, -sin_val],
                  [sin_val,  cos_val]])

    new_corners = np.dot(corners, R.T)
    x_coords = new_corners[:, 0] #旋转后的x坐标
    y_coords = new_corners[:, 1] #旋转后的y坐标

    # 旋转后尺寸发生变化，计算旋转后图像的宽高
    w_new = int(math.ceil(x_coords.max() - x_coords.min()))
    h_new = int(math.ceil(y_coords.max() - y_coords.min()))

    x_offset = -x_coords.min()
    y_offset = -y_coords.min()

    rotated = np.zeros((h_new, w_new), dtype=img.dtype)

    for i in range(h_new):
        for j in range(w_new):
            y_new = i - y_offset
            x_new = j - x_offset

            x_old =  cos_val * x_new + sin_val * y_new
            y_old = -sin_val * x_new + cos_val * y_new

            # 还原到原图坐标系
            x_src = x_old + cx
            y_src = y_old + cy

            if x_src >= 0 and x_src < w - 1 and y_src >= 0 and y_src < h - 1:
                rotated[i, j] = bilinear_interpolate(img, x_src, y_src)
            else:
                rotated[i, j] = 0 # 没有对应像素值时填充为0

    return rotated


angle = 180

img = cv2.imread('lena.bmp', 0)
rotated_np = rotate_image(img, angle)
output_filename = f"lema_rotated_{angle}.bmp"
cv2.imwrite(output_filename, np.uint8(rotated_np))
print(f"旋转后的图像已保存为 {output_filename}")

