import argparse
import yaml
from src.Sim import Simulation
import os

def openYAML(probname):

    with open("inputs/inputs.yml", "r") as f:
        config = yaml.safe_load(f)
        f.close()

    simparams = config[probname]
    return simparams

if __name__ == "__main__":

    parser = argparse.ArgumentParser()

    parser.add_argument(
        "--problem",
        type=str,
        help="Problem name in input yml file and name of script in src/pgen"
    )

    parser.add_argument(
        "--outpath",
        type=str,
        help="Output directory for simulation data to be saved"
    )

    parser.add_argument(
        "--outfile",
        type=str,
        help="Output file for simulation data to be saved without padded iteration number or .h5 extension"
    )

    parser.add_argument(
        "--savefreq",
        type=int,
        help="Frequency of data output dumps in iterations"
    )

    args = parser.parse_args()

    problemname = args.problem

    simparams = openYAML(probname=problemname)

    # Check if outpath exists, if not, create it
    if os.path.isdir(args.outpath) == False:
        os.mkdir(f"{args.outpath}")

    # Setting up simulation object 
    sim = Simulation(simparams, args)

    print(f"[UPDATE] Initializing simulation with problem {problemname}...")
    sim.Initialize()

    print(f"[UPDATE] Finished initializing, running simulation for {problemname}...")
    sim.Run()
    print(f"[FINISHED] Run complete, please see specified {args.outpath} for saved data")
