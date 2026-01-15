import numpy as np
from PIL import Image

image = Image.open('Lena.bmp')
image_array = np.array(image)

#修改方法
def RGBtrans(n):
    return (n, n, 255 - n)

colored_image_array = np.zeros((image_array.shape[0], image_array.shape[1], 3), dtype=np.uint8)
for i in range(image_array.shape[0]):
    for j in range(image_array.shape[1]):
        colored_image_array[i, j] = RGBtrans(image_array[i, j])
        
#生成彩色图像
colored_image = Image.fromarray(colored_image_array)
colored_image.show()
colored_image.save('Lena2.bmp')