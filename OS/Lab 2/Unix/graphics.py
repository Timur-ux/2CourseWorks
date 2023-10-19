import seaborn as sns
import pandas as pd

data = pd.read_csv("./Log.csv")

data.to_excel("Log.xlsx", sheet_name="List1")
