# For this version we don't have to use this library if you want to use
# get_float funtion on line 23 then uncomment below library

# from cs50 import get_float

while (1):
    userInput = input("Change: ")  # Take input from user as string
    try:
        userInput = float(userInput)  # Convert string into float
        if userInput > 0:
            break  # Break the loop

    except ValueError:
        continue


# We will get input in Dollars so We have to convert it into cents so we multiply
# it by 100 to get the total cents which will avoid our calculations in floats,
# we will convert into integer which will be calculated easily rather than float,
# because in float there are possible rounding issues and etc.
cash = round(userInput*100)

# cash = get_float("Change: ") # Take input from the user, could be done manually as done above, which don't requires the import of cs50.

# -----------------Unoptimized Version------------------- #

tempCash = cash
coins = 0

while (tempCash >= 25):  # Collects the number of 25 cent coins
    tempCash -= 25
    coins += 1

while (tempCash >= 10):  # Collects the number of 10 cent coins
    tempCash -= 10
    coins += 1

while (tempCash >= 5):  # Collects the number of 10 cent coins
    tempCash -= 5
    coins += 1

while (tempCash >= 1):  # Collects the number of 1 cent coins
    tempCash -= 1
    coins += 1

# -----------------Optimized Version------------------- #

newCash = cash
newCoins = 0

listOfCoins = [25, 10, 5, 1]
for value in listOfCoins:
    while (newCash >= value):
        newCoins += newCash // value
        newCash = newCash % value

# The optimized code decreases the time consumed because if are working with a
# very large amount , the substraction will cost us more time instead time but
# using floor division will give us exact number of coins which are possible
# with that number while remainder will become our original cash so that we
# only have to now calculate for other coins like 10, 5 and i cent which don't
# require much calculation because after the modulus of number with 25 will give
# us result under than 25 which could be easilty calculated with minimal resources.

# -----------------Output of Program------------------- #

print(newCoins)
