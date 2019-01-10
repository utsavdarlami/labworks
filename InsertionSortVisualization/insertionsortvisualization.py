import random
import time
import matplotlib.pyplot as plt #matplot library for plotting and animations
import matplotlib.animation as animation

def insertion_sort(array_of_random_numbers):
    size_of_array=len(array_of_random_numbers)
    for i in range(1,size_of_array):
        key = array_of_random_numbers[i]
        j=i-1
        while(j>=0 and array_of_random_numbers[j]>key):
            array_of_random_numbers[j+1]=array_of_random_numbers[j]
            j=j-1
            yield array_of_random_numbers
        array_of_random_numbers[j+1]=key
        
x = random.sample(range(1,100),99)          

generator = insertion_sort(x)
fig, ax = plt.subplots() #figure , axes


thechart = ax.bar(range(len(x)),x) #bar graph with x-axis value from 1 to 100 and y-axis value form array X, 

#function to update the figure 
def update(A,rects):
    for rect,value in zip(rects,A):
        rect.set_height(value)#updating the height of rectangle with respect to value of array
        

ani  = animation.FuncAnimation(fig, func= update,fargs=(thechart,) ,frames = generator,interval = 1,repeat =False)

plt.show() #showing the animation 
