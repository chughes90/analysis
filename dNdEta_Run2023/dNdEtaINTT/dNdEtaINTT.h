// Tell emacs that this is a C++ source
//  -*- C++ -*-.
#ifndef DNDETAINTT_H
#define DNDETAINTT_H

#include <fun4all/SubsysReco.h>

#include <ffaobjects/EventHeader.h>

#include <g4eval/SvtxClusterEval.h>
#include <g4eval/SvtxEvalStack.h>
#include <g4eval/SvtxHitEval.h>
#include <g4eval/SvtxTruthEval.h>
#include <g4main/PHG4Hit.h>
#include <g4main/PHG4Particle.h>
#include <g4main/PHG4TruthInfoContainer.h>
#include <g4main/PHG4VtxPoint.h>
#include <phool/getClass.h>

#include <g4detectors/PHG4CylinderGeomContainer.h>
#include <intt/CylinderGeomIntt.h>

#include <phool/getClass.h>
#include <trackbase/ActsGeometry.h>
#include <trackbase/InttDefs.h>
#include <trackbase/MvtxDefs.h>
#include <trackbase/TrkrCluster.h>
#include <trackbase/TrkrClusterContainerv4.h>
#include <trackbase/TrkrClusterHitAssoc.h>
#include <trackbase/TrkrClusterv4.h>
#include <trackbase/TrkrDefs.h>
#include <trackbase/TrkrHitSet.h>
#include <trackbase/TrkrHitSetContainer.h>
#include <trackbase_historic/ActsTransformations.h>
#include <trackbase_historic/SvtxTrack.h>
#include <trackbase_historic/SvtxTrackMap.h>
// #include <trackbase_historic/SvtxVertex.h>
// #include <trackbase_historic/SvtxVertexMap.h>
// #include <centrality/CentralityInfov1.h>

#include <calotrigger/MinimumBiasInfo.h>
#include <centrality/CentralityInfo.h>
#include <globalvertex/GlobalVertex.h>
#include <globalvertex/GlobalVertexMap.h>
#include <globalvertex/MbdVertex.h>
#include <globalvertex/MbdVertexMap.h>
#include <mbd/MbdOut.h>

#include <math.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include <TFile.h>
#include <TLorentzVector.h>
#include <TTree.h>
#include <TVector3.h>

class PHCompositeNode;
class SvtxTrack;
class SvtxTrackMap;
class TrkrHitSetContainer;
class TrkrClusterContainer;
class CentralityInfo;
class MinimumBiasInfo;
class MbdOut;

class dNdEtaINTT : public SubsysReco
{
 public:
  dNdEtaINTT(const std::string &name = "dNdEtaINTTAnalyzer", const std::string &outputfile = "INTTdNdEta.root", const bool &isData = false);

  ~dNdEtaINTT() override;

  /** Called during initialization.
      Typically this is where you can book histograms, and e.g.
      register them to Fun4AllServer (so they can be output to file
      using Fun4AllServer::dumpHistos() method).
   */
  int Init(PHCompositeNode *topNode) override;

  /** Called for first event when run number is known.
      Typically this is where you may want to fetch data from
      database, because you know the run number. A place
      to book histograms which have to know the run number.
   */
  int InitRun(PHCompositeNode *topNode) override;

  /** Called for each event.
      This is where you do the real work.
   */
  int process_event(PHCompositeNode *topNode) override;

  /// Clean up internals after each event.
  int ResetEvent(PHCompositeNode *topNode) override;

  /// Called at the end of each run.
  int EndRun(const int runnumber) override;

  /// Called at the end of all processing.
  int End(PHCompositeNode *topNode) override;

  /// Reset
  int Reset(PHCompositeNode * /*topNode*/) override;

  void Print(const std::string &what = "ALL") const override;

  void GetTruthPV(bool b) { _get_truth_pv = b; }
  void GetRecoCluster(bool b) { _get_reco_cluster = b; }
  void GetINTTdata(bool b) { _get_intt_data = b; }
  void GetCentrality(bool b) { _get_centrality = b; }
  void GetTrkrHit(bool b) { _get_trkr_hit = b; }

 private:
  void ResetVectors();
  void GetTruthPVInfo(PHCompositeNode *topNode);
  void GetRecoClusterInfo(PHCompositeNode *topNode);
  void GetTruthClusterInfo(PHCompositeNode *topNode);
  void GetCentralityInfo(PHCompositeNode *topNode);
  void GetTrkrHitInfo(PHCompositeNode *topNode);
  PHG4Particle *GetG4PAncestor(PHG4Particle *p);

  bool _get_truth_pv;
  bool _get_reco_cluster;
  bool _get_centrality;
  bool _get_intt_data;
  bool _get_trkr_hit;

  unsigned int eventNum = 0;
  std::string _outputFile;
  bool IsData;
  // int InputFileListIndex;
  // int NEvtPerFile;

  TTree *outtree;
  int event_;
  // Centrality and MBD stuff
  float centrality_bimp_, centrality_impactparam_, centrality_mbd_, centrality_mbdquantity_;
  UShort_t femclk;
  float mbd_south_charge_sum, mbd_north_charge_sum, mbd_charge_sum, mbd_charge_asymm;
  float mbd_z_vtx;
  // std::set<std::pair<int, float>> m_pmt_q;
  bool is_min_bias;
  int ncoll_, npart_;  // number of collisions and participants
  // Truth primary vertex information
  float TruthPV_trig_x_, TruthPV_trig_y_, TruthPV_trig_z_;
  int NTruthVtx_;
  // Reconstructed cluster information
  int NClus_, NClus_Layer1_;
  std::vector<int> ClusLayer_, ClusHitcount_, ClusTimeBucketId_;
  std::vector<float> ClusX_, ClusY_, ClusZ_, ClusR_, ClusPhi_, ClusEta_;
  std::vector<unsigned int> ClusAdc_;
  std::vector<float> ClusPhiSize_, ClusZSize_;
  std::vector<uint8_t> ClusLadderZId_, ClusLadderPhiId_;
  std::vector<uint32_t> ClusTrkrHitSetKey_;
  std::vector<int> ClusTruthCKeys_;
  std::vector<int> TruthClusPhiSize_;
  std::vector<int> TruthClusZSize_;
  std::vector<int> PrimaryTruthClusPhiSize_;
  std::vector<int> PrimaryTruthClusZSize_;
  std::vector<int> ClusNG4Particles_;
  std::vector<int> ClusNPrimaryG4Particles_;
  std::vector<int> TruthClusNRecoClus_;
  std::vector<int> PrimaryTruthClusNRecoClus_;
  // TrkrHit information
  int NTrkrhits_;
  std::vector<uint16_t> TrkrHitRow_, TrkrHitColumn_, TrkrHitADC_;
  std::vector<uint8_t> TrkrHitLadderZId_, TrkrHitLadderPhiId_, TrkrHitLayer_;
  // G4 information Matching for simulation
  int NGenPart_, NTruthLayers_;
  std::vector<float> UniqueAncG4P_Pt_, UniqueAncG4P_Eta_, UniqueAncG4P_Phi_, UniqueAncG4P_E_;
  std::vector<int> UniqueAncG4P_PID_;

  EventHeader *eventheader = nullptr;

  SvtxEvalStack *svtx_evalstack = nullptr;
  SvtxTruthEval *truth_eval = nullptr;
  SvtxClusterEval *clustereval = nullptr;
  SvtxHitEval *hiteval = nullptr;

  TrkrClusterContainerv4 *dst_clustermap = nullptr;
  TrkrClusterHitAssoc *clusterhitmap = nullptr;
  TrkrHitSetContainer *hitsets = nullptr;
  ActsGeometry *_tgeometry = nullptr;
  PHG4CylinderGeomContainer *_intt_geom_container = nullptr;
  PHG4TruthInfoContainer *m_truth_info = nullptr;
  CentralityInfo *m_CentInfo = nullptr;
  MinimumBiasInfo *_minimumbiasinfo = nullptr;
  MbdOut *m_mbdout = nullptr;
  GlobalVertexMap *m_glbvtxmap = nullptr;
  GlobalVertex *m_glbvtx = nullptr;
  //MbdVertexMap *m_mbdvtxmap = nullptr;
  //MbdVertex *m_mbdvtx = nullptr;
};

#endif  // DNDETAINTT_H
