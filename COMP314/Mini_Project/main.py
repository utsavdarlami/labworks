from PIL import Image
import sys
import numpy as np

from kmeans import Kmeans_Clustering

"""
    Usage:
        python main.py imgPath --n_clusters nc=16 --max_iter mi=50
"""

def usage(arg,msg="exit"):
    print(f"Argument '{arg}' is not Known")
    print("Usage: \n\tpython main.py imgPath --n_clusters nc=16 --max_iter mi=50")
    print()
    sys.exit(msg)


def is_intstring(s):
    try:
        return int(s)
    except ValueError:
        usage(s,"The argument must be integer. Exit.")

if len(sys.argv) > 6:
    print("To Many Argument : \nUsage: \n\tpython main.py imgPath --n_clusters nc=16 --max_iter mi=50\n")
    sys.exit()

elif len(sys.argv)%2 == 1:
    print("Not Enough Argument : \nUsage: \n\tpython main.py imgPath --n_clusters nc=16 --max_iter mi=50\n")
    sys.exit()

else:
    if len(sys.argv) == 4:
        if sys.argv[2] == "--n_clusters" :
            n_clusters = is_intstring(sys.argv[3])
            max_iter = 50
        else:
            usage(sys.argv[2])

    elif len(sys.argv) == 6 :
        if sys.argv[2] == "--n_clusters" :
            n_clusters = is_intstring(sys.argv[3])
        else:
            usage(sys.argv[2])

        if sys.argv[4] == "--max_iter" :
            max_iter = is_intstring(sys.argv[5])
        else:
            usage(sys.argv[4])
    else:
        n_clusters = 16
        max_iter = 50

image_path = sys.argv[1]

try:
    original_image = Image.open(image_path)

except Exception as err:
    print(err)
    sys.exit()

image_size = original_image.size # (512,512)

w  = image_size[1]
h  = image_size[0]

image_array = np.array(original_image)

image_array.resize(h*w, 3)  # Made 2D array of (row*col , depth)

# Kmeans Clustering
print(f"Performing Kmeans Clustering with {n_clusters} clusters and {max_iter} max iter")

k_algo = Kmeans_Clustering(n_clusters=n_clusters, max_iter=max_iter)

# fitting the clustering model with given image data
k_algo.fit(image_array)

# predicting the final predictions for each pixel
predicted_cluster_ids = k_algo.predict(image_array)

# finding the centroid color for each pixel
only_centroid_value = k_algo.clusters_centers[predicted_cluster_ids]

# changing the array to 3D array as original image size
print("quantizing the image")

clustered_image = np.array(only_centroid_value.reshape(w, h, 3), dtype=np.uint8)

quantized_image = Image.fromarray(clustered_image)

image_name = "quantized_image_" + str(n_clusters) + "_" + str(max_iter)+".jpg"

print(f"Saving the quantized Image as {image_name}")
# quantized_image.save("quantized_image.jpg")
quantized_image.save(image_name)
