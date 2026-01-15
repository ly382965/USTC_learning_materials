import cv2

# 从 JPG 文件中加载图像
image = cv2.imread('wxd.jpg')
if image is None:
    print("Error: Could not load 'wxd.jpg'.")
    exit(1)

# 定义目标尺寸（宽, 高）
target_dimensions = (65536, 65536)

# 使用线性插值放大图像
resized_image = cv2.resize(image, target_dimensions, interpolation=cv2.INTER_LINEAR)

# 保存为 PNG 文件
output_filename = 'wxd_enlarged_1.png'
cv2.imwrite(output_filename, resized_image)
print(f"Image has been resized to {target_dimensions[0]}x{target_dimensions[1]} and saved as '{output_filename}'.")