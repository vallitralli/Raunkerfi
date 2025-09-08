import board
import busio
import adafruit_tcs34725
import adafruit_ssd1306
from PIL import Image, ImageDraw, ImageFont

Create I2C bus
i2c = busio.I2C(board.SCL, board.SDA)

Initialize sensor
sensor = adafruit_tcs34725.TCS34725(i2c)
sensor.enable = True
sensor.integration_time = 100
sensor.gain = 4

Read raw color values
r, g, b, c = sensor.color_raw

Determine dominant color
values = {"Red": r, "Green": g, "Blue": b}
color = max(values, key=values.get)  # pick the key with the largest value

Initialize display
display = adafruit_ssd1306.SSD1306_I2C(128, 64, i2c)
display.fill(0)
display.show()

Prepare drawing surface
width = display.width
height = display.height
image = Image.new("1", (width, height))
draw = ImageDraw.Draw(image)
font = ImageFont.load_default()

Draw text
text = color
text_width, text_height = draw.textsize(text, font=font)
x = (width - text_width) // 2
y = (height - text_height) // 2
draw.text((x, y), text, font=font, fill=255)

Display it
display.image(image)
display.show()