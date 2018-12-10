#!/usr/bin/env python

from CommonAnalysisHelpers import submit
import argparse


def submit_hello_world_job(args):
    """
    Creates a 'Hello World' job and sends it to the available submission
    controller.
    """
    task = submit.task("hello_world", "sleep 60; touch hello_world.txt",
                       memory=args.memory,
                       ncores=args.ncores,
                       time=args.time,
                       setup=submit.getSetupCommand(args),
                       outputs=["hello_world.txt"])

    controller = submit.guessSubmissionController()
    controller.submitTasks(args, [task])

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Script to submit a 'Hello World' job")
    submit.configureDefaultArgumentParser(parser)
    args = parser.parse_args()

    submit_hello_world_job(args)
