import os
import sys
import numpy as np
import random
import tkinter as tk
import decimal

class ControlPoint:
    def __init__(self, x = 0, y = 0):
        self.x = x
        self.y = y

# Generates the control points
X = [i + 100 for i in range(10, 600, 8)]
Y = []
points = []
for i in X:
    Y.append(random.randint(100, 300))
for i, v in enumerate(X):
    points.append([X[i], Y[i]])

# Helpers
def frange(x, y , steps):
    while x < y:
        yield float(x)
        x += decimal.Decimal(steps)


# Rendering Helpers
def drawPoint(x, y, c):
    c.create_rectangle(x, y, x + 4, y + 4, fill="blue")


# Render the control points
def drawControlPoints():
    for p in points:
        drawPoint(p[0], p[1], c)

# Connect the control points with straight lines
def connectWithLines():
    for i, v in enumerate(points):
        if i > len(points) - 2: break
        next = points[i + 1]
        c.create_line(v[0], v[1], next[0], next[1], fill="red")

# Connect the control points with cubic interpolations
def catmullRom():
    for i, v in enumerate(points):
        if i == 0 or i > len(points) - 3: continue

        p0 = points[i - 1]
        p1 = points[i]
        p2 = points[i + 1]
        p3 = points[i + 2]

        delta = p2[0] - p1[0]
        steps = 1.0 / delta
    
        for t in frange(0, 1, 0.05):
            tt = t**2
            ttt = tt * t

            q1 = -ttt + 2 * tt - t
            q2 = 3 * ttt - 5 * tt + 2
            q3 = -3 * ttt + 4 * tt + t
            q4 = ttt - tt

            x = 0.5 * (q1 * p0[0] + q2 * p1[0] + q3 * p2[0] + q4 * p3[0])
            y = 0.5 * (q1 * p0[1] + q2 * p1[1] + q3 * p2[1] + q4 * p3[1])

            drawPoint(x, y, c)

def cleanCanvas(c):
    c.delete('all')
#################################################################################################"

root = tk.Tk()
root.title("Splines Proof of Concept")

c = tk.Canvas(root, bg='white', width='800', height='600')
c.pack(expand=True, fill=tk.X)

# Buttons        
drawcpButton = tk.Button(root, text='Control Points', command=drawControlPoints)
drawcpButton.pack(side=tk.LEFT)

connectLinesButton = tk.Button(root, text="Linear Connect", command=connectWithLines)
connectLinesButton.pack(side=tk.LEFT)

catmullRomButton = tk.Button(root, text="Catmull-Rom", command=catmullRom)
catmullRomButton.pack(side=tk.LEFT)

cleanButton = tk.Button(root, text='Clean Canvas', fg='white', bg='green', command= lambda : cleanCanvas(c))
cleanButton.pack(side=tk.LEFT)

quitButton = tk.Button(root, text='Quit Application', fg="white", bg='red', command=root.quit)
quitButton.pack(fill=tk.X)


root.mainloop()