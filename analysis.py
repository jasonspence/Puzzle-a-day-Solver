import pandas as pd
import matplotlib.pyplot as plt

# Load the CSV file into a DataFrame
file_path = 'data/data.csv'
df = pd.read_csv(file_path)

# Display the first few rows of the DataFrame
print(df.head())

# Group by the first 4 columns
grouped4 = df.groupby(['First blank x', 'First blank y', 'Second blank x', 'Second blank y'])
# Summarize the count of each group
all_solutions_count = grouped4.size().reset_index(name='Count')
# Add a row manually
all_solutions_count.loc[len(all_solutions_count)] = {'First blank x': 0, 'First blank y': 1, 'Second blank x': 1, 'Second blank y': 0, 'Count': 0}
all_solutions_count.loc[len(all_solutions_count)] = {'First blank x': 0, 'First blank y': 4, 'Second blank x': 1, 'Second blank y': 5, 'Count': 0}
all_solutions_count.loc[len(all_solutions_count)] = {'First blank x': 2, 'First blank y': 5, 'Second blank x': 3, 'Second blank y': 6, 'Count': 0}
all_solutions_count.loc[len(all_solutions_count)] = {'First blank x': 4, 'First blank y': 6, 'Second blank x': 5, 'Second blank y': 5, 'Count': 0}
all_solutions_count.loc[len(all_solutions_count)] = {'First blank x': 5, 'First blank y': 0, 'Second blank x': 5, 'Second blank y': 2, 'Count': 0}
all_solutions_count.loc[len(all_solutions_count)] = {'First blank x': 5, 'First blank y': 0, 'Second blank x': 6, 'Second blank y': 1, 'Count': 0}
all_solutions_count.loc[len(all_solutions_count)] = {'First blank x': 5, 'First blank y': 2, 'Second blank x': 6, 'Second blank y': 1, 'Count': 0}
# Sort by counts
all_solutions_count = all_solutions_count.sort_values(by='Count', ascending=False)
print("Pairs head")
print(all_solutions_count.head())
print("Pairs tail")
print(all_solutions_count.tail())
# Output as a CSV
all_solutions_count.to_csv('data/all_solutions_count.csv', index=False)
# Plot a histogram of counts with as many bars as rows
plt.hist(all_solutions_count['Count'], bins=int(len(all_solutions_count)/3))
plt.title('Counts of Pairs of Omitted Positions')
plt.xlabel('Count')
plt.ylabel('Frequency')
plt.show()

# Remove rows where the first point is a day
valid_dates_count = all_solutions_count[all_solutions_count['First blank x'] <= 1]
# Remove rows where the second point is a month
valid_dates_count = valid_dates_count[valid_dates_count['Second blank x'] >= 2]
# Output as a CSV
valid_dates_count.to_csv("data/valid_dates_count.csv", index=False)
# Plot a histogram of counts with as many bars as rows
plt.hist(valid_dates_count['Count'], bins=int(len(valid_dates_count)))
plt.title('Counts of Pairs of Omitted Positions')
plt.xlabel('Count')
plt.ylabel('Frequency')
plt.show()







# Group by the first 2 columns
groupedFirst2 = df.groupby(['First blank x', 'First blank y'])
# Summarize the count of each group
groupedFirst2_count = groupedFirst2.size().reset_index(name='Count')
print("First head")
print(groupedFirst2_count.head())

# Group by the second 2 columns
groupedSecond2 = df.groupby(['Second blank x', 'Second blank y'])
# Summarize the count of each group
groupedSecond2_count = groupedSecond2.size().reset_index(name='Count')
print("Second head")
print(groupedSecond2_count.head())

# Rename the columns of groupedSecond2_count to match grouped2_count
groupedFirst2_count.rename(columns={'First blank x': 'x', 'First blank y': 'y'}, inplace=True)
groupedSecond2_count.rename(columns={'Second blank x': 'x', 'Second blank y': 'y'}, inplace=True)

# Add the values from each table together by matching coordinates
merged_counts = pd.merge(groupedFirst2_count, groupedSecond2_count, on=['x', 'y'], suffixes=('_first', '_second'), how='outer').fillna(0)
merged_counts['Count'] = merged_counts['Count_first'] + merged_counts['Count_second']
#merged_counts.drop(columns=['Count_first', 'Count_second'], inplace=True)
merged_counts['Count'] = merged_counts['Count'].astype(int)
print("Merged head")
print(merged_counts.head())

def plot_heatmap(df):
	# Plot a heatmap where the first column value is the row index, the second column value is the col index, and the Count is the colour saturation
	heatmap = df.pivot(columns='y', index='x', values='Count')
	cmap = plt.cm.hot
	cmap.set_bad(color='gray')
	plt.imshow(heatmap, cmap=cmap, interpolation='nearest')
	plt.title('Heatmap of Solutions Omitting That Position')
	plt.xlabel('y')
	plt.ylabel('x')
	plt.colorbar()
	plt.show()

# Call the function with the DataFrame
plot_heatmap(merged_counts)
