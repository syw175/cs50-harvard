 #
 # Filename: mario.c (More Comfortable)
 #
 # Description: Recreate the pyramid of blocks in the beginning of World 1-1 from Super Mario Brothers
 #              made in Python instead of C.
 # 
 # Author: Steven Wong
 # Date: July 21, 2022
 

def main(): 
    height = getHeight()
    drawPyramid(height)

# Get the height of the pyramid from the user    
def getHeight():
    while True: 
        try: 
            # Try to get the height from the user
            height = int(input("Give me a height: "))
            return height

        # If the user enters a non-integer, print an error message and ask again
        except ValueError:
            print("That is not a valid height")    

    
# Draw the pyramid
def drawPyramid(height): 
    for row in range(height):
        # Calculate the hashes to be printed in the current row 
        rowHashes = row + 1 
        # Calculate the spaces to be printed in the current row 
        rowSpaces = height - row -1 

        # Print the LHS pyramid 
        print(" " * rowSpaces, end="")
        print("#" * rowHashes, end="")

        # Print the LHS-RHS pyramid divider 
        print("  ", end="")
        # Print the RHS pyramid 
        print("#" * rowHashes, end="")
        # Print a space for each end of a row 
        print()


if __name__ == "__main__":
    main()    
