import numpy as np
import bokeh
from bokeh.plotting import figure, show, output_notebook, output_file
from bokeh.models import Range1d

bokeh.sampledata.download()
directory_path = '.'
# Ensure the output is displayed in the notebook
output_notebook()

# Prepare the data
x = np.linspace(-10, 10, 21)
y = np.array([0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 90, 80, 70, 60, 50, 40, 30, 20, 10, 0])
y_err = np.array([5] * 21)

# Create a new plot with a title and axis labels
p = figure(title="ΔG vs Δt", x_axis_label='Δt [s]', y_axis_label='ΔG [%]', width=600, height=400)

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

# Create an inset plot
inset = figure(width=200, height=200,
               x_axis_label='t (s)', y_axis_label='Δt',
               title="Inset Plot",
               x_range=Range1d(0, 20), y_range=Range1d(-0.2, 0.6))

# Add the inset data
inset.line([0, 5, 15, 20], [0, 0.6, 0.6, 0], color="red", line_width=2)
inset.line([0, 5, 15, 20], [0, -0.2, -0.2, 0], color="black", line_width=2)

# Show the plots
output_file('Oci.html')
show(p)
show(inset)
