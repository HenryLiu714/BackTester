import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from datetime import datetime

columns = ["Date", "Equity"]
df = pd.read_csv("output/equity_curve.csv", usecols=columns)
pd.to_datetime(df['Date'])

fig, ax = plt.subplots()
fig.subplots_adjust(bottom=0.15, left=0.15)

plot = plt.plot(df.Date, df.Equity)

plt.xlabel("Date")
plt.ylabel("Total Equity")
plt.title("Equity Curve")
plt.xticks([df.Date.iloc[0], df.Date.iloc[-1]], visible=True, rotation=0)


plt.savefig("output/plot.png")

