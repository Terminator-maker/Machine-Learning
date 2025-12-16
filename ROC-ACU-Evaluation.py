# Pouya Belali - 4011193003

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# Step 1: Data Initialization
# Data format: [Bias, Size, Price, Label]
dataset = [
    [0, 1, 1, 0],
    [0, 2, 1, 0],
    [0, 3, 2, 0],
    [0, 3, 5, 1],
    [0, 2, 4, 1]
]

data_array = np.array(dataset)

X = data_array[:, 0:3]
Y = data_array[:, 3]

weights = np.array([0.5, 0.5, 0.5])
learning_rate = 0.01
epochs = 2000
def sigmoid(z):
    return 1 / (1 + np.exp(-z))

# Step 2: Training (Gradient Ascent)
print("Training started...")

for i in range(epochs):
    z = np.dot(X, weights)
    
    predictions = sigmoid(z)
    error = Y - predictions
    gradient = np.dot(X.T, error)
    
    weights = weights + learning_rate * gradient

print("Training finished.")
print("Final Weights:", weights)
print("-" * 30)

# Step 3: Final Predictions
final_z = np.dot(X, weights)
final_probs = sigmoid(final_z)

y_pred_class = []
for p in final_probs:
    if p >= 0.5:
        y_pred_class.append(1)
    else:
        y_pred_class.append(0)
        
TP = 0
TN = 0
FP = 0
FN = 0

for i in range(len(Y)):
    actual = Y[i]
    pred = y_pred_class[i]
    
    if actual == 1:
        if pred == 1:
            TP = TP + 1
        else:
            FN = FN + 1
    else:
        if pred == 0:
            TN = TN + 1
        else:
            FP = FP + 1

# Calculate Metrics (Accuracy, Precision, Recall, F1)
accuracy = (TP + TN) / len(Y)

if (TP + FP) == 0:
    precision = 0
else:
    precision = TP / (TP + FP)

if (TP + FN) == 0:
    recall = 0
else:
    recall = TP / (TP + FN)

if (precision + recall) == 0:
    f1_score = 0
else:
    f1_score = 2 * (precision * recall) / (precision + recall)

# Step 4: ROC Curve Calculation
tpr_list = [0]
fpr_list = [0]

sorted_thresholds = np.sort(final_probs)
sorted_thresholds = sorted_thresholds[::-1]

for threshold in sorted_thresholds:
    temp_preds = []
    for prob in final_probs:
        if prob >= threshold:
            temp_preds.append(1)
        else:
            temp_preds.append(0)
    
    temp_TP = 0
    temp_FP = 0
    temp_TN = 0
    temp_FN = 0
    
    for i in range(len(Y)):
        if Y[i] == 1:
            if temp_preds[i] == 1:
                temp_TP = temp_TP + 1
            else:
                temp_FN = temp_FN + 1
        else:
            if temp_preds[i] == 1:
                temp_FP = temp_FP + 1
            else:
                temp_TN = temp_TN + 1
    
    if (temp_TP + temp_FN) == 0:
        current_tpr = 0
    else:
        current_tpr = temp_TP / (temp_TP + temp_FN)
        
    if (temp_FP + temp_TN) == 0:
        current_fpr = 0
    else:
        current_fpr = temp_FP / (temp_FP + temp_TN)
        
    tpr_list.append(current_tpr)
    fpr_list.append(current_fpr)

# Step 5: Plot

# Plot ROC Curve
plt.figure(figsize=(6, 6))
plt.plot(fpr_list, tpr_list, color='blue', marker='o', label='ROC Curve')
plt.plot([0, 1], [0, 1], color='red', linestyle='--', label='Random Guess')
plt.title('ROC Curve')
plt.xlabel('False Positive Rate (FPR)')
plt.ylabel('True Positive Rate (TPR)')
plt.legend()
plt.grid(True)
plt.show()

metrics_dict = {
    'Metric': ['Accuracy', 'Precision', 'Recall', 'F1 Score'],
    'Value': [accuracy, precision, recall, f1_score]
}

results_df = pd.DataFrame(metrics_dict)
print("\nEvaluation Results:")
print(results_df)
