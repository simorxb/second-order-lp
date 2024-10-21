import control as ct
import numpy as np
import math
import matplotlib.pyplot as plt
import pandas as pd

s = ct.TransferFunction.s

# Parameters
tau1 = 1
tau2 = 3

# Filter transfer function
F = 1/((tau1*s+1)*(tau2*s + 1))

# Step response - nominal - output
t_L, yout_L = ct.step_response(F, T=20)
plt.figure()
plt.plot(t_L, yout_L, label="Second Order Low Pass Filter")
plt.grid()
plt.title("Step response - nominal")

# Read data from data.txt into a pandas DataFrame
data = pd.read_csv('data.txt', delim_whitespace=True, names=["Time", "Input", "Output"])

# Plot response from C code
plt.figure()
plt.plot(t_L, yout_L, label=f"Response - Ideal")
plt.plot(data["Time"], data["Output"], label=f"Response - from C Code")
plt.xlabel("Time [s]")
plt.legend()
plt.grid()

# Show plots
plt.show()