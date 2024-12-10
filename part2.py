# PROJECT PART 2
# 1. GABRIEL GIFT AZERE
# 2. AHMAD SHAFI MOGRAL
# DEC 1, 2024
# Used the help of AI and CoPilot to write this code

import csv
import random
import cmpt120image
import draw
from main import play_sound, read_input_with_screen

# Load words from CSV
def load_words(filename="blackfoot.csv"):
    words = []
    with open(filename, newline='') as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            words.append(row[0])
    return words

# Learn function
def learn(words, num_words):
    words_to_learn = random.sample(words, num_words)
    for word in words_to_learn:
        image = cmpt120image.get_image(f"images/{word}.png")
        canvas = cmpt120image.get_black_image(800, 600)
        for row in canvas:
            for col in range(len(row)):
                row[col] = [255, 255, 255]
        draw.distribute_items(canvas, image, 1)
        cmpt120image.show_image(canvas, f"Learning: {word}")
        play_sound(word)
        read_input_with_screen("Press enter to continue to the next word...")
    main_menu()

# Settings function
def settings():
    global num_words_to_learn, num_rounds
    while True:
        choice = read_input_with_screen(f"Enter number of words to learn (3 - {len(words)}): ")
        if choice.isdigit():
            choice = int(choice)
            if 3 <= choice <= len(words):
                num_words_to_learn = choice
                print(f"Number of words to learn set to: {num_words_to_learn}")
                break
            else:
                print(f"Please enter a number between 3 and {len(words)}.")
        else:
            print("Invalid input. Please enter a number.")

    while True:
        choice = read_input_with_screen("Enter number of rounds to play: ")
        if choice.isdigit():
            choice = int(choice)
            if choice >= 1:
                num_rounds = choice
                print(f"Number of rounds set to: {num_rounds}")
                break
            else:
                print("Please enter a valid number of rounds.")
        else:
            print("Invalid input. Please enter a number.")
    main_menu()

# Play function
def play():
    for _ in range(num_rounds): 
        print("New Challenge")
        challenge_word = random.choice(words)
        image = cmpt120image.get_image(f"images/{challenge_word}.png")
        canvas = cmpt120image.get_black_image(800, 600)

        for row in canvas:
            for col in range(len(row)):
                row[col] = [255, 255, 255]

        for _ in range(5):
            random_word = random.choice(words)
            random_image = cmpt120image.get_image(f"images/{random_word}.png")
            random_transform = random.random()
            if random_transform < 0.5:
                random_image = draw.recolor_image(random_image, [random.randint(0, 255) for _ in range(3)])
            if random_transform < 0.25:
                random_image = draw.minify(random_image)
            if random_transform < 0.15:
                random_image = draw.mirror(random_image)
            draw.distribute_items(canvas, random_image, random.randint(1, 3))

        n = random.randint(1, 4)
        draw.distribute_items(canvas, image, n)
        cmpt120image.show_image(canvas, f"Find the {challenge_word}")
        play_sound(challenge_word)

        user_count = int(read_input_with_screen("How many items did you find? "))
        if user_count == n:
            print("Correct!")
        else:
            print(f"Incorrect. There were {n} items.")
    main_menu()

# Main menu function
def main_menu():
    while True:
        print("MAIN MENU")
        print("1. Learn    - Word flashcards")
        print("2. Play     - Seek and Find Game")
        print("3. Settings - Change Difficulty")
        print("4. Exit")
        choice = read_input_with_screen("Choose an option: ")
        if choice == '1':
            learn(words, num_words_to_learn)
        elif choice == '2':
            play()
        elif choice == '3':
            settings()
        elif choice == '4':
            print("Goodbye!")
            exit()
        else:
            print("Invalid choice. Please try again.")

if __name__ == "__main__":
    initial_canvas = cmpt120image.get_black_image(800, 600)
    for row in initial_canvas:
        for col in range(len(row)):
            row[col] = [255, 255, 255]
    cmpt120image.show_image(initial_canvas, "Welcome to the Learning App")

    words = load_words()
    num_words_to_learn = 3
    num_rounds = 3
    main_menu()
