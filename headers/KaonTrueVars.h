const SpillCut kCosmicSpill([](const caf::SRSpillProxy* sp) {
    return sp->mc.nnu == 0;
  });

const SpillCut kMultiNu([](const caf::SRSpillProxy* sp) {
    return sp->mc.nnu > 1;
  });

// Choose the neutrino that deposited the most energy in the TPC, this neutrino will
// be used to determine the event type (e.g. CCNuMu) and be the target of selection.
const SpillVar kBestNuID([](const caf::SRSpillProxy* sp) {
    int id = std::numeric_limits<int>::max(), counter = 0;
    double most_en = -std::numeric_limits<double>::max();

    for(auto const& nu : sp->mc.nu)
      {
        double visE = nu.plane[0][0].visE + nu.plane[0][1].visE + nu.plane[0][2].visE;

        if(visE > most_en)
          {
            most_en = visE;

            id      = counter;
          }
        ++counter;
      }
    return id;
  });

const SpillVar kTrueBestSlice([](const caf::SRSpillProxy* sp) -> unsigned {
    if(kCosmicSpill(sp))
      return 999999;
    std::cout<< "**Nslc: " << sp->slc.size() << std::endl;
    auto const& nuid = sp->mc.nu[kBestNuID(sp)].index;

    float best_eff(-1.f);
    unsigned id = 0, returnid = 999999;

    for(auto const &slc : sp->slc)
      {
        if(slc.tmatch.index == nuid && slc.tmatch.eff > best_eff)
          {
            best_eff = slc.tmatch.eff;
            returnid = id;
          }
        ++id;
      }

    return returnid;
  });

const SpillVar kTrueKaonID([](const caf::SRSpillProxy* sp) -> unsigned {
  auto const& slc = sp->slc[kTrueBestSlice(sp)];
  int kaonID = 0;
  std::cout << "N PFPs: " << slc.reco.pfp.size() << std::endl;

  auto const& pfps = slc.reco.pfp;

  for (auto const& pfp : pfps)
    {
      int pdg = abs(pfp.trk.truth.p.pdg);
      std::cout << "pfp matched pdg: " << pdg << std::endl;
      //if (pdg == 13){ /*Make sure this is a pdg of 321*/
      //  return kaonID;
      //}
      kaonID++;
    }
  //return 99999;
  return 0;
  
  });

/*delete this*/
// const SpillVar kTrueVarKaonID([](const caf::SRSpillProxy* sr) -> unsigned {
//   auto const& pfps = sr->reco.pfp;
//   int kaonID = 0;
//   std::cout << "N PFPs: " << pfps.size() << std::endl;
//   if (pfps.size() == 0) return 99999;

//   for (auto const& pfp : pfps)
//     {
//       int pdg = abs(pfp.trk.truth.p.pdg);
//       std::cout << "pdg: " << pdg << std::endl;
//       //if (pdg == 13){ /*Make sure this is a pdg of 321*/
//       //  return kaonID;
//       //}
//       kaonID++;
//     }
  
//   });

const SpillVar kMCKaonID([](const caf::SRSpillProxy* sp) -> unsigned {
  auto const& nu = sp->mc.nu[kBestNuID(sp)];
  int kaonID = 0;
  std::cout << "N Primaries: " << nu.prim.size() << std::endl;

  for (auto const& prim : nu.prim)
    {
      int pdg = abs(prim.pdg);
      if (pdg == 321){ /*Make sure this is a pdg of 321*/
       return kaonID;
      }
      kaonID++;
    }
  //return 99999;
  return 0; //temporary
  
  });

const SpillVar kKaonTrueEnergy([](const caf::SRSpillProxy* sp) -> float {
  auto const& slc = sp->slc[kTrueBestSlice(sp)];
  auto const& pfps = slc.reco.pfp;
  auto const& pfp = pfps[kTrueKaonID(sp)];
  return pfp.trk.truth.p.genE;
});

const SpillVar kMCKaonEnergy([](const caf::SRSpillProxy* sp) -> float {
  auto const& nu = sp->mc.nu[kBestNuID(sp)];
  auto const& prim = nu.prim[kMCKaonID(sp)];
  return prim.genE;
});


