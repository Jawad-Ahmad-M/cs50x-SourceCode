# We are going to loop until we get the exact value of pyramid which we require according to the problem i.e from 1 to 8 only.
# Se we gonna set some parameter for it like below:

while (1):  # It makes a loop to run till user enters wrong input
    # asks user to input the value of height
    height = input("Height: ")

    # Check whether the input is digit or not
    if (height.isdigit()):
        height = int(height)  # converts the height str into integer

        # Checks the condition if the height comes in our parameters to break the loop to get results
        if (height > 0 and height <= 8):
            break  # break the loop

for i in range(height):  # The  loop which iterates through the no of lines(i.e. height) of pyramid.
    # This loop makes the spaces which come before the char '#' in one line.
    for j in range(height-i-1):
        print(" ", end="")  # this prints the space character

    # This loops prints the '#' char number of lines times like 8 on 8th line, 1 on 1st line and etc.
    for j in range(i+1):
        print("#", end="")  # this prints the '#' character

    print()  # prints a new line when spaces and '#' i.e. bricks are drawn.
