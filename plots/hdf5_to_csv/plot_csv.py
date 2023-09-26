import pandas as pd
import matplotlib.pyplot as plt

# Load the data from the CSV file into a pandas DataFrame
data = pd.read_csv('csv\\new_rat4_muscle_F_speed_50_layers_21_eeshz_40.csv')

# Assuming your CSV file has a single column named 'value'
values_st0 = data['#0_step_0']
values_st1 = data['#0_step_1']

# Initialize lists to store the points where the trend changes


def get_change_points(values):
    # Iterate through the data
    change_points_x = []
    change_points_y = []
    
    # Initialize variables to keep track of the previous data point and the current trend direction
    prev_value = values.iloc[0]
    trend_direction = None  # 'upward' or 'downward'

    for i in range(1, len(values)):
        current_value = values.iloc[i]

        if current_value > prev_value:
            if trend_direction != 'upward':
                trend_direction = 'upward'
                change_points_x.append(i)
                change_points_y.append(current_value)
        elif current_value < prev_value:
            if trend_direction != 'downward':
                trend_direction = 'downward'
                change_points_x.append(i)
                change_points_y.append(current_value)
        # If current_value is equal to prev_value, there is no change in trend.

        prev_value = current_value
    return change_points_x, change_points_y

change_points_x_st0, change_points_y_st0  = get_change_points(values_st0)
change_points_x_st1, change_points_y_st1  = get_change_points(values_st1)
    
# Plot the original data
#plt.plot(values_st0, label='Pre-synaptic spikes')
#plt.plot(values_st1, label='Post-synaptic spikes')

# Plot the points where the trend changes
plt.scatter(change_points_x_st0, change_points_y_st0, c='red', marker='o', label='Change Points')
plt.scatter(change_points_x_st1, change_points_y_st1, c='green', marker='o', label='Change Points')

# Customize the plot
plt.xlabel('Index')
plt.ylabel('Value')
plt.legend()
plt.title('Trend Change Points')

# Show the plot
plt.grid(True)
plt.show()