
#-----Statement of Authorship----------------------------------------#
#
#  This is an individual assessment item for QUT's teaching unit
#  IFB104, "Building IT Systems", Semester 1, 2022.  By submitting
#  this code I agree that it represents my own work.  I am aware of
#  the University rule that a student must not act in a manner
#  which constitutes academic dishonesty as stated and explained
#  in QUT's Manual of Policies and Procedures, Section C/5.3
#  "Academic Integrity" and Section E/2.1 "Student Code of Conduct".
#

student_number = 69420 # put your student number here as an integer
student_name   = "NOPE" # put your name here as a character string

#
#  NB: Files submitted without a completed copy of this statement
#  will not be marked.  All files submitted will be subjected to
#  software plagiarism analysis using the MoSS system
#  (http://theory.stanford.edu/~aiken/moss/).
#
#--------------------------------------------------------------------#



#-----Task Description-----------------------------------------------#
#
#  BREAKOUT
#
#  This assessment item tests your skills at processing data stored in
#  lists, creating reusable code and following instructions to display
#  a complex visual image.  The incomplete Python program below is
#  missing a crucial function, "follow_path".  You are required to
#  complete this function so that when the program runs it fills
#  a map with various symbols, using data stored in a list to
#  determine which symbols to draw and where.  See the various
#  "client's briefings" in Blackboard for full details.
#
#  Note that this assessable assignment is in multiple parts,
#  simulating incremental release of instructions by the client.
#  This single template file will be used for all parts and you will
#  submit your final solution as a single Python 3 file only, whether
#  or not you complete all requirements for the assignment.
#
#--------------------------------------------------------------------#



#-----Preamble-------------------------------------------------------#
#
# This section imports necessary functions and defines constant
# values used for creating the drawing canvas.  You may NOT change
# any of the code in this section except as indicated by the
# comments marked '*****'.
#

# Import standard Python modules needed to complete this assignment.
# You should not need to use any other modules for your solution.
# In particular, your solution must NOT rely on any non-standard
# Python modules that need to be downloaded and installed separately,
# because the markers will not have access to such modules.
from ast import For
from re import I
from tkinter import Y
from turtle import *
from math import *
from random import *
from sys import exit as abort
from os.path import isfile
# from tkinter import dialog

# Define the length of the sides of the cells. All other dimensions
# for the drawing canvas are calculated relative to this value.
# ***** If necessary you can change this value to alter the
# ***** overall size of the drawing canvas, but only do so
# ***** as a last resort. A better option is to change the
# ***** resolution of your computer's screen. Setting the value
# ***** below too small will limit the space available for drawing
# ***** symbols and making it too big may cause the canvas
# ***** to be too large for the marker's screen.
cell_side = 50 # pixels (default is 50)

