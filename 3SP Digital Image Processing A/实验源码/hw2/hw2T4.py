from PIL import Image

image = Image.open('Lena.bmp')
pixels = []

for y in range(200, 210):
    row = []
    for x in range(200, 210):
        row.append(image.getpixel((x, y)))
        
    pixels.append(row)

for row in pixels:
    print(row)