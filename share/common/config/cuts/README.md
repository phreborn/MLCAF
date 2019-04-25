Cuts
=========================

The cuts for the analysis can and should be defined with an external
configuration file. 

Usage
--------------------

The syntax is the `TQFolder` text syntax, which follows the general idea
of constructing the cut hierarchy as a tree of `TQFolders`, and then
converting these into instances of `TQCut`.

    # This is a comment.
    +CutBase { # this is a new folder and soon-to-be cut. there is no folder above, so this is the base cut
    # The tags '.cutExpression' and '.weightExpression' will become the cut and weight expressions of the `TQCut`.
      +CutLeptonPt { # this is a new child cut of CutBase
        <.cutExpression="lepton_pts[0] > $(lepPtCut) * 1000.", .weightExpression = "1.">
      }   
    }

Please note the use of the string `$(lepPtCut)` in the above
expression. This is a placeholder variable that will be filled by the
code at runtime. There are several ways to give such placeholder
variables meaning:

 * The values can be defined as a global `alias`. Aliases are
   basically global string-replacements that you can define in a
   separate config file in order to keep your files human-readable.

 * In cases where different values should be used for different
   samples (or groups thereof), the individual values can be defined
   as tags on the sample folder hierarchy. These can be defined in
   `patches` that you can apply to your sample folder at will.

Alternatively cuts can be defined via python snippets in place of TQFolder syntax based files (they need to be listed in the master config just like the TQFolder syntax ones). Their structure is as follows:
```
from CommonAnalysisHelpers.analyze import PyCut
def addCuts(config,baseCut):
  #the baseCut is just a dummy cut used to add your own cuts.
  #use += if you want to continue assigning more subsequent cuts
  baseCut+= PyCut("CutChannels", cut="$(fitsChannel)", weight="Weight_$(weightname):$(cand)", options={".title":"Channel Selection"} )
  #the next line then adds "CutVgammaVjet_overlap" as a sub-cut of "CutChannels"
  baseCut+= PyCut("CutVgammaVjet_overlap", cut="{ $(isVjets) ? $(Truth_hasFSRPhotonDR01)==0 : 1 }", options={".title":"Overlap: Vgamma/Vjets"} )
  #accessing a cut that was defined earlier (e.g. to create a second branch of cuts):
  cutChannels = baseCut["CutChannels"]
  cutChannels+= PyCut("CutVgammaVjet_overlap_invert", cut="{ $(isVjets) ? $(Truth_hasFSRPhotonDR01)>0 : 0 }", options={".title":"Inverted Overlap: Vgamma/Vjets"} )
  #...more manipulation/cut definitions...
  #if everything went fine, return True
  return True
```

Advanced Features
--------------------

For complicated analyses, your cut hierarchy can get quite
large. However, the `TQFolder` text syntax is very powerful and can be
exploited to keep your config files nice and clean. Consider, for
example, a case where you want to attach the same set of cuts to
multiple regions.

    +ChannelSelection{
      <.cutExpression="EventType=$(channelEnum)", .weightExpression="mcEventWeight">
      +CutA {
        <.cutExpression="$(VarA)>20.">
        +CutB {
          <.cutExpression="$(VarB)<30.">
          +CR_Bkg1 {
            <.cutExpression="$(lepPt1)<30.">        
          }     
          +CR_Bkg2 {
            <.cutExpression="$(lepPt2)<30.">        
          }
        }
      }
    }
    
    @*/CR_*{
      +BDTcut {
        <.name="BDTcut_$(CR)",.cutExpression="[MVA:tmva_xmls/mybdttraining.xml]>0.1">
        +MTcut {
          <.name="MTcut_$(CR)",.cutExpression="$(MT)>30">
        }
      }
    }
    
    $replace("*/CR_Bkg1/*:.name",CR="CR_Bkg1");
    $replace("*/CR_Bkg2/*:.name",CR="CR_Bkg2");

Note how the `@*/CR_*` selects all folders matching a certain path,
such that then, the same block of additional cuts can be created
there.  Then, in order to make each cut have a unique name (which is a
requirement of the framework), the `$replace` command is used to
replace the placeholder `$(CR)` in the `.name` tag with the
corresponding name component.