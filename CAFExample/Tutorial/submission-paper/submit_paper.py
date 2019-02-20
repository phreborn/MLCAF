#!/usr/bin/env python
# -*- coding: utf-8 -*-

from CommonAnalysisHelpers import submit
import argparse


def build_task_graph(args):
    """
    Creates the dependency graph of all jobs need to compile a legendary
    paper. This includes
        (1) Generation of scatter data
        (2) Generation of three plots based on the scatter data (parallel)
            The plots are: top view, x- and y-projections
        (3) Compilation of LaTeX file

    The full dependency graph looks like a 'diamond'.

                     (1)
                      Λ
                      |
           -----------------------    
          /           |           \   
       (2 x)        (2 y)       (2 top)
         Λ            Λ            Λ
          \           |           / 
           ----------------------- 
                      |
                     (3)

    The arrows indicate the dependecy. Job (2 x), for example, depends on job
    (1).
    
    The method returns job (3). This is the 'root' of this graph. From job
    (3), job can navigate to all other jobs in the graph following the
    dependency arrows.
    """
    # Generate scatter data
    gen_scatter_data = submit.task("gen_scatter_data",
                                   "pwd; ls; python create_scatter_data.py",
                                   memory=args.memory,
                                   ncores=args.ncores,
                                   time=args.time,
                                   setup=submit.getSetupCommand(args),
                                   outputs=["scatter_data.txt"],
                                   inputs=["config.yml"])

    # Plot x-projection
    plot_x = submit.task("plot_x",
                         "python x_view.py",
                         memory=args.memory,
                         ncores=args.ncores,
                         time=args.time,
                         setup=submit.getSetupCommand(args),
                         outputs=["x.pdf"],
                         dependencies=[gen_scatter_data])

    # Plot y-projection
    plot_y = submit.task("plot_y",
                         "python y_view.py",
                         memory=args.memory,
                         ncores=args.ncores,
                         time=args.time,
                         setup=submit.getSetupCommand(args),
                         outputs=["y.pdf"],
                         dependencies=[gen_scatter_data])

    # Plot top view
    plot_top =  # TODO: add the definition of the top view task

    # Compile paper
    paper =  # TODO: add the distribution of the pdflatex task

    return paper


def submit_root_task(args, task):
    """
    Guesses the submission controller and submits the root job to the batch
    system.
    """
    # TODO: Implement this method

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Script to submit a 'Hello World' job")
    submit.configureDefaultArgumentParser(parser)
    args = parser.parse_args()

    root_task = build_task_graph(args)
    submit_root_task(args, root_task)