# Derive constant values used in the main program that sets up
# the drawing canvas.  Do NOT change any of these values.
cell_width = cell_side + (2 * (cell_side * cos(radians(60)))) # some trigonometry!
cell_height = 2 * (cell_side * sin(radians(60))) # and some more!
x_margin = cell_width * 2.5 # the size of the margin left and right of the map
y_margin = cell_height // 1.5 # the size of the margin below and above the map
window_height = 8 * cell_height + y_margin * 2 # the drawing canvas' height
window_width = 8 * cell_width + x_margin * 2 # the drawing canvas' width
coord_font = ('Arial', cell_side // 3, 'normal') # text font for coords
label_font = ('Arial', cell_side // 2, 'normal') # text font for labels

# Validity check on dimensions - do not change this code
assert (40 <= cell_side <= 60), \
       'Cell sides must be between 40 and 60 pixels in length'

#
#--------------------------------------------------------------------#



#-----Initialisation Steps-------------------------------------------#
#
# This code checks that the programmer's identity has been provided
# and whether or not the data generation function is available.  Do
# NOT change any of the code in this section.
#

# Confirm that the student has declared their authorship
if not isinstance(student_number, int):
    print('\nUnable to run: No student number supplied',
          '(must be an integer)\n')
    abort()
if not isinstance(student_name, str):
    print('\nUnable to run: No student name supplied',
          '(must be a character string)\n')
    abort()

### Define the function for generating data sets, using the
### client's data generation function if available, but
### otherwise creating a dummy function that returns an empty
### list
if isfile('motion_data.py'):
    print('\nData module found ...')
    from motion_data import steps
    def movements(new_seed = randint(0, 999)):
        print('Using seed', new_seed, '...\n')
        seed(new_seed) # set the seed
        return steps() # return the random data set
else:
    print('\nNo data module available!\n')
    def movements(dummy_parameter = None):
        return [] # return an empty data set

#
#--------------------------------------------------------------------#



#-----Functions for Drawing the Map----------------------------------#
#
# The functions in this section are called by the main program to
# create the drawing canvas for your image.  Do NOT change
# any of the code in this section.
#

# Set up the canvas and draw the background for the overall image
def create_map(bg_colour = 'light grey',
               line_colour = 'slate grey',
               draw_map = True,
               add_text = True): # NO! DON'T CHANGE THIS CODE!

    # Set up the drawing canvas with enough space for the map and
    # spaces on either side
    setup(window_width, window_height)
    bgcolor(bg_colour)

    # Draw as quickly as possible
    tracer(False)

    # Get ready to draw the map
    penup()
    color(line_colour)
    width(2)

    # Determine the left-bottom coords of the map
    left_edge = -(8.5 * cell_width) // 2
    bottom_edge = -(7 * cell_height) // 2

    # Optionally draw the map
    if draw_map:

        # Mark the home coordinate
        home()
        dot(cell_side // 4)

        # Draw the cells row by row
        for rows in range(8):
            # Draw upper half of row
            goto(left_edge, bottom_edge + (rows * cell_height))
            pendown()
            setheading(0) # face east
            for angle in ([60, -60, -60, 60] * 6)[:-1]:
                left(angle)
                forward(cell_side)
            penup()
            # Draw lower half of row
            goto(left_edge, bottom_edge + (rows * cell_height))
            pendown()
            setheading(0) # face east
            for angle in ([-60, 60, 60, -60] * 6)[:-1]:
                left(angle)
                forward(cell_side)
            penup()

        # Draw each of the labels on the x axis
        penup()
        y_offset = cell_height // 1.2 # pixels
        for x_label in range(11):
            goto(left_edge - (cell_width // 4) + ((x_label + 1) * (cell_width // 1.32)),
                 bottom_edge - y_offset)
            write(chr(x_label + ord('A')), align = 'center', font = coord_font)

        # Draw each of the labels on the y axis
        penup()
        x_offset, y_offset = cell_side // 5, cell_height // 10 # pixels
        for y_label in range(15):
            goto(left_edge + (cell_width * 8.7), bottom_edge + (y_label * (cell_height // 2)) - y_offset)
            write(str(y_label + 1), align = 'left', font = coord_font)


    # Optionally mark the blank spaces ... HANDS OFF! YOU CAN'T CHANGE ANY OF THIS CODE!
    if add_text:
        # Write to the left of the map
        goto(-(4.4 * cell_width), -(cell_height // 2))
        write('Draw the\nfour levels of\nyour object or\nentity here', align = 'right', font = label_font)
        # Write to the right of the map
        goto(4.8 * cell_width, -cell_height)
        write('Your final\nmessage\n(if any) will\nappear\nhere', align = 'left', font = label_font)


    # Reset everything ready for the student's solution
    pencolor('black')
    width(1)
    penup()
    home()
    tracer(True)


# End the program and release the drawing canvas to the operating
# system.  By default the cursor (turtle) is hidden when the
# program ends.  Call the function with False as the argument to
# prevent this.
def release_map(hide_cursor = True):
    tracer(True) # ensure any drawing still in progress is displayed
    if hide_cursor:
        hideturtle()
    done()

#
#--------------------------------------------------------------------#



#-----Function to Write a Message------------------------------------#
#
# The function in this section writes a message to the screen.  You
# can use it to write your closing message at the end of the
# simulation.
#

def write_breakout_message(step_num):
    penup()
    color('firebrick')
    goto(cell_width * 4.8, -cell_height * 0.25)
    write('Breakout\nat Step ' + str(step_num) + '!',
          align = 'left', font = label_font)

#
#--------------------------------------------------------------------#



#-----Code to Create Drawing Canvas----------------------------------#
#
# This part of the main program sets up the canvas, ready for you to
# draw your solution.  Do NOT change any of this code except
# as indicated by the comments marked '*****'.  Do NOT put any of
# your solution code in this area.
#

# Set up the drawing canvas
# ***** You can change the background and line colours, and choose
# ***** whether or not to draw the map and other elements, by
# ***** providing arguments to this function call
create_map(add_text=False)

# Control the drawing speed
# ***** Change the following argument if you want to adjust
# ***** the drawing speed
speed('fastest')

# Decide whether or not to show the drawing being done step-by-step
# ***** Set the following argument to False if you don't want to wait
# ***** forever while the cursor moves slooooowly around the screen
tracer(False)

# Give the drawing canvas a title
# ***** Replace this title with a description of the
# ***** object or entity shown in your solution
title("Put a description of your object/entity here")

#
#--------------------------------------------------------------------#



#-----Student's Solution---------------------------------------------#
#
#  Complete the assignment by replacing the dummy function below with
#  your own "follow_path" function.  ALL of your solution code
#  must appear in, or be called from, function "follow_path".  Do
#  NOT put any of your code in any other parts of the program and do
#  NOT change any of the provided code except as allowed in parts
#  of the main program marked '*****'.

# Function to draw the base features of the hexagons
def hex_base(x_start, y_start):
    # Go to the starting point for the hexagon and make pen and fill colour black
    goto(x_start, y_start)
    setheading(0)
    pencolor("Black")
    fillcolor("Black")
    pendown()
    begin_fill()

    # Draw the hexagon outline
    for side in range(6):
        forward(50)
        right(60)
    end_fill()
    penup()

    # Draw house base
    pencolor("White")
    goto((x_start + 5), (y_start - 80))
    pensize(3)
    pendown()
    forward(20)
    left(90)
    forward(20)
    left(90)
    forward(20)
    left(90)
    forward(20)
    penup()


    # Draw roof
    goto((x_start + 15, y_start - 50))

    pendown()
    left(45)
    forward(15)
    penup()
    goto((x_start + 15, y_start - 50))
    pendown()
    left(-90)
    forward(15)

    penup()

    #draw doors!
    pensize(2)
    goto((x_start + 20, y_start -80))
    setheading(90)
    pendown()
    forward(10)
    left(90)
    forward(10)
    left(90)
    forward(10)
    left(90)
    forward(10)
    setheading(0)
    left(90)

    forward(5)
    left(90)
    forward(10)

    penup()
    # Draw grass
    goto((x_start + 50), (y_start - 83))
    pendown()
    color('green')
    begin_fill()
    setheading(180)
    forward(50)
    left(90)
    forward(5)
    left(90)
    forward(50)
    left(90)
    forward(5)
    end_fill()
    penup()
    color('white')

    #Draw stars
    goto((x_start + 40, y_start -20))
    pendown()
    for points in range(5):
        forward(10)
        right(144)
    penup()

    goto((x_start + 20, y_start -10))
    pendown()
    for points in range(5):
        forward(10)
        right(144)
    penup()

    goto((x_start + 20, y_start -30))
    pendown()
    for points in range(5):
        forward(10)
        right(144)
    penup()


def cresent_moon(x, y):
    hex_base(x, y)
    goto(x+45, y-40)
    color('orange')
    begin_fill()
    circle(10)
    end_fill()
    penup()
    goto(x+50, y-40)
    pendown()
    color('Black')
    begin_fill()
    circle(10)
    end_fill()
    penup()

def half_moon(x, y):
    hex_base(x, y)
    goto(x+40, y-40)
    color('orange')
    begin_fill()
    circle(10)
    end_fill()
    penup()
    goto(x+50, y-50)
    pendown()
    color('Black')
    setheading(90)
    begin_fill()
    forward(18)
    left(90)
    forward(18)
    left(90)
    forward(20)
    left(90)
    forward(22)
    left(90)
    forward(20)
    end_fill()
    penup()

def large_cresent_moon(x,y):
    hex_base(x, y)
    goto(x+50, y-40)
    color('orange')
    begin_fill()
    circle(10)
    end_fill()
    penup()
    goto(x +60 ,y-40)
    pendown()
    color('Black')
    begin_fill()
    circle(10)
    end_fill()
    penup()


def full_moon(x,y):
    hex_base(x, y)
    goto(x+50, y-35)
    pendown()
    color('orange')
    begin_fill()
    circle(10)
    end_fill()
    penup()


# All of your code goes in, or is called from, this function
def follow_path(path, visualise):
    x, y = 0, 0
    cresent_moon(-550, 200)
    half_moon(-550, 100)
    large_cresent_moon(-550, 0)
    full_moon(-550, -100)
    tracer(False)

    movement_mapping = {
        "N": {"x": 0, "y": 86.6},
        "NE": {"x": 76, "y": 44.3},
        "S": {"x": 0, "y": -86.6},
        "SW": {"x": -75, "y": -43},
        "NW": {"x": -74, "y": 44},
        "SE": {"x": 74, "y": -44}
    }

    level_name_to_index = {
        'Level A': 0,
        'Level B': 1,
        'Level C': 2,
        'Level D': 3,
    }

    level_mapping_index = [cresent_moon, half_moon, large_cresent_moon, full_moon]

    level_counter = 0

    hoz_edge = (8.5 * cell_width) // 2
    ver_edge = (7 * cell_height) // 2

    for path_step in path:
        step, direction, level = path_step

        if step == 0:
            level_counter = level_name_to_index[level]
            level_mapping_index[level_counter](x-(cell_width/4), y+(cell_height/2))
        else:
            if level == "Increase" and level_counter < 3:
                level_counter += 1
            elif level == "Decrease" and level_counter > 0:
                level_counter -= 1

            x += movement_mapping[direction]['x']
            y += movement_mapping[direction]['y']

            if abs(x) > hoz_edge:
                write_breakout_message(step)
                break
            elif abs(y) > ver_edge:
                write_breakout_message(step)
                break
            else:
                if visualise:
                    color('red')
                    write(f"{step}", align="left", font=("Verdana", 10, "normal"))
                level_mapping_index[level_counter](x - (cell_width / 4), y + (cell_height / 2))



#
#--------------------------------------------------------------------#



#-----Main Program to Call Student's Solution------------------------#
#
# This part of the main program calls your code and provides the
# data set to be visualised.  Do NOT change any of this code except
# as indicated by the comments marked '*****'.  Do NOT put any of
# your solution code in this area.

# Call the student's function to process the data set
# ***** While developing your program you can call the
# ***** "movements" function with a fixed seed for the
# ***** random number generator, but your final solution must
# ***** work with "movements()" as the first argument to
# ***** "follow_path", i.e., for any data set that can be
# ***** returned by calling function "movements" with no seed.
follow_path(movements(), True) # <-- no argument for "movements" when assessed

# Exit gracefully
# ***** Change the default argument to False if you want the
# ***** cursor (turtle) to remain visible when the program
# ***** terminates as a debugging aid
release_map()

#
#--------------------------------------------------------------------#


