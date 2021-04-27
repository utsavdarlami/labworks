# Image Quntization Using KMeans Clustering

## To Run

```shell
$ python main.py <image path>
```

## Install
- Pillow image library
- Numpy 

## Result
 Orginal Image             |   Quantized Image with 16 clusters
:------------------------: |:------------------------:
![Richard_Hendricks](Richard_Hendricks.jpg) |  ![Compressed_Richard_Hendricks](compressed_richard.jpg)
![Nemo](nemo.jpg) |  ![Compressed_nemo](./quantized_image.jpg)

## TODO
 
- [X] Read Image
- [X] Image to Array
- [X] Kmeans Algo Implement 
- [X] Save Image

## Report

- " Clustering techniques apply when there is no class to be 
predicted but rather when the instances are to be divided into natural 
groups. "
    - — Page 141, [Data Mining: Practical Machine Learning Tools and Techniques](https://amzn.to/2R0G3uG), 2016.

### K Means Clustering
- Kmeans is Centroid-based Clustering
 
#### Main rules

The way K Means algorithm works is as follows:

1. Specify a value for K= the number of clusters to be determined
2. For each of the K clusters, randomly choose an arbitrary point from the dataset as the initial center.
3. For each instance Compute the sum of the squared distance between data points and all centroids. i.e calculate the Euclidean distance between the instance and each of the cluster centers assign the instance to the cluster center with smallest distance
4. For each cluster, calculate a new mean (centroid) based on the instances now in the cluster
Repeat steps 3-4 with the new set of means until there is no change in the centroids or have reached a limit of iterations.

### Euclidean Distance 

Euclidean Distance between  and  is given by: 

$d(X,Y)={\sqrt {(x_{1}-y_{1})^{2}+(x_{2}-y_{2})^{2}}}$

Distance between 2 coordinates can be found with the help of the euclidean distance. If the data is 2 dimensional and is in a plane , n will be 2 in the above formula and can be represented as (x,y) . If it's 3 dimensional data , n will be 3 and can be represented as (x,y,z).

### Centroid Calculation 
    
![centroid](https://miro.medium.com/max/3000/1*hp6P0ePn8zSRzZTZIxL2ig.jpeg)

Now, Consider the black points in the above figure,we need to find the centre of all the black points. We know that this is 2 dimensional data as it has an x and y and is represented as (x,y)
In Order to find the centroid, this is what we do.
Get the x coordinates of all the black points and take mean for that and let’s say it is x_mean.
Do the same for the y coordinates of all the black points and let’s call that y_mean.
Now, the centroid point will be nothing but (x_mean,y_mean) which will result in that red polygon present at the centre of the black points
With this , we have successfully computed the centroids.

## Guide and References
- CHeck this : https://medium.com/analytics-vidhya/k-means-clustering-explained-419ee66d095e
- https://stanford.edu/~cpiech/cs221/handouts/kmeans.html
- [visualizing kmeans clustering](https://stanford.edu/class/engr108/visualizations/kmeans/kmeans.html)
- Kmeans_medium - https://towardsdatascience.com/k-means-clustering-algorithm-applications-evaluation-methods-and-drawbacks-aa03e644b48a
- https://towardsdatascience.com/clustering-evaluation-strategies-98a4006fcfc
- https://afit-r.github.io/kmeans_clustering
- [Sklearn Quntization Color](https://scikit-learn.org/stable/auto_examples/cluster/plot_color_quantization.html)


