# Image processing module
# Sample solution - by Brian Fraser
# Copyright 2024
# Do not share this file with others not in the class, or post it online.
import cmpt120image
import random

# Change any non-white pixel to the new colour.
# "non-white" is defined as a colour with r,g or b < 240
def recolor_image(img, color):
    THRESHOLD = 240
    height = len(img)
    width = len(img[0])
    new_img = cmpt120image.get_black_image(width, height)

    for row in range(height):
        for col in range(width):
            pixel = img[row][col][:]
            if pixel[0] < THRESHOLD or pixel[1] < THRESHOLD or pixel[2] < THRESHOLD:
                pixel = color
            new_img[row][col] = pixel
    return new_img

# Reduce the image to be half size.
# Input:
#   img: Input image
# Return:
#   A new image which is half the width and half the height of `img`
def minify(img):
    height = len(img)
    width = len(img[0])
    small_img = cmpt120image.get_black_image(width // 2, height // 2)

    for row in range(height // 2):
        for col in range(width // 2):
            # Average 4 source pixels
            sum = [0,0,0]
            for rgb_idx in range(len(sum)):
                for src_row in [row * 2, row * 2 + 1]:
                    for src_col in [col * 2, col * 2 + 1]:
                        pixel = img[src_row][src_col]
                        sum[rgb_idx] += pixel[rgb_idx]

                sum[rgb_idx] /= 4
        
            small_img[row][col] = sum
    return small_img
  
def mirror(img):
    height = len(img)
    width = len(img[0])
    mirror_img = cmpt120image.get_black_image(width, height)

    for row in range(height):
        for col in range(width):
            pixel = img[row][col]
            mirror_img[row][width - col - 1] = pixel
    return mirror_img
  
def draw_item(canvas, img, row, col):
    THRESHOLD = 240
    for row_idx in range(len(img)):
        for col_idx in range(len(img[0])):
            pixel = img[row_idx][col_idx]
            if pixel[0] < THRESHOLD or pixel[1] < THRESHOLD or pixel[2] < THRESHOLD:
                canvas[row + row_idx][col + col_idx] = pixel
  
def distribute_items(canvas, img, n):
    can_height = len(canvas)
    can_width = len(canvas[0])
    img_height = len(img)
    img_width = len(img[0])
    for i in range(n):
        max_height = can_height - img_height
        max_width = can_width - img_width
        start_row = random.randint(0, max_height - 1)
        start_col = random.randint(0, max_width - 1)
        draw_item(canvas, img, start_row, start_col)
