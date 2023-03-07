
from random import randint, choice

#-----Data Set Function for Assessing Your Solution------------------#
#
# The function in this module generates the data sets that will be
# used to assess your solution.
#
# Do NOT change any of the code in this module.  Do NOT submit a copy
# of this module with your solution - we will use our own copy to
# assess your code.
#
# The following function creates a random data set defining the
# overall image to draw.  Your program must work for ANY data set that
# can be produced by this function.  The results returned by calling
# this function will be used as the argument to your data visualisation
# function during marking.  For convenience during code development
# and marking this function also prints the data set generated to the
# shell window.  NB: Your solution should not print anything else to
# the shell.  Make sure any debugging calls to the "print" function
# are disabled before you submit your solution.
#
def steps():

    # Define the possible movement directions with a bias in one
    # particular direction
    basic_moves = ['N', 'NE', 'SE', 'S', 'SW', 'NW']
    biased_moves = basic_moves + [choice(basic_moves)] * 5 
    # Define the different levels
    levels = ['Level A', 'Level B', 'Level C', 'Level D']
    # Define the possible level changes
    changes = ['Increase', 'Decrease', 'Same']
    # Choose the total number of steps
    # (in addition to the special first one)
    num_steps = randint(1, 50)

    # Initialise the data set with the special first step
    dataset = [[0, 'Home', choice(levels)]]

    # Create the individual steps (apart from the first one)
    for step_num in range(1, num_steps):
        # Choose which way to move
        move = choice(biased_moves)
        # Choose how the level changes
        change = choice(changes)
        # Add the chosen step to the data set
        dataset.append([step_num, move, change])

    # Print the whole data set to the shell window
    print('The movements to visualise\n(step number, direction and\nlevel change) are as follows:\n')
    print(str(dataset).replace('],', '],\n'))
    # Return the data set to the caller
    return dataset

#
#--------------------------------------------------------------------#



#--------------------------------------------------------------------#
#
# Some "fixed" data sets
#
# Developing code when the underlying data set changes randomly can
# be difficult.  To help you develop your code you can temporarily
# provide the call to the "movements" function defined in the
# assignment template file with a "seed" value which will force it
# to produce a known data set.
#
# To do so, just put the seed value in the call to "movements" as
# its argument.  Of course, having completed your solution, your
# program must work for any list that can be returned by calling
# "movements" with no argument.
#
# Some examples of useful seeds follow.  Of course, you are free
# to choose other seed values to help you debug your code.
#
# In all the following cases the object/entity stays within
# the grid.
#
# Seed 641: The object/entity starts at Level A and doesn't move.
# Seed 806: The object/entity starts at Level C and doesn't move.
# Seed 317: The object/entity moves only one cell north and stays
#           at Level D.
# Seed 10:  The object/entity only moves twice and stays at
#           Level D the whole time.
# Seed 925: The object/entity moves twice, starting at Level C
#           and increasing to Level D.
# Seed 972: The object/entity travels in a crooked path to the
#           north-west.
# Seed 308: The object/entity travels in a crooked path to the
#           east and stops on the border. It goes through all
#           four levels in doing so.
# Seed 62:  The object/entity travels in a crooked path to the
#           south-west, sometimes revisiting the same cells.
# Seed 200: The object/entity initially stays near the home cell,
#           revisiting it three times, but then goes up to the
#           north border.
#
# In all the following cases the object/entity breaks out of the
# grid.
#
# Seed 536: The object/entity heads straight north-west and breaks
#           out in Step 6.
# Seed 655: The object heads mainly north, with a few small
#           diversions, eventually breaking out at Step 9.
# Seed 831: The object/entity moves around at Level D for a while
#           and then starts going east at lower levels and breaks
#           out in Step 9.
# Seed 7:   The object/entity follows a crooked path east and
#           breaks out in Step 7.
# Seed 937: The object/entity heads south-west to the bottom-left
#           corner (cell A1) and breaks out in Step 8.
# Seed 161: The object/entity follows a crooked path west and
#           breaks out in Step 11.
# Seed 586: The object/entity follows a crooked path north-west
#           and breaks out in Step 15. It goes through all four
#           levels in doing so.
# Seed 297: The object/entity goes up to the north border but then
#           turns west and eventually breaks out in Step 10.
#
#--------------------------------------------------------------------#
