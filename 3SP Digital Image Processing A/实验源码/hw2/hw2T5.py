from PIL import Image
import numpy as np

image = Image.open('Lena.bmp')
image_array = np.array(image)

# 将前256行像素设为255
image_array[:256, :] = 255

processed_image = Image.fromarray(image_array)
processed_image.show()
processed_image.save('Lena1.bmp')