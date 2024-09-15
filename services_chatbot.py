import random

# List of random employee names
employee_names = ["Ahmad (000-000-0000)", "Uday (111-111-1111)", "Brian (222-222-2222)", "Fraser (333-333-3333)",
                   "Dan (444-444-4444)"]
# Keywords for each service
children_youth_familysupport = ["children", "youth", "family", "support"]
diversity_inclusion_training = ["diversity", "inclusion", "training"]
employer_support_engagement = ["employer", "engagement", "support", "workplace"]
english_class_testing = ["english", "class", "testing"]
health_counselling = ["health", "counselling", "mental", "wellness"]
interpretation_translating = ["interpretation", "translating", "language"]
legal_information_workplace_rights = ["legal", "rights", "workplace"]
refugee_sponsorship = ["refugee", "sponsorship", "asylum"]
settlement_services = ["settlement", "housing", "employment", "community"]
violence_prevention_support = ["violence", "support", "crisis", "prevention"]

# Function to capitalize the first letter of the user's name
def format_name(name):
    return name.strip().capitalize()

# Loop everything 3 times
# give them 10 options to pick from 
for i in range(3):
    # Random employee name selection
    employee = random.choice(employee_names)
    userinput = input("Hello! Welcome to Mosaic Charities. I'm your virtual assistant here to help you."
    " May I know your name? ")
    username = format_name(userinput)
    print(f"Hi, {username}! What can I help you with today?")
    print("Enter 1 for Children, Youth, and Family Support")
    print("Enter 2 for Diversity and Inclusion Training")
    print("Enter 3 for Employer Support and Engagement")
    print("Enter 4 for English Class and Testing")
    print("Enter 5 for Health and Counselling")
    print("Enter 6 for Interpretation and Translating")
    print("Enter 7 for Legal Information & Workplace Rights")
    print("Enter 8 for Refugee Sponsorship")
    print("Enter 9 for Settlement Services")
    print("Enter 10 for Violence Prevention and Support")

    # ask the user to enter a number from 1-10 depending on what they want or they can also type it out
    servicechoice = input("Please enter the number corresponding to your choice\n"
    "or if you know which service you want please put that: ").strip().lower


    # give the user more information on what they want
    if servicechoice == "1" or any(keyword in servicechoice for keyword in children_youth_familysupport):
        print("You selected Children, Youth, and Family Support. When you move your family" +
            " to a new country, it can be hard to adjust and fit into your new community." +
            " MOSAIC provides many family immigration services to help you get to know your" +
            " community, practice your English, find jobs, and register for schools and children’s" +
            " programming. Our team of family support workers can help every member of your family" +
            " with one-on-one or group support. The MOSAIC family centre also runs additional programs" +
            " specifically for refugee families and their young kids. Programs are available in a variety" +
            " of languages. For more details, you can contact us at 604-254-9626 (Manager) or email info@mosaicbc.org.")
    elif servicechoice == "2" or any(keyword in servicechoice for keyword in diversity_inclusion_training):
        print("You selected Diversity and Inclusion Training. We provide tailored workshops" +
            " to foster inclusive workplaces and communities. These workshops help organizations" +
            " understand the importance of diversity and create environments where everyone feels" +
            " valued and included. For more details, you can contact us at 604-254-9626 (Manager) or email info@mosaicbc.org.")
    elif servicechoice == "3" or any(keyword in servicechoice for keyword in employer_support_engagement):
        print("You selected Employer Support and Engagement. Our services assist employers in" +
            " building diverse, equitable workplaces. We offer tools and resources to help companies" +
            " engage with their employees and create inclusive work environments. For more details, you can" +
            " contact us at 604-254-9626 (Manager) or email info@mosaicbc.org.")
    elif servicechoice == "4" or any(keyword in servicechoice for keyword in english_class_testing):
        print("You selected English Class and Testing. We offer a range of language classes for" +
            " all levels, from beginner to advanced. In addition to classes, we provide language" +
            " proficiency testing to help individuals assess and improve their English skills. For more" +
            " details, you can contact us at 604-254-9626 (Manager) or email info@mosaicbc.org.")
    elif servicechoice == "5" or any(keyword in servicechoice for keyword in health_counselling):
        print("You selected Health and Counselling. We provide various mental health and wellness" +
            " programs, including counseling services to support individuals in managing stress," +
            " emotional challenges, and overall well-being. For more details, you can contact us at" +
            " 604-254-9626 (Manager) or email info@mosaicbc.org.")
    elif servicechoice == "6" or any(keyword in servicechoice for keyword in interpretation_translating):
        print("You selected Interpretation and Translating. We offer professional interpretation" +
            " and translation services in multiple languages to assist individuals and organizations" +
            " in overcoming language barriers and ensuring effective communication. For more details," +
            " you can contact us at 604-254-9626 (Manager) or email info@mosaicbc.org.")
    elif servicechoice == "7" or any(keyword in servicechoice for keyword in legal_information_workplace_rights):
        print("You selected Legal Information & Workplace Rights. We offer guidance on legal rights" +
            " in the workplace and help workers navigate issues related to employment laws," +
            " discrimination, and workplace safety. For more details, you can contact us at 604-254-9626" +
            " (Manager) or email info@mosaicbc.org.")
    elif servicechoice == "8" or any(keyword in servicechoice for keyword in refugee_sponsorship):
        print("You selected Refugee Sponsorship. We assist individuals and groups with the refugee" +
            " sponsorship process. Our services include providing legal advice and settlement guidance" +
            " to ensure a smooth transition for refugees. For more details, you can contact us at 604-254-9626" +
            " (Manager) or email info@mosaicbc.org.")
    elif servicechoice == "9" or any(keyword in servicechoice for keyword in settlement_services):
        print("You selected Settlement Services. We help newcomers integrate into their communities" +
            " with a range of settlement resources and support services, including help with finding" +
            " housing, employment, and accessing community services. For more details, you can contact us" +
            " at 604-254-9626 (Manager) or email info@mosaicbc.org.")
    elif servicechoice == "10" or any(keyword in servicechoice for keyword in violence_prevention_support):
        print("You selected Violence Prevention and Support. Our team offers crisis intervention" +
            " and ongoing support for individuals affected by violence. We provide resources and" +
            " assistance to help victims of violence find safety and recovery. For more details, you can" +
            " contact us at 604-254-9626 (Manager) or email info@mosaicbc.org.")
    else:
        # if anything other than a number between a number from 1-10 then print invalid choice
        print(f"Invalid choice. Please contact {employee} or try again later!")

    # ask them for feedback
    feedback = input("Satisfied with my service? (Yes/No)").strip().lower()

    if feedback == "yes" or feedback == "y":
        print(f"Thank you {username}! I wish you a great day!")
    elif feedback == "no" or feedback == "n":
        whatwentwrong = input("I'm sorry about that! What went wrong?").strip()
        print("Your feedback is appreciated and has been reported to our agents!")
    else:
        print(f"Error 101: Invalid input. Please contact {employee} for more support!")
