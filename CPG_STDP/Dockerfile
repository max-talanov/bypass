FROM python
RUN pip install neuron
RUN apt update 
RUN apt upgrade 
RUN apt install -y mpich
RUN pip install h5py
COPY . ./bypass/
WORKDIR /bypass/second_layer/neuron+python
RUN nrnivmodl ./mod_files