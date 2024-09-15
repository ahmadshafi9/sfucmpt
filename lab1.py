import random

# Function to capitalize the first letter of the user's name
def format_name(name):
    return name.strip().capitalize()

# list of directions for seeking fortune
directions = ["North", "East", "West", "South"]

# greet the user as batman
print("I am Batman. ")

# ask for the user's name and capitalize the first letter when storing it
userinput = input("Whats your name? Gotham needs to know who I'm speaking to: ")
username = format_name(userinput)
# greet the user by their name and tell them you have a mission for them
print(f"Hi, {username}. I have a mission for you.")

# randomly choose a direction for the user's fortune
chosen_direction = random.choice(directions)

# tell the user their fortune lies in the chosen direction
print(f"Your fortune lies in the {chosen_direction}. Head that way, and don’t look back. Justice awaits.")

# Ask the user a yes/no question
user_reply = input("Do you need any tools from the Batcave? Enter [yes/yup/no/nope]: ").strip().lower()

# Batman responds based on user input
if user_reply == "yes" or user_reply == "yup":
    print("Good. Take the grappling hook. You'll need it.")
elif user_reply == "no" or user_reply == "nope":
    print("Brave. But remember, the night is dark, and Gotham is unforgiving.")
else:
    print("I don't have time for games. Choose wisely next time.")

# End the chat
print(f"Now go, and may justice be with you, {username}.")