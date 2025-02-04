const SpillVar kKaonLength([](const caf::SRSpillProxy* sp) -> float {
  auto const& slc = sp->slc[kTrueBestSlice(sp)];
  auto const& pfps = slc.reco.pfp;
  auto const& pfp = pfps[kTrueKaonID(sp)];
  return pfp.trk.len;
});