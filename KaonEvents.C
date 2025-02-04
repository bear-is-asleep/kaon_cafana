#include "sbnana/CAFAna/Core/Spectrum.h"
#include "sbnana/CAFAna/Core/SpectrumLoader.h"
#include "sbnanaobj/StandardRecord/Proxy/SRProxy.h"
#include "sbnana/SBNAna/Cuts/VolumeDefinitions.h"
#include "sbnana/CAFAna/Cuts/TruthCuts.h"
#include "sbnana/CAFAna/Core/Var.h"
#include "sbnana/CAFAna/Core/Binning.h"
#include "sbnana/SBNAna/Cuts/Cuts.h"
#include "sbnana/CAFAna/Core/MultiVar.h"

#include "sbnanaobj/StandardRecord/SRTrueInteraction.h"

//My includes
using namespace ana;
#include "headers/KaonTrueVars.h"
#include "headers/KaonRecoVars.h"

#include <string>
#include <iostream>
#include <fstream>
#include "TVector.h"
#include "TTree.h"
#include "TFile.h"
#include "TString.h"


const std::string inputName = "/exp/sbnd/data/users/brindenc/analyze_sbnd/kaon/v09_91_02/single.flat.caf.root";
const TString saveName = "/exp/sbnd/data/users/brindenc/analyze_sbnd/kaon/v09_91_02/single.root";

void KaonEvents()
{
  //Vectors to store variables
  vector<int> run;
  vector<int> subrun;
  vector<int> evt;
  vector<int> slcid;
  vector<int> kid;

  //True values
  vector<double> true_kaon_energy;

  //Reco values
  vector<double> reco_kaon_length;


  // Make TTree
  TFile* file = new TFile(saveName, "RECREATE");
  TTree *tree = new TTree("rectree","CAF Tree");

  //Tree branches - the string is what it's saved as in the root file
  tree->Branch("run",&run);
  tree->Branch("subrun",&subrun);
  tree->Branch("evt",&evt);
  
  tree->Branch("true_kaon_energy", &true_kaon_energy);
  tree->Branch("reco_kaon_length", &reco_kaon_length);
  /*You don't need these*/
  //tree->Branch("slcid", &slcid);
  //tree->Branch("kaonid", &kid);


  SpectrumLoader loader(inputName);

  const SpillVar dummy_var([&](const caf::SRSpillProxy* sp){
    run.push_back(sp->hdr.run);
    subrun.push_back(sp->hdr.subrun);
    evt.push_back(sp->hdr.evt);
    
    //true_kaon_energy.push_back(kKaonTrueEnergy(sp));
    true_kaon_energy.push_back(kMCKaonEnergy(sp));
    reco_kaon_length.push_back(kKaonLength(sp));

    //slcid.push_back(kTrueBestSlice(sp));
    //kid.push_back(kTrueKaonID(sp));
    //kMCKaonID(sp);
    //kTrueVarKaonID(sp);


    return 0;
  });

  const Binning dummy_bins = Binning::Simple(2, 0, 2);
  Spectrum dummy_spec("Dummy Label", dummy_bins, loader, dummy_var, kNoSpillCut);

  loader.Go();

  tree->Fill();
  file->Write();
  file->Close();

}