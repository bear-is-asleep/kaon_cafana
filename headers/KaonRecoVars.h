/*
Hi bear, Im sorry about the time. Classes and other homework have kept me really busy.
The list of all of the branches I need is the following given as :
(edited)

The Branch Infomration, TheName
True Starting X Position, stX	
True Starting Y Position, stY	
True Starting Z Position, stZ
True Ending X Position, enX
True Ending Y Position, enY
True Ending Z Position, enZ
Reco Starting X Position, reco_k_stX	
Reco Starting Y Position, reco_k_stY	
Reco Starting Z Position, reco_k_stZ
Reco Ending X Position, reco_k_enX
Reco Ending Y Position, reco_k_enY
Reco Ending Z Position, reco_k_enZ
True Initial Momentum In X Direction, Px
True Initial Momentum In Y Direction, Py
True Initial Momentum In Z Direction, Pz
True Total initial Momentum, p
True Total initial Energy, E
True Phi, phi
True Theta, theta
Reco Phi, reco_k_phi
Reco Theta, recp_k_theta
Event number, event
Run Number, run
Subrun Number, subrun
Purity, reco_k_purity
Completeness, reco_k_completeness
*/

const SpillVar kKaonLength([](const caf::SRSpillProxy* sp) -> float {
  auto const& bestslice = kTrueBestSlice(sp);
  if (bestslice == 9999) return -9999;
  auto const& slc = sp->slc[bestslice];
  auto const& pfps = slc.reco.pfp;
  auto const& kaonID = kTrueKaonID(sp);
  if (kaonID == 9999) return -9999;
  auto const& pfp = pfps[kaonID];
  return pfp.trk.len;
});

const SpillVar kKaonStartX([](const caf::SRSpillProxy* sp) -> float {
  auto const& bestslice = kTrueBestSlice(sp);
  if (bestslice == 9999) return -9999;
  auto const& slc = sp->slc[bestslice];
  auto const& pfps = slc.reco.pfp;
  auto const& kaonID = kTrueKaonID(sp);
  if (kaonID == 9999) return -9999;
  auto const& pfp = pfps[kaonID];
  return pfp.trk.start.x;
});

const SpillVar kKaonStartY([](const caf::SRSpillProxy* sp) -> float {
  auto const& bestslice = kTrueBestSlice(sp);
  if (bestslice == 9999) return -9999;
  auto const& slc = sp->slc[bestslice];
  auto const& pfps = slc.reco.pfp;
  auto const& kaonID = kTrueKaonID(sp);
  if (kaonID == 9999) return -9999;
  auto const& pfp = pfps[kaonID];
  return pfp.trk.start.y;
});

const SpillVar kKaonStartZ([](const caf::SRSpillProxy* sp) -> float {
  auto const& bestslice = kTrueBestSlice(sp);
  if (bestslice == 9999) return -9999;
  auto const& slc = sp->slc[bestslice];
  auto const& pfps = slc.reco.pfp;
  auto const& kaonID = kTrueKaonID(sp);
  if (kaonID == 9999) return -9999;
  auto const& pfp = pfps[kaonID];
  return pfp.trk.start.z;
});

const SpillVar kKaonEndX([](const caf::SRSpillProxy* sp) -> float {
  auto const& bestslice = kTrueBestSlice(sp);
  if (bestslice == 9999) return -9999;
  auto const& slc = sp->slc[bestslice];
  auto const& pfps = slc.reco.pfp;
  auto const& kaonID = kTrueKaonID(sp);
  if (kaonID == 9999) return -9999;
  auto const& pfp = pfps[kaonID];
  return pfp.trk.end.x;
});

const SpillVar kKaonEndY([](const caf::SRSpillProxy* sp) -> float {
  auto const& bestslice = kTrueBestSlice(sp);
  if (bestslice == 9999) return -9999;
  auto const& slc = sp->slc[bestslice];
  auto const& pfps = slc.reco.pfp;
  auto const& kaonID = kTrueKaonID(sp);
  if (kaonID == 9999) return -9999;
  auto const& pfp = pfps[kaonID];
  return pfp.trk.end.y;
});

const SpillVar kKaonEndZ([](const caf::SRSpillProxy* sp) -> float {
  auto const& bestslice = kTrueBestSlice(sp);
  if (bestslice == 9999) return -9999;
  auto const& slc = sp->slc[bestslice];
  auto const& pfps = slc.reco.pfp;
  auto const& kaonID = kTrueKaonID(sp);
  if (kaonID == 9999) return -9999;
  auto const& pfp = pfps[kaonID];
  return pfp.trk.end.z;
});

const SpillVar kKaonTheta([](const caf::SRSpillProxy* sp) -> float {
  auto const& bestslice = kTrueBestSlice(sp);
  if (bestslice == 9999) return -9999;
  auto const& slc = sp->slc[bestslice];
  auto const& pfps = slc.reco.pfp;
  auto const& kaonID = kTrueKaonID(sp);
  if (kaonID == 9999) return -9999;
  auto const& pfp = pfps[kaonID];
  return acos(pfp.trk.costh);
});

const SpillVar kKaonPhi([](const caf::SRSpillProxy* sp) -> float {
  auto const& bestslice = kTrueBestSlice(sp);
  if (bestslice == 9999) return -9999;
  auto const& slc = sp->slc[bestslice];
  auto const& pfps = slc.reco.pfp;
  auto const& kaonID = kTrueKaonID(sp);
  if (kaonID == 9999) return -9999;
  auto const& pfp = pfps[kaonID];
  return pfp.trk.phi;
});