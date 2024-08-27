import numpy as np
import bokeh
from bokeh.plotting import figure, show, output_notebook, output_file
from bokeh.models import Range1d

bokeh.sampledata.download()
directory_path = '.'
# Ensure the output is displayed in the notebook
output_notebook()

# Prepare the data
x = np.linspace(-60, 60, 121)
y = np.sin(x / 10) * 50  # example data
y_err = np.random.normal(5, 2, len(x))  # example error data

# Create a new plot with a title and axis labels
p = figure(x_axis_label='Δt [ms]', y_axis_label='ΔG [%]', width=600, height=400)

p.xaxis.axis_label_text_font_style = "bold"
p.yaxis.axis_label_text_font_style = "bold"
p.xaxis.major_label_text_font_style = "bold"
p.yaxis.major_label_text_font_style = "bold"

# Add the main plot
p.line(x, y, legend_label="ΔG", line_width=2, color="red")
p.scatter(x, y, size=8, color="red", alpha=0.6)
p.y_range = Range1d(-100, 100)

# Adding error bars
p.multi_line(xs=[[x[i], x[i]] for i in range(len(x))],
             ys=[[y[i] - y_err[i], y[i] + y_err[i]] for i in range(len(x))],
             color="red")

p.yaxis.ticker = [-100, -75, -50, -25, 0, 25, 50, 75, 100]

# Show the plots
output_file('Oci.html')
show(p)
