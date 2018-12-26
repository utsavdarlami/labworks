
import random
import time
import matplotlib.pyplot as plt #matplot library for plotting and animations
import matplotlib.animation as animation

def bubblesort(A):

    for i in range(len(A)):
        swapped = False
        for j in range(len(A)-1-i):
            if A[j]>=A[j+1]:
                temp = A[j]
                A[j] = A[j+1]
                A[j+1] = temp          
                swapped = True
            yield A
        if swapped == False:
            break


x = random.sample(range(1,100),99)          
 
generator=bubblesort(x)

fig, ax = plt.subplots() #figure , axes


thechart = ax.bar(range(len(x)),x) #bar graph with x-axis value from 1 to 100 and y-axis value form array X, 

#function to update the figure 
def update(A,rects):
    for rect,value in zip(rects,A):
        rect.set_height(value)#updating the height of rectangle with respect to value of array
        

ani  = animation.FuncAnimation(fig, func= update,fargs=(thechart,) ,frames = generator,interval = 1,repeat =False)

plt.show() #showing the animation 



