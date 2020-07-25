import pandas as pd
from patsy import dmatrices
import numpy as np
import statsmodels.api as sm
import matplotlib.pyplot as plt
import time


# Create a pandas DataFrame for the counts data set.
df = pd.read_csv('clean_data.csv', header=0, infer_datetime_format=True)

print(df.head())
print(df.index)

time.sleep(30)


# Create the training and testing data sets.
mask = np.random.rand(len(df)) < 0.8
df_train = df[mask]
df_test = df[~mask]
print('Training data set length='+str(len(df_train)))
print('Testing data set length='+str(len(df_test)))

print(df_train.head())
print(df_test.head())


# Setup the regression expression in patsy notation. We are telling patsy that packets_4 is our dependent variable and
# it depends on the regression variables: packets_1, packets_2, and packets_3.
expr = """packets_4 ~ packets_1 + packets_2 + packets_3"""

# Set up the X and y matrices
y_train, X_train = dmatrices(expr, df_train, return_type='dataframe')
y_test, X_test = dmatrices(expr, df_test, return_type='dataframe')

# Using the statsmodels GLM class, train the Poisson regression model on the training data set.
poisson_training_results = sm.GLM(y_train, X_train, family=sm.families.Poisson()).fit()

# Print the training summary.
print(poisson_training_results.summary())

# Make some predictions on the test data set.
poisson_predictions = poisson_training_results.get_prediction(X_test)

# .summary_frame() returns a pandas DataFrame
predictions_summary_frame = poisson_predictions.summary_frame()
print(predictions_summary_frame)

predicted_traffic= predictions_summary_frame['mean']
actual_traffic = y_test['packets_4']

# Plot the predicted traffic versus the actual traffic for the test data.
fig = plt.figure()
fig.suptitle('Predicted versus Actual traffic')
predicted, = plt.plot(X_test.index, predicted_traffic, 'go-', label='Predicted Traffic')
actual, = plt.plot(X_test.index, actual_traffic, 'ro-', label='Actual Traffic')
plt.legend(handles=[predicted, actual])
plt.savefig("predict_actual.png")
plt.show()

# Show scatter plot of Actual versus Predicted Traffic
plt.clf()
fig = plt.figure()
fig.suptitle('Scatter plot of Actual versus Predicted counts')
plt.scatter(x=predicted_traffic, y=actual_traffic, marker='.')
plt.xlabel('Predicted counts')
plt.ylabel('Actual counts')
plt.savefig("predict_scatter.png")
plt.show()
