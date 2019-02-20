#!/usr/bin/env python

import yaml
import numpy

with open("config.yml") as config_file:
    config = yaml.load(config_file)

x = config["x"]
y = config["y"]
rho = config["correlation"]
n = config["n"]

data = numpy.random.multivariate_normal(
    [x["mean"], y["mean"]],                            # Mean values
    [[x["width"]**2, x["width"] * y["width"] * rho],   # Covariance matrix
     [x["width"] * y["width"] * rho, y["width"]**2]],
    size=n)                                            # Number of samples

numpy.savetxt("scatter_data.txt", data)
