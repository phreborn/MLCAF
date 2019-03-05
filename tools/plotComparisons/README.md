# Plot Comparisons
This tool allows to make quick comparison plots between different processes at different
cut stages and for several observables. It uses the general concepts of patches and tags
in CAF including a config file for steering this script.

### Producing your own comparison plots

In order to make a new plot comparison you need to do the following:

   1. Adapt the config file 'plotComparisons.cfg' (or write a new one) to your needs
   2. Adapt the style file 'style-plotComparisons.txt' (or write a new one) to your needs
   3. Run the plotComparison.py script with:
       `python plotComparisons.py <plotCategory>`,
       where `<plotCategory>` specifies the desired section in your config file.

Note, that you can also write your own config and style files and point to them accordingly:
For pointing to a new config file please specify the '--config' argument when running the python script.
For pointing to a new style file please adapt the 'patches' tag in your config.

### Run the example
For running the example simply execute (assuming you are in the share directory):

```bash
python ../tools/plotComparisons/plotComparisons.py PFlowVsEMTopoRatio
python ../tools/plotComparisons/plotComparisons.py PFlowVsEMTopo
```

Note, you have to be subscribed to the qframework-users email list in order to have access to the example sample folder.