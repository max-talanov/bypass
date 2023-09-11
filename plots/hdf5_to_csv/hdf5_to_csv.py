import h5py
import os
import pandas as pd
import matplotlib.pyplot as plt
pjoin = os.path.join

root_dir = os.path.dirname(os.path.realpath(__file__))



def convert_hdf5_files_to_csv(hdf5_folder, output_csv_folder, output_plot_folder):
    try:
        # Create output folders if they don't exist
        if not os.path.exists(output_csv_folder):
            os.makedirs(output_csv_folder)
        if not os.path.exists(output_plot_folder):
            os.makedirs(output_plot_folder)

        # List all HDF5 files in the input folder
        hdf5_files = [f for f in os.listdir(hdf5_folder) if f.endswith(".hdf5")]

        for hdf5_file in hdf5_files:
            input_hdf5_file = os.path.join(hdf5_folder, hdf5_file)
            output_csv_file = os.path.join(output_csv_folder, hdf5_file.replace(".hdf5", ".csv"))

            # Convert HDF5 to CSV and plot
            hdf5_to_csv_and_plot(input_hdf5_file, output_csv_file, output_plot_folder)

    except Exception as e:
        print(f"An error occurred: {str(e)}")


def hdf5_to_csv_and_plot(input_hdf5_file, output_csv_file, output_plot_folder):
    try:
        # Open the HDF5 file for reading
        with h5py.File(input_hdf5_file, 'r') as hdf5_file:
            filename = os.path.splitext(os.path.basename(output_csv_file))[0]
            # Extract the data from the HDF5 file into a Pandas DataFrame
            data = {key: hdf5_file[key][:] for key in hdf5_file.keys()}
            df = pd.DataFrame(data)

            # Save the DataFrame to a CSV file
            df.to_csv(output_csv_file, index=False)
            print(f"Conversion completed. CSV file saved as {output_csv_file}")

            # Plot Column1
            plt.figure(figsize=(10, 6))
            plt.plot(df['#0_step_0'])
            plt.xlabel('Time (ms)')
            plt.ylabel('Voltage (mV)')
            plt.title(filename + '_#0_step_0')
            plt.grid(True)

            # Save the plot as an image file
            column1_plot_file = output_plot_folder + "/" + filename + "_0.png"
            plt.savefig(column1_plot_file)
            print(f"Column1 plot saved as {column1_plot_file}")

            # Show the plot (optional)
            # plt.show()

            # Plot Column2
            plt.figure(figsize=(10, 6))
            plt.plot(df['#0_step_1'])
            plt.xlabel('Time (ms)')
            plt.ylabel('Voltage (mV)')
            plt.title(filename + '_#0_step_1')
            plt.grid(True)

            # Save the plot as an image file
            column2_plot_file = output_plot_folder + "/" + filename + "_1.png"
            plt.savefig(column2_plot_file)
            print(f"Column2 plot saved as {column2_plot_file}")

            # Show the plot (optional)
            # plt.show()

    except Exception as e:
        print(f"An error occurred: {str(e)}")


if __name__ == "__main__":
    current_path = os.path.realpath(__file__)
    hdf5_folder = pjoin(root_dir,'hdf5')
    output_csv_folder = pjoin(root_dir,'csv')
    output_plot_folder = pjoin(root_dir,'plots')

    convert_hdf5_files_to_csv(hdf5_folder, output_csv_folder, output_plot_folder)
