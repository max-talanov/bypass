import h5py
import pandas as pd

def hdf5_to_csv(input_hdf5_file, output_csv_file):
    try:
        # Open the HDF5 file for reading
        with h5py.File(input_hdf5_file, 'r') as hdf5_file:
            # Extract the data from the HDF5 file into a Pandas DataFrame
            data = {key: hdf5_file[key][:] for key in hdf5_file.keys()}
            df = pd.DataFrame(data)

            # Save the DataFrame to a CSV file
            df.to_csv(output_csv_file, index=False)
            print(f"Conversion completed. CSV file saved as {output_csv_file}")
    except Exception as e:
        print(f"An error occurred: {str(e)}")

hdf5_to_csv('new_rat4_muscle_F_speed_50_layers_21_eeshz_40.hdf5', 'new_rat4_muscle_F_speed_50_layers_21_eeshz_40.csv')
hdf5_to_csv('new_rat4_muscle_E_speed_50_layers_21_eeshz_40.hdf5', 'new_rat4_muscle_E_speed_50_layers_21_eeshz_40.csv')
hdf5_to_csv('new_rat4_mns_F_speed_50_layers_21_eeshz_40.hdf5', 'new_rat4_mns_F_speed_50_layers_21_eeshz_40.csv')
hdf5_to_csv('new_rat4_mns_E_speed_50_layers_21_eeshz_40.hdf5', 'new_rat4_mns_E_speed_50_layers_21_eeshz_40.csv')
hdf5_to_csv('new_rat4_mem_muscle_F_speed_50_layers_21_eeshz_40.hdf5', 'new_rat4_mem_muscle_F_speed_50_layers_21_eeshz_40.csv')
hdf5_to_csv('new_rat4_mem_muscle_E_speed_50_layers_21_eeshz_40.hdf5', 'new_rat4_mem_muscle_E_speed_50_layers_21_eeshz_40.csv')
hdf5_to_csv('new_rat4_mem_mns_F_speed_50_layers_21_eeshz_40.hdf5', 'new_rat4_mem_mns_F_speed_50_layers_21_eeshz_40.csv')
hdf5_to_csv('new_rat4_mem_mns_E_speed_50_layers_21_eeshz_40.hdf5', 'new_rat4_mem_mns_E_speed_50_layers_21_eeshz_40.csv')
