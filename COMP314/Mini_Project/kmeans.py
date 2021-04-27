import numpy as np

class Kmeans_Clustering:

    def __init__(self, n_clusters = 16, max_iter=300, tol=0.0001):
        """ n_clusters is no of clusters"""
        self.n_clusters = n_clusters
        self.clusters_centers = np.zeros((self.n_clusters,3))
        self.max_iter = max_iter
        self.tol = tol
        self._labels = None
        self.cost = 1000

    def __random_cluster_centroid(self,matrix_data,row): # Private function
        choice = np.random.randint(0,row,size=self.n_clusters)
        for idx,c in enumerate(choice):
            self.clusters_centers[idx] = matrix_data[c]

    def __predict_labels(self,matrix_data): # private function
        """
        Labels Update according to Centroid.
        """
        distance_point_centroid = np.sqrt(((matrix_data[:,:,None] - self.clusters_centers.T[None,:,:])**2).sum(axis=1))
        self._labels = np.argmin(distance_point_centroid,axis=1)

    def __update_centroid(self,matrix_data): # private function
        """
        Centroid Update according to the Labels.
        """
        for cid in range(self.n_clusters):
            cluster_member_idx = np.where(self._labels==cid)[0]
            if len(cluster_member_idx)==0:
                self.clusters_centers[cid] = np.array([0,0,0])
            else:
                self.clusters_centers[cid] = np.mean(matrix_data[cluster_member_idx],axis=0)

    def __cost(self,matrix_data): # private function
        """
        Calculate the cost of the centroid in each iterations
        """
        centroid_idx_value = self.clusters_centers[self._labels]
        rse = np.sqrt(((matrix_data - centroid_idx_value)**2).sum(axis=1))
        return rse.mean()

    def fit(self,matrix_data):
        """ find cluster centers for the data """
        try:
            if len(matrix_data.shape) != 2:
                print("Data wrong for fit")
            else:
                print("fitting the data")
                row = matrix_data.shape[0]
                self.__random_cluster_centroid(matrix_data,row)
                self._labels = np.zeros(shape=row)

                for go_iter in range(self.max_iter):

                    """
                    Labels Update according to Centroid.
                    """
                    self.__predict_labels(matrix_data)


                    """
                    Centroid Update according to the Labels.
                    """
                    self.__update_centroid(matrix_data)

                    """
                    Cost Update
                    """
                    new_cost = self.__cost(matrix_data)
                    print(f"at {go_iter} iteration cost is {new_cost}")
                    if -self.tol <= self.cost - new_cost <= self.tol:
                        break
                    else:
                        self.cost = new_cost

            print(f"Done fitting at {go_iter} iteration")

        except Exception as err:
            print(err)

    def predict(self,matrix_data):
        """Returns labels array for given data"""
        if self.clusters_centers is not None:
            print("predicting cluster id for the data")
            self._labels = np.zeros(shape=matrix_data.shape[0])
            self.__predict_labels(matrix_data)
            print("Done predicting")
        else:
            print("Fitting The given data first before predicting")
            self.fit(matrix_data)
            self.predict(matrix_data)
        return self._labels
