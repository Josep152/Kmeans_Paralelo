import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv('../points_cluster_2.csv')

x = []
y = []
color = []

for e in df['x']:
    x.append(e)
for e in df['y']:
    y.append(e)
for e in df['color']:
    color.append(e)

# Datos 
color_dict = {0:'blue', 1:'red', 2:'green', 3:'yellow', 4: 'darkviolet'}
color = [color_dict[label] for label in color]

# Gráfico
fig, ax = plt.subplots()
ax.scatter(x, y, c = color)
plt.show()
