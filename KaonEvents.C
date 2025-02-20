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


//const std::string inputName = "/exp/sbnd/data/users/brindenc/analyze_sbnd/kaon/v09_91_02/single.flat.caf.root";
//const TString saveName = "/exp/sbnd/data/users/brindenc/analyze_sbnd/kaon/v09_91_02/single.root";

const std::string inputName = "/exp/sbnd/data/users/perezmos/SwappedAna/Trees/Trial/prodgenie_bnb_nu_filtered_CCSingleKplus_sbnd_20250205T233418_gen_G4-20250205T234453_DetSim-20250205T235753_Reco1-20250205T235955_Reco2-20250206T000649.flat.caf.root";
const TString saveName = "/exp/sbnd/data/users/brindenc/analyze_sbnd/kaon/v09_91_02/singlev3.root";
void KaonEvents()
{
  //Vectors to store variables
  vector<int> run;
  vector<int> subrun;
  vector<int> evt;
  vector<int> slcid;
  vector<int> kid;

  //True values
  //vector<double> true_kaon_energy;
  vector<double> stX, stY, stZ, enX, enY, enZ;
  vector<double> Px, Py, Pz, p, E, phi, theta;

  //Reco values
  //vector<double> reco_kaon_length;
  vector<double> reco_k_stX, reco_k_stY, reco_k_stZ;
  vector<double> reco_k_enX, reco_k_enY, reco_k_enZ;
  vector<double> reco_k_phi, reco_k_theta;
  vector<double> reco_k_purity, reco_k_completeness;


  // Make TTree
  TFile* file = new TFile(saveName, "RECREATE");
  TTree *tree = new TTree("rectree","CAF Tree");

  //Tree branches - the string is what it's saved as in the root file
  tree->Branch("run",&run);
  tree->Branch("subrun",&subrun);
  tree->Branch("evt",&evt);
  
  //tree->Branch("true_kaon_energy", &true_kaon_energy);
  //tree->Branch("reco_kaon_length", &reco_kaon_length);
  /*You don't need these*/
  //tree->Branch("slcid", &slcid);
  //tree->Branch("kaonid", &kid);

  // True position branches
  tree->Branch("stX", &stX);
  tree->Branch("stY", &stY);
  tree->Branch("stZ", &stZ);
  tree->Branch("enX", &enX);
  tree->Branch("enY", &enY);
  tree->Branch("enZ", &enZ);

  // True momentum and energy branches
  tree->Branch("Px", &Px);
  tree->Branch("Py", &Py);
  tree->Branch("Pz", &Pz);
  tree->Branch("p", &p);
  tree->Branch("E", &E);

  // True angular branches
  tree->Branch("phi", &phi);
  tree->Branch("theta", &theta);

  // Reco position branches
  tree->Branch("reco_k_stX", &reco_k_stX);
  tree->Branch("reco_k_stY", &reco_k_stY);
  tree->Branch("reco_k_stZ", &reco_k_stZ);
  tree->Branch("reco_k_enX", &reco_k_enX);
  tree->Branch("reco_k_enY", &reco_k_enY);
  tree->Branch("reco_k_enZ", &reco_k_enZ);

  // Reco angular branches
  tree->Branch("reco_k_phi", &reco_k_phi);
  tree->Branch("reco_k_theta", &reco_k_theta);

  // Reco quality metric branches
  tree->Branch("reco_k_purity", &reco_k_purity);
  tree->Branch("reco_k_completeness", &reco_k_completeness);

  SpectrumLoader loader(inputName);

  const SpillVar dummy_var([&](const caf::SRSpillProxy* sp){
    run.push_back(sp->hdr.run);
    subrun.push_back(sp->hdr.subrun);
    evt.push_back(sp->hdr.evt);
    
    //true_kaon_energy.push_back(kKaonTrueEnergy(sp));
    //true_kaon_energy.push_back(kMCKaonEnergy(sp));
    //reco_kaon_length.push_back(kKaonLength(sp));

    //slcid.push_back(kTrueBestSlice(sp));
    //kid.push_back(kTrueKaonID(sp));
    //kMCKaonID(sp);
    //kTrueVarKaonID(sp);

    // Fill true values
    stX.push_back(kKaonTrueStartX(sp));
    stY.push_back(kKaonTrueStartY(sp));
    stZ.push_back(kKaonTrueStartZ(sp));
    enX.push_back(kKaonTrueEndX(sp));
    enY.push_back(kKaonTrueEndY(sp));
    enZ.push_back(kKaonTrueEndZ(sp));
    Px.push_back(kKaonTruePx(sp));
    Py.push_back(kKaonTruePy(sp));
    Pz.push_back(kKaonTruePz(sp));
    p.push_back(kKaonTrueEnergy(sp));
    E.push_back(kKaonTrueEnergy(sp));
    phi.push_back(kKaonTruePhi(sp));
    theta.push_back(kKaonTrueTheta(sp));

    // Fill reco values
    reco_k_stX.push_back(kKaonStartX(sp));
    reco_k_stY.push_back(kKaonStartY(sp));
    reco_k_stZ.push_back(kKaonStartZ(sp));
    reco_k_enX.push_back(kKaonEndX(sp));
    reco_k_enY.push_back(kKaonEndY(sp));
    reco_k_enZ.push_back(kKaonEndZ(sp));
    reco_k_phi.push_back(kKaonPhi(sp));
    reco_k_theta.push_back(kKaonTheta(sp));
    reco_k_purity.push_back(kKaonPurity(sp));
    reco_k_completeness.push_back(kKaonCompleteness(sp));

    return 0;
  });

  const Binning dummy_bins = Binning::Simple(2, 0, 2);
  Spectrum dummy_spec("Dummy Label", dummy_bins, loader, dummy_var, kNoSpillCut);

  loader.Go();

  tree->Fill();
  file->Write();
  file->Close();

}