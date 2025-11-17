# Traffic

The data set can be viewed by opening the gtsrb directory. You’ll notice 43 subdirectories in this dataset, numbered 0 through 42. Each numbered subdirectory represents a different category (a different type of road sign). Within each traffic sign’s directory is a collection of images of that type of traffic sign.

Next, take a look at traffic.py. In the main function, we accept as command-line arguments a directory containing the data and (optionally) a filename to which to save the trained model. The data and corresponding labels are then loaded from the data directory (via the load_data function) and split into training and testing sets. After that, the get_model function is called to obtain a compiled neural network that is then fitted on the training data. The model is then evaluated on the testing data. Finally, if a model filename was provided, the trained model is saved to disk.

Our model that contains:
- 2 Convolutional Layers (reLU activated)
- 2 Max Pooling layers (size 2 by 2)
- A flatten layer
- A dense layer
- A dropout layer
- Output layer (softmax)
<a/>
Manage to achieve 92% accuracy when evaluated with test data.
