import numpy as np
import matplotlib.pyplot as plt
from scipy import stats
import seaborn as sns; sns.set()
from sklearn.svm import SVR
model = SVC(kernel='rbf', C=1E10) # C adjusts sensitivity for misclassifications
model.fit(X, y)

def main():
  arr = ["No Risk", "Low Risk", "Moderate Risk", "High Risk"]
  csv = np.genfromtext('Dataset_-_CBRE_Challenge_-_HackSMU_2023.csv', delimiter = ",")
  
def formatData():
  numArr
  
  return numArr